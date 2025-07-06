#include "main_app.h"
#include "main_frame.h"

BOOL CMainApp::InitInstance()
{
    // Create the main frame window and set it as the main window
    CMainFrame *frame = new CMainFrame();
    m_pMainWnd = frame;

    // Hide the main window by default
    frame->ShowWindow(SW_HIDE);
    frame->UpdateWindow();

    return TRUE;
}