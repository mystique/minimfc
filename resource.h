/**
 * @file resource.h
 * @brief 资源定义文件
 *
 * 本文件定义了应用程序中使用的各种资源ID，包括菜单项ID和图标ID。
 * 这些ID在资源脚本文件（.rc）中被引用，用于标识不同的用户界面元素。
 */

// 菜单资源ID定义
// 这些ID用于标识应用程序的主菜单和菜单项

/** @def ID_MENU
 * @brief 主菜单资源ID
 *
 * 标识应用程序的主菜单资源，对应菜单资源ID为101。
 * 此菜单包含应用程序的上下文菜单项，如显示/隐藏窗口、退出等。
 */
#define ID_MENU 101

/** @def ID_MENU_TOGGLE_WINDOW
 * @brief 切换窗口显示状态菜单项ID
 *
 * 标识菜单中的"切换窗口"菜单项，对应菜单项ID为102。
 * 用户选择此菜单项可以显示或隐藏应用程序的主窗口。
 */
#define ID_MENU_TOGGLE_WINDOW 102

/** @def ID_MENU_QUIT
 * @brief 退出应用程序菜单项ID
 *
 * 标识菜单中的"退出"菜单项，对应菜单项ID为103。
 * 用户选择此菜单项将关闭应用程序。
 */
#define ID_MENU_QUIT 103

// 图标资源ID定义
// 这些ID用于标识应用程序中使用的图标资源

/** @def MAIN_ICON
 * @brief 主图标资源ID
 *
 * 标识应用程序的主图标资源，对应图标资源ID为201。
 * 此图标用于应用程序的窗口标题栏、任务栏和系统托盘显示。
 */
#define MAIN_ICON 201
