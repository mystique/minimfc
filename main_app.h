#pragma once

/**
 * @file main_app.h
 * @brief 主应用程序类声明文件
 *
 * 本文件定义了CMainApp类，该类继承自CWinApp，是整个MFC应用程序的核心类。
 * 主要负责应用程序的初始化和管理。
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

#include <afxwin.h>

/**
 * @class CMainApp
 * @brief 主应用程序类
 *
 * CMainApp是应用程序的主类，继承自MFC的CWinApp基类。
 * 负责处理应用程序的生命周期，包括初始化、运行和清理工作。
 */
class CMainApp : public CWinApp
{
public:
    /**
     * @brief 初始化应用程序实例
     *
     * 此虚函数在应用程序启动时被调用，用于执行应用程序的初始化工作。
     * 主要包括创建主窗口、设置窗口属性等操作。
     *
     * @return BOOL 初始化成功返回TRUE，失败返回FALSE
     */
    virtual BOOL InitInstance() override;
};
