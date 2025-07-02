#include "resource.h"
#include <afxwin.h>

// Main entry point for the MFC application

class CMainFrame : public CFrameWnd {
  public:
    // Constructor for the main frame window
    CMainFrame() {
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

    // Called after the window is destroyed to clean up resources
    virtual void PostNcDestroy() {
        // Remove the system tray icon
        if (!Shell_NotifyIcon(NIM_DELETE, &m_nid)) {
            // Log or handle failure if needed, though not critical at
            // destruction
        }
        CFrameWnd::PostNcDestroy();
    }

  private:
    NOTIFYICONDATA m_nid;

  protected:
    // Handler for system tray icon notifications
    afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
    // Handler for the quit menu command
    afx_msg void OnQuit();
    // Handler for toggling window visibility
    afx_msg void OnToggleWindow();
    // Handler for window close event
    afx_msg void OnClose();

    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
ON_WM_SYSCOMMAND()
ON_MESSAGE(WM_USER + 1, OnTrayNotify)
ON_COMMAND(ID_MENU_QUIT, OnQuit)
ON_COMMAND(ID_MENU_TOGGLE_WINDOW, OnToggleWindow)
ON_WM_CLOSE()
END_MESSAGE_MAP()

LRESULT CMainFrame::OnTrayNotify(WPARAM wParam, LPARAM lParam) {
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

void CMainFrame::OnQuit() {
    // Call OnClose to handle the close prompt
    OnClose();
}

void CMainFrame::OnToggleWindow() {
    // Toggle the visibility of the main window
    if (IsWindowVisible()) {
        ShowWindow(SW_HIDE);
    } else {
        ShowWindow(SW_SHOW);
        BringWindowToTop();
    }
}

void CMainFrame::OnClose() {
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

class CMainApp : public CWinApp {
    // Initialize the application instance
    BOOL InitInstance() {
        // Create the main frame window and set it as the main window
        CMainFrame *frame = new CMainFrame();
        m_pMainWnd = frame;

        // Hide the main window by default
        frame->ShowWindow(SW_HIDE);
        frame->UpdateWindow();

        return TRUE;
    }
};

CMainApp app;
