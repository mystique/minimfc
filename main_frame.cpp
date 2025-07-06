#include "main_frame.h"

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_SYSCOMMAND()
    ON_MESSAGE(WM_USER + 1, OnTrayNotify)
    ON_COMMAND(ID_MENU_QUIT, OnQuit)
    ON_COMMAND(ID_MENU_TOGGLE_WINDOW, OnToggleWindow)
    ON_WM_CLOSE()
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
    // Create the main window with the title "MFC"
    if (!Create(NULL, _T("MFC"))) {
        AfxMessageBox(_T("Failed to create main window"));
        return;
    }

    // Set the title bar icon for the window
    HICON hIcon = AfxGetApp()->LoadIcon(MAIN_ICON);
    if (hIcon) {
        SetIcon(hIcon, TRUE);  // Set big icon
        SetIcon(hIcon, FALSE); // Set small icon
    }

    // Initialize the system tray icon data
    m_nid.cbSize = sizeof(NOTIFYICONDATA);
    m_nid.hWnd = this->GetSafeHwnd();
    m_nid.uID = 1;
    m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_nid.uCallbackMessage = WM_USER + 1; // Custom message for tray icon events
    m_nid.hIcon = hIcon;
    wcscpy_s(m_nid.szTip, sizeof(m_nid.szTip) / sizeof(wchar_t),
             L"MFC"); // Tooltip text for the tray icon

    // Add the icon to the system tray
    if (!Shell_NotifyIcon(NIM_ADD, &m_nid)) {
        AfxMessageBox(_T("Failed to add system tray icon"));
    }
}

void CMainFrame::PostNcDestroy()
{
    // Remove the system tray icon
    if (!Shell_NotifyIcon(NIM_DELETE, &m_nid)) {
        // Log or handle failure if needed, though not critical at destruction
    }
    CFrameWnd::PostNcDestroy();
}

LRESULT CMainFrame::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    // Handle right-click on the system tray icon to show context menu
    if (lParam == WM_RBUTTONDOWN) {
        // Load the context menu from resources
        CMenu menu;
        if (!menu.LoadMenu(ID_MENU)) {
            AfxMessageBox(_T("Failed to load context menu"));
            return 0L;
        }
        CMenu *pPopup = menu.GetSubMenu(0); // Get the first submenu
        if (!pPopup) {
            AfxMessageBox(_T("Failed to get submenu"));
            return 0L;
        }

        // Get the current mouse position for menu placement
        POINT curPoint;
        GetCursorPos(&curPoint);

        // Bring the window to the foreground and display the context menu
        SetForegroundWindow();
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, curPoint.x, curPoint.y, this);
        PostMessage(WM_NULL); // Prevent focus issues
    }
    return 0L;
}

void CMainFrame::OnQuit()
{
    // Call OnClose to handle the close prompt
    OnClose();
}

void CMainFrame::OnToggleWindow()
{
    // Toggle the visibility of the main window
    if (IsWindowVisible()) {
        ShowWindow(SW_HIDE);
    } else {
        ShowWindow(SW_SHOW);
        BringWindowToTop();
    }
}

void CMainFrame::OnClose()
{
    // Display a confirmation dialog before closing
    if (AfxMessageBox(_T("Are you sure you want to close the program?"),
                      MB_YESNO | MB_ICONQUESTION) == IDYES) {
        // Remove the system tray icon and terminate the application
        if (!Shell_NotifyIcon(NIM_DELETE, &m_nid)) {
            // Log or handle failure if needed
        }
        CFrameWnd::OnClose(); // Call base class to close the window
    }
}