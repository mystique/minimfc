#include "main_app.h"
#include "main_frame.h"

/**
 * @file main_app.cpp
 * @brief 主应用程序类实现文件
 *
 * 本文件实现了CMainApp类的成员函数，主要负责应用程序的初始化过程。
 * 创建主框架窗口并将其设置为应用程序的主窗口。
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

BOOL CMainApp::InitInstance()
{
    /**
     * @brief 初始化应用程序实例
     *
     * 此函数是应用程序启动后的入口点，执行以下关键操作：
     * 1. 创建主框架窗口对象
     * 2. 将创建的窗口设置为应用程序的主窗口
     * 3. 默认隐藏主窗口（因为这是一个托盘应用程序）
     * 4. 更新窗口显示
     *
     * @return BOOL 总是返回TRUE，表示初始化成功
     */

    // 创建主框架窗口并将其设置为应用程序的主窗口
    // CMainFrame是自定义的主窗口类，负责处理用户界面和系统托盘交互
    CMainFrame *frame = new CMainFrame();
    m_pMainWnd = frame;

    // 默认隐藏主窗口，因为这是一个系统托盘应用程序
    // 用户主要通过系统托盘图标与应用程序交互
    frame->ShowWindow(SW_HIDE);
    frame->UpdateWindow();

    return TRUE;
}
