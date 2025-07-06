#pragma once

#include "resource.h"
#include <afxwin.h>

class CMainFrame : public CFrameWnd
{
public:
    // Constructor
    CMainFrame();

    // Called after the window is destroyed to clean up resources
    virtual void PostNcDestroy() override;

private:
    NOTIFYICONDATA m_nid;

protected:
    // Message handlers
    afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
    afx_msg void OnQuit();
    afx_msg void OnToggleWindow();
    afx_msg void OnClose();

    DECLARE_MESSAGE_MAP()
};