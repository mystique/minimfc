#include <afxwin.h>
#include "resource.h"

class CMainFrame : public CFrameWnd
{
public:
    CMainFrame()
    {
        Create(NULL, _T("MFC"));

        m_nid.cbSize = sizeof(NOTIFYICONDATA);
        m_nid.hWnd = this->GetSafeHwnd();
        m_nid.uID = 1;
        m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        m_nid.uCallbackMessage = WM_USER + 1;
        m_nid.hIcon = AfxGetApp()->LoadIcon(MAIN_ICON);
        wcscpy_s(m_nid.szTip, L"MFC");

        Shell_NotifyIcon(NIM_ADD, &m_nid);
    }

    virtual void PostNcDestroy()
    {
        Shell_NotifyIcon(NIM_DELETE, &m_nid);
        CFrameWnd::PostNcDestroy();
    }
private:
    NOTIFYICONDATA m_nid;
protected:
    afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
    afx_msg void OnQuit();

    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_SYSCOMMAND()
    ON_MESSAGE(WM_USER + 1, OnTrayNotify)
    ON_COMMAND(ID_MENU_QUIT, OnQuit)
END_MESSAGE_MAP()

LRESULT CMainFrame::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    if (lParam == WM_RBUTTONDOWN)
    {
        CMenu menu;
        menu.LoadMenu(ID_MENU);
        CMenu* pPopup = menu.GetSubMenu(0);

        POINT curPoint;
        GetCursorPos(&curPoint);

        SetForegroundWindow();
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, curPoint.x, curPoint.y, this);
        PostMessage(WM_NULL);
    }
    return 0L;
}

void CMainFrame::OnQuit()
{
    Shell_NotifyIcon(NIM_DELETE, &m_nid);
    PostQuitMessage(0);
}

class CMainApp : public CWinApp
{
    BOOL InitInstance()
    {
        CMainFrame* frame = new CMainFrame();
        m_pMainWnd = frame;

        frame->ShowWindow(SW_NORMAL);
        frame->UpdateWindow();

        return TRUE;
    }
};

CMainApp app;