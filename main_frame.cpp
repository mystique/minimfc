#include "main_frame.h"

/**
 * @file main_frame.cpp
 * @brief 主框架窗口类实现文件
 *
 * 本文件实现了CMainFrame类的所有成员函数，包括窗口创建、系统托盘图标管理、
 * 消息处理等功能。这是应用程序的核心实现文件。
 *
 * Copyright (C) 2025 mystique
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// 消息映射开始
// 将Windows消息与对应的处理函数关联起来
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    // 处理系统命令消息
    ON_WM_SYSCOMMAND()
    // 处理自定义托盘图标消息（WM_USER + 1）
    ON_MESSAGE(WM_USER + 1, OnTrayNotify)
    // 处理退出菜单命令
    ON_COMMAND(ID_MENU_QUIT, OnQuit)
    // 处理切换窗口显示状态菜单命令
    ON_COMMAND(ID_MENU_TOGGLE_WINDOW, OnToggleWindow)
    // 处理窗口关闭消息
    ON_WM_CLOSE()
END_MESSAGE_MAP()

/**
 * @brief 主框架窗口构造函数
 *
 * 初始化主框架窗口，执行以下关键操作：
 * 1. 创建主窗口，设置标题为"MFC"
 * 2. 加载并设置窗口图标
 * 3. 初始化系统托盘图标数据结构
 * 4. 将托盘图标添加到系统托盘
 *
 * 如果窗口创建失败，会显示错误消息并终止构造函数执行。
 */
CMainFrame::CMainFrame()
{
    // 创建主窗口，标题设置为"MFC"
    // 如果创建失败，显示错误消息并返回
    if (!Create(NULL, _T("MFC"))) {
        AfxMessageBox(_T("Failed to create main window"));
        return;
    }

    // 从应用程序资源中加载主图标
    // MAIN_ICON在resource.h中定义，对应资源ID为201
    HICON hIcon = AfxGetApp()->LoadIcon(MAIN_ICON);
    if (hIcon) {
        // 为窗口设置大图标（TRUE）和小图标（FALSE）
        SetIcon(hIcon, TRUE);  // 设置大图标（任务栏、窗口切换器等）
        SetIcon(hIcon, FALSE); // 设置小图标（标题栏、Alt+Tab等）
    }

    // 初始化系统托盘图标数据结构
    // 设置托盘图标的基本属性和行为
    m_nid.cbSize = sizeof(NOTIFYICONDATA);              // 结构体大小
    m_nid.hWnd = this->GetSafeHwnd();                   // 接收托盘消息的窗口句柄
    m_nid.uID = 1;                                      // 托盘图标的唯一标识符
    m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;    // 标志：启用消息、图标和提示文本
    m_nid.uCallbackMessage = WM_USER + 1;               // 自定义消息ID，用于托盘事件通知
    m_nid.hIcon = hIcon;                                // 托盘图标句柄

    // 设置托盘图标的提示文本（鼠标悬停时显示）
    // 使用宽字符拷贝函数，确保Unicode兼容性
    wcscpy_s(m_nid.szTip, sizeof(m_nid.szTip) / sizeof(wchar_t),
             L"MFC"); // 提示文本为"MFC"

    // 将图标添加到系统托盘
    // 如果添加失败，显示错误消息
    if (!Shell_NotifyIcon(NIM_ADD, &m_nid)) {
        AfxMessageBox(_T("Failed to add system tray icon"));
    }
}

/**
 * @brief 窗口销毁后的清理函数
 *
 * 此函数在窗口销毁后被调用，用于执行清理工作。
 * 主要负责从系统托盘中移除图标，防止系统托盘图标在应用程序
 * 退出后仍然残留在托盘中。
 *
 * 注意：在窗口销毁阶段，托盘图标删除失败通常不是严重问题，
 * 因为操作系统会在进程结束后自动清理相关资源。
 */
void CMainFrame::PostNcDestroy()
{
    // 从系统托盘中删除图标
    // 使用NIM_DELETE命令移除之前添加的托盘图标
    if (!Shell_NotifyIcon(NIM_DELETE, &m_nid)) {
        // 删除失败时的处理（通常不做特殊处理，因为在销毁阶段失败不严重）
        // 在实际项目中，这里可以添加日志记录，但对于此示例程序不做处理
    }

    // 调用基类的PostNcDestroy函数，完成标准的窗口销毁清理工作
    CFrameWnd::PostNcDestroy();
}

/**
 * @brief 系统托盘图标通知消息处理函数
 *
 * 处理来自系统托盘图标的各种通知消息。目前主要处理鼠标右键点击事件，
 * 当用户右键点击托盘图标时，显示上下文菜单供用户选择操作。
 *
 * @param wParam 消息参数，标识托盘图标的ID（当前固定为1）
 * @param lParam 消息参数，标识具体的消息类型和鼠标状态
 * @return LRESULT 处理结果，总是返回0
 */
LRESULT CMainFrame::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    // 仅处理鼠标右键点击事件
    // 当用户右键点击托盘图标时，显示上下文菜单
    if (lParam == WM_RBUTTONDOWN) {
        // 从资源文件中加载上下文菜单
        // ID_MENU在resource.h中定义，对应资源ID为101
        CMenu menu;
        if (!menu.LoadMenu(ID_MENU)) {
            AfxMessageBox(_T("Failed to load context menu"));
            return 0L;
        }

        // 获取菜单的第一个子菜单（弹出菜单）
        // GetSubMenu(0)表示获取第一个子菜单
        CMenu *pPopup = menu.GetSubMenu(0);
        if (!pPopup) {
            AfxMessageBox(_T("Failed to get submenu"));
            return 0L;
        }

        // 获取当前鼠标位置，用于菜单显示定位
        // 菜单将显示在鼠标点击位置附近
        POINT curPoint;
        GetCursorPos(&curPoint);

        // 将窗口置于前台并显示上下文菜单
        // SetForegroundWindow确保菜单显示时窗口获得焦点
        SetForegroundWindow();

        // 显示弹出菜单
        // TPM_LEFTALIGN：左对齐显示
        // TPM_RIGHTBUTTON：右键菜单样式
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, curPoint.x, curPoint.y, this);

        // 发送空消息防止焦点问题
        // WM_NULL是一个空消息，不会产生任何效果，但可以解决菜单关闭后的焦点问题
        PostMessage(WM_NULL);
    }

    // 其他类型的托盘消息暂不处理，直接返回0
    return 0L;
}

/**
 * @brief 退出应用程序消息处理函数
 *
 * 处理用户从托盘菜单选择"退出"时的命令消息。
 * 此函数不直接退出应用程序，而是调用OnClose函数，
 * 让OnClose函数来处理退出前的确认对话框和清理工作。
 *
 * 这种设计使得退出逻辑集中在一个地方，便于维护。
 */
void CMainFrame::OnQuit()
{
    // 调用OnClose函数来处理退出前的确认和清理工作
    // 这样可以将退出逻辑集中在OnClose函数中，避免重复代码
    OnClose();
}

/**
 * @brief 切换窗口显示状态消息处理函数
 *
 * 处理用户从托盘菜单选择"切换窗口"时的命令消息。
 * 此函数可以显示或隐藏主窗口，并确保显示的窗口获得焦点。
 *
 * 功能类似于任务管理器中的"显示/隐藏窗口"操作。
 */
void CMainFrame::OnToggleWindow()
{
    // 检查窗口当前是否可见
    if (IsWindowVisible()) {
        // 窗口当前可见，则隐藏窗口
        // SW_HIDE表示隐藏窗口，但不销毁窗口
        ShowWindow(SW_HIDE);
    } else {
        // 窗口当前隐藏，则显示窗口并置于顶层
        ShowWindow(SW_SHOW);        // 显示窗口
        BringWindowToTop();         // 将窗口置于其他窗口之上，确保可见
    }
}

/**
 * @brief 窗口关闭消息处理函数
 *
 * 处理窗口关闭消息（通常由用户点击关闭按钮或选择退出产生）。
 * 在关闭窗口之前显示确认对话框，只有在用户确认后才真正关闭。
 *
 * 此函数还负责清理系统托盘图标，确保应用程序完全退出。
 */
void CMainFrame::OnClose()
{
    // 显示确认对话框，询问用户是否确定要关闭程序
    // MB_YESNO：显示"是"和"否"按钮
    // MB_ICONQUESTION：显示问号图标，表示这是一个询问对话框
    if (AfxMessageBox(_T("Are you sure you want to close the program?"),
                      MB_YESNO | MB_ICONQUESTION) == IDYES) {

        // 用户确认退出，执行清理工作并关闭窗口

        // 从系统托盘中删除图标
        // 确保应用程序退出后托盘中没有残留图标
        if (!Shell_NotifyIcon(NIM_DELETE, &m_nid)) {
            // 删除失败时的处理（通常记录日志）
            // 在实际项目中，这里应该添加适当的错误处理或日志记录
        }

        // 调用基类的OnClose函数，完成窗口关闭操作
        // 这将触发窗口销毁和应用程序退出流程
        CFrameWnd::OnClose();
    }
    // 如果用户选择"否"，则不执行任何操作，窗口保持打开状态
}
