#pragma once

/**
 * @file main_frame.h
 * @brief 主框架窗口类声明文件
 *
 * 本文件定义了CMainFrame类，该类继承自CFrameWnd，是应用程序的主窗口。
 * 主要负责窗口管理、系统托盘图标处理和用户交互。
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

#include "resource.h"
#include <afxwin.h>

/**
 * @class CMainFrame
 * @brief 主框架窗口类
 *
 * CMainFrame是应用程序的主窗口类，继承自MFC的CFrameWnd基类。
 * 除了基本的窗口功能外，还实现了系统托盘图标功能，
 * 允许用户通过托盘图标与应用程序进行交互。
 */
class CMainFrame : public CFrameWnd
{
public:
    /**
     * @brief 构造函数
     *
     * 初始化主框架窗口，创建窗口和系统托盘图标。
     * 在构造函数中会设置窗口标题、图标，并初始化托盘图标数据结构。
     */
    CMainFrame();

    /**
     * @brief 窗口销毁后的清理工作
     *
     * 此虚函数在窗口销毁后被调用，用于清理资源。
     * 主要负责从系统托盘中移除图标，防止资源泄露。
     */
    virtual void PostNcDestroy() override;

private:
    /** @brief 系统托盘图标数据结构
     *
     * NOTIFYICONDATA结构体包含托盘图标的所有信息，
     * 包括图标句柄、提示文本、回调消息等。
     */
    NOTIFYICONDATA m_nid;

protected:
    /**
     * @brief 系统托盘图标通知消息处理函数
     *
     * 处理来自系统托盘图标的各种消息，特别是鼠标右键点击事件。
     * 当用户右键点击托盘图标时，显示上下文菜单。
     *
     * @param wParam 消息参数，标识托盘图标的ID
     * @param lParam 消息参数，标识具体的消息类型（如鼠标点击）
     * @return LRESULT 处理结果，通常返回0
     */
    afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);

    /**
     * @brief 退出应用程序消息处理函数
     *
     * 处理用户选择退出菜单项时的消息。
     * 会调用OnClose函数来执行退出前的确认和清理工作。
     */
    afx_msg void OnQuit();

    /**
     * @brief 切换窗口显示状态消息处理函数
     *
     * 处理用户选择切换窗口显示状态的菜单项。
     * 可以显示或隐藏主窗口，并将窗口置于前景。
     */
    afx_msg void OnToggleWindow();

    /**
     * @brief 窗口关闭消息处理函数
     *
     * 处理窗口关闭消息，显示确认对话框。
     * 如果用户确认退出，则从托盘中移除图标并关闭窗口。
     */
    afx_msg void OnClose();

    // 声明消息映射宏，用于将Windows消息与处理函数关联
    DECLARE_MESSAGE_MAP()
};
