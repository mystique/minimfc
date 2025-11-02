# minimfc - 最小化 MFC 系统托盘应用程序

[![Build and Release MFC Project](https://github.com/mystique/minimfc/actions/workflows/main.yml/badge.svg)](https://github.com/mystique/minimfc/actions/workflows/main.yml)
![License](https://img.shields.io/badge/license-GPL%20v3-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-blue.svg)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)

**minimfc** 是一个简洁而优雅的 Microsoft Foundation Classes (MFC) 应用框架，专为构建 Windows 系统托盘应用程序而设计。这个项目演示了如何使用现代 C++ 和 MFC 创建最小化的、功能完整的系统托盘应用程序。

## 📋 目录

- [功能特性](#功能特性)
- [系统要求](#系统要求)
- [构建项目](#构建项目)
- [使用](#使用)
- [项目结构](#项目结构)
- [核心组件](#核心组件)
- [开发](#开发)
- [许可证](#许可证)
- [贡献](#贡献)

## ✨ 功能特性

- **🖼️ 系统托盘集成** - 完全的系统托盘图标支持，支持右键菜单交互
- **🎯 最小化设计** - 精简的代码库，易于理解和扩展
- **⚙️ 现代 C++** - 使用 C++17 标准编写
- **🔧 两种构建方式** - 同时支持 CMake 和 Visual Studio 项目文件
- **🪟 正向 Unicode** - 完整的 Unicode 支持，无缝支持国际化文本
- **🚀 自动发布** - GitHub Actions 自动构建和发布
- **📦 多平台构建** - 支持 Win32 和 x64 平台

## 🖥️ 系统要求

### 必需组件

- **操作系统**: Windows 7 或更新版本
- **编译器**: Visual Studio 2022（或更新的 MSVC 工具链）
- **C++ 标准**: C++17
- **MFC**: Microsoft Foundation Classes（通常包含在 Visual Studio 中）
- **构建工具**:
  - 选项 1: Visual Studio 2022（完整安装）
  - 选项 2: CMake 3.20 或更新版本

### 可选组件

- **Git**: 用于版本控制
- **Clang-Format**: 代码格式化（项目包含 `.clang-format` 配置）

## 🔨 构建项目

### 方法 1：使用 Visual Studio（推荐）

1. **克隆仓库**
   ```bash
   git clone https://github.com/mystique/minimfc.git
   cd minimfc
   ```

2. **打开解决方案**
   - 使用 Visual Studio 2022 打开 `minimfc.sln`

3. **配置构建**
   - 选择configuration：Debug 或 Release
   - 选择平台：Win32 或 x64

4. **构建项目**
   - 按 `Ctrl+Shift+B` 或选择 "构建" → "生成解决方案"

5. **运行应用程序**
   - 按 `Ctrl+F5` 或选择 "调试" → "开始执行（不调试）"

### 方法 2：使用 CMake

1. **克隆仓库**
   ```bash
   git clone https://github.com/mystique/minimfc.git
   cd minimfc
   ```

2. **创建构建目录**
   ```bash
   mkdir build
   cd build
   ```

3. **生成 Visual Studio 项目文件**
   ```bash
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```

4. **构建项目**
   ```bash
   cmake --build . --config Release
   ```

5. **运行应用程序**
   ```bash
   ./Release/minimfc.exe
   ```

### 方法 3：使用命令行编译

1. **打开 Visual Studio 命令提示符**
   - 从 Visual Studio 2022 菜单中选择 "Developer Command Prompt"

2. **导航到项目目录**
   ```bash
   cd C:\path\to\minimfc
   ```

3. **构建项目**
   ```bash
   msbuild /p:Configuration=Release /p:Platform=x64 minimfc.sln
   ```

4. **运行应用程序**
   ```bash
   x64\Release\minimfc.exe
   ```

## 📖 使用

### 启动应用程序

执行编译后的 `minimfc.exe`，应用程序将：
1. 创建主窗口（默认隐藏）
2. 在系统托盘中添加一个图标（显示 "MFC" 提示文本）
3. 监听用户交互

### 系统托盘交互

**右键点击托盘图标**将显示上下文菜单，包含以下选项：

- **切换窗口 (Toggle Window)** - 显示或隐藏主窗口
- **退出 (Quit)** - 退出应用程序

### 常见操作

| 操作 | 说明 |
|------|------|
| 右键点击托盘图标 | 显示上下文菜单 |
| 选择"切换窗口" | 显示/隐藏主窗口 |
| 选择"退出" | 关闭应用程序（显示确认对话框） |
| 窗口关闭按钮 | 触发关闭确认对话框 |

## 📁 项目结构

```
minimfc/
├── CMakeLists.txt              # CMake 配置文件
├── minimfc.sln                 # Visual Studio 解决方案文件
├── minimfc.vcxproj             # Visual Studio 项目文件
├── minimfc.vcxproj.user        # Visual Studio 用户配置文件
├── .clang-format               # Clang-Format 代码风格配置
├── .gitignore                  # Git 忽略文件列表
├── LICENSE                     # GNU General Public License v3
├── app.ico                     # 应用程序图标
├── resource.h                  # 资源文件常量定义
├── main.rc                     # 资源脚本文件
│
├── main.cpp                    # 应用程序入口点
├── main_app.h                  # 应用程序类声明
├── main_app.cpp                # 应用程序类实现
├── main_frame.h                # 主窗口框架类声明
├── main_frame.cpp              # 主窗口框架类实现
│
├── .github/
│   └── workflows/
│       └── main.yml            # GitHub Actions CI/CD 工作流
│
└── build/                      # 构建输出目录（CMake）
    ├── Debug/
    └── Release/
```

## 🏗️ 核心组件

### 1. 应用程序类 - `CMainApp`

**文件**: `main_app.h`, `main_app.cpp`

继承自 `CWinApp`，负责应用程序的整个生命周期。

**主要职责**:
- 应用程序初始化（`InitInstance()`）
- 创建主窗口框架
- 管理应用程序事件循环

```cpp
class CMainApp : public CWinApp
{
public:
    virtual BOOL InitInstance() override;
};
```

### 2. 主窗口框架 - `CMainFrame`

**文件**: `main_frame.h`, `main_frame.cpp`

继承自 `CFrameWnd`，是应用程序的主窗口，并处理系统托盘功能。

**主要职责**:
- 窗口创建和管理
- 系统托盘图标初始化和管理
- 上下文菜单处理
- 用户交互事件处理

**关键成员函数**:
- `CMainFrame()` - 构造函数，初始化窗口和托盘
- `PostNcDestroy()` - 窗口销毁时的清理
- `OnTrayNotify()` - 托盘通知消息处理
- `OnToggleWindow()` - 切换窗口显示状态
- `OnQuit()` - 退出命令处理
- `OnClose()` - 窗口关闭处理

**Windows 消息映射**:
```cpp
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_SYSCOMMAND()
    ON_MESSAGE(WM_USER + 1, OnTrayNotify)      // 托盘消息
    ON_COMMAND(ID_MENU_QUIT, OnQuit)           // 退出菜单
    ON_COMMAND(ID_MENU_TOGGLE_WINDOW, OnToggleWindow)  // 切换窗口
    ON_WM_CLOSE()                              // 窗口关闭
END_MESSAGE_MAP()
```

### 3. 系统托盘集成

应用程序使用 Windows Shell API 进行系统托盘管理：

**关键 API**:
- `Shell_NotifyIcon(NIM_ADD, ...)` - 添加托盘图标
- `Shell_NotifyIcon(NIM_DELETE, ...)` - 删除托盘图标
- `NOTIFYICONDATA` - 托盘图标数据结构

**初始化流程**:
```cpp
NOTIFYICONDATA m_nid;
m_nid.cbSize = sizeof(NOTIFYICONDATA);
m_nid.hWnd = GetSafeHwnd();
m_nid.uID = 1;
m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
m_nid.uCallbackMessage = WM_USER + 1;
m_nid.hIcon = LoadIcon(MAIN_ICON);
Shell_NotifyIcon(NIM_ADD, &m_nid);
```

## 💻 开发

### 代码风格

项目包含 `.clang-format` 文件，定义了代码风格规范。

**格式化代码** (使用 Clang-Format):
```bash
clang-format -i *.cpp *.h
```

### 编译配置

**CMakeLists.txt 配置**:
- C++ 标准: C++17
- MFC 模式: 动态链接（Shared DFC）
- 字符集: Unicode
- 平台: Windows 专用

**Visual Studio 项目配置**:
- 平台: Win32, x64
- 配置: Debug, Release
- 工具集: MSVC v143（Visual Studio 2022）
- MFC: 动态链接库

### 自动化构建和发布

项目使用 GitHub Actions 自动化 CI/CD 流程：

**工作流文件**: `.github/workflows/main.yml`

**自动化流程**:
1. 在主分支上的 push/pull_request 时触发
2. 检出代码
3. 配置 MSBuild
4. 编译 Release x64 版本
5. 生成发布标签
6. 创建 GitHub Release
7. 上传构建的 exe 文件
8. 保存构建工件（保留 30 天）

### 项目配置参考

| 选项 | 值 |
|------|-----|
| 项目名称 | minimfc |
| 版本 | 1.0.0.0 |
| C++ 标准 | 17 |
| 最低 CMake 版本 | 3.20 |
| 最低 Windows 版本 | 10.0 |
| Visual Studio 版本 | v143 (2022) |
| 字符编码 | UTF-8 |

### 扩展应用程序

为了扩展功能，你可以：

1. **添加新的菜单项**
   - 在 `main.rc` 中编辑菜单资源
   - 在 `main_frame.cpp` 中添加消息处理函数
   - 进行 DECLARE_MESSAGE_MAP 宏映射

2. **实现新的窗口类**
   - 从 `CWnd` 或 `CDialog` 继承
   - 添加到项目文件中
   - 从 `CMainFrame` 中实例化

3. **添加资源**
   - 编辑 `main.rc` 文件
   - 在 `resource.h` 中定义资源 ID
   - 在代码中引用资源

4. **自定义托盘行为**
   - 修改 `OnTrayNotify()` 处理新消息类型
   - 更改 `m_nid` 配置
   - 自定义上下文菜单内容

## 📄 许可证

本项目采用 **GNU General Public License v3.0** 许可证。

```
Copyright (C) 2025 mystique

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
```

详见 [LICENSE](LICENSE) 文件。

## 🤝 贡献

我们欢迎各种形式的贡献！你可以通过以下方式参与：

### 贡献方式

1. **报告 Bug**
   - 在 GitHub Issues 中详细描述问题
   - 包含重现步骤和系统信息

2. **提出功能建议**
   - 在 GitHub Discussions 中讨论想法
   - 为想法提供详细的用例说明

3. **提交代码**
   - Fork 本仓库
   - 创建功能分支 (`git checkout -b feature/amazing-feature`)
   - 提交变更 (`git commit -m 'Add amazing feature'`)
   - 推送到分支 (`git push origin feature/amazing-feature`)
   - 创建 Pull Request

### 代码规范

- 遵循 `.clang-format` 定义的代码风格
- 添加详细的代码注释和文档
- 确保代码编译时不产生警告
- 使用 C++17 标准，避免过时的 C++ 特性
- 测试所有特定平台的功能

### 提交指南

- 使用清晰、描述性的提交信息
- 每个提交只做一个逻辑改动
- 包含相关 Issue 编号（如果有）
- 在 PR 描述中解释更改的原因

## 📞 联系方式

- **项目维护者**: mystique
- **问题反馈**: GitHub Issues
- **讨论交流**: GitHub Discussions

## 🎓 学习资源

- [MFC 官方文档](https://docs.microsoft.com/en-us/cpp/mfc/)
- [Windows API 参考](https://docs.microsoft.com/en-us/windows/win32/api/)
- [C++17 标准参考](https://en.cppreference.com/w/cpp/17)
- [CMake 文档](https://cmake.org/documentation/)

## 📊 项目统计

- **主要语言**: C++
- **构建系统**: CMake + Visual Studio
- **代码行数**: ~500 行
- **许可证**: GPL v3
- **维护状态**: 积极维护

## 🙏 致谢

感谢所有贡献者和使用者的支持和反馈！

---

**最后更新**: 2025 年 1 月
**项目版本**: 1.0.0.0