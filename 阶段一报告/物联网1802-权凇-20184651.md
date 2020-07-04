# 用<windows.h>可视化界面实现

**主要函数如下所示：**

```c++
#include<windows.h>
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)  // 主函数实现调用
void display_file(char* path)     //文本内容显示
void open_file(HWND hwnd)    //打开文件
void AddMenus(HWND hwnd)    //添加菜单
void create_window(HWND hwnd)  //创建框架
```

**详细代码如下：**

```c++
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#undef UNICODE
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND codeTxt_dis, token_dis, Quadra_dis, optimize_dis, aimCode_dis, assem_dis, exptxt_dis, blank_dis, label, blank_button, txt_button, token_button, Quadra_button, optimize_button, aimCode_button, assem_button;
HMENU hMenu;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("开学大三组"),       /* Title Text */
           WS_SYSMENU, /* default window */
           0,       /* Windows decides the position */
           0,       /* where the window ends up on the screen */
           640,                 /* The programs width */
           500,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void open_file(HWND hwnd) {

}

void AddMenus(HWND hwnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();

    AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) 4, "打开文件");
    AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) 5, "退出");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "文件");
    AppendMenu(hMenu, MF_STRING, (UINT_PTR) 6, "帮助");

    SetMenu(hwnd, hMenu);
}

void create_window(HWND hwnd) {
            AddMenus(hwnd);
            codeTxt_dis = CreateWindow("EDIT", //ES_AUTOVSCROLL
                                   "",
                                   WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
                                   5, 40, 200, 400,
                                   hwnd, NULL, NULL, NULL);
            token_dis = CreateWindow("EDIT", //ES_AUTOVSCROLL
                                 "",
                                 WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
                                 215, 40, 200, 400,
                                 hwnd, NULL, NULL, NULL);

            Quadra_dis = CreateWindow("EDIT", //ES_AUTOVSCROLL
                                 "",
                                 WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
                                 425, 40, 200, 400,
                                 hwnd, NULL, NULL, NULL);
            txt_button = CreateWindow("BUTTON",
                                      "打开文件",
                                      WS_VISIBLE | WS_CHILD,
                                      20, 15, 100, 20,
                                      hwnd, (HMENU) 1, NULL, NULL);
            token_button = CreateWindow("BUTTON",
                                        "生成Token序列",
                                        WS_VISIBLE | WS_CHILD,
                                        230, 15, 100, 20,
                                        hwnd, (HMENU) 2, NULL, NULL);
            Quadra_button = CreateWindow("BUTTON",
                                        "生成四元式",
                                        WS_VISIBLE | WS_CHILD,
                                        440, 15, 100, 20,
                                        hwnd, (HMENU) 3, NULL, NULL);
}



LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            create_window(hwnd);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case 1:
                    open_file(hwnd);
                    break;

                case 2:
                    SetWindowText(exptxt_dis,"Token串生成成功");
                    break;

                case 3:
                    SetWindowText(exptxt_dis,"四元式生成成功");
                    break;
                case 4:
                    open_file(hwnd);
                    break;
                case 5:
                    int val;
                    val = MessageBox(hwnd, "确定退出？", "退出", MB_YESNO | MB_ICONEXCLAMATION);
                    if (val==IDYES)
                    {
                        PostQuitMessage (0);
                    }
                    break;
                case 6:
                    MessageBox(hwnd, "此编译器目前只能实现词法分析和语法分析功能。", "帮助", MB_OK | MB_ICONQUESTION);
                    break;
            }
        break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

```

**目前的界面情况如下：**

![截图1](https://kwon-bucket.oss-cn-beijing.aliyuncs.com/img/202007/截图1.png)

![截图2](https://kwon-bucket.oss-cn-beijing.aliyuncs.com/img/202007/截图2.png)

![截图3](https://kwon-bucket.oss-cn-beijing.aliyuncs.com/img/202007/截图3.png)

**工作区**：默认生成界面在屏幕左上角。

![截图4](https://kwon-bucket.oss-cn-beijing.aliyuncs.com/img/202007/截图4.png)

学习过程：

+ 创建窗口用CreateWindow来定义和调用。

```c++
//CreateWindow函数的参数介绍：
HWND CreateWindow(
  LPCTSTR lpClassName,          //Windows窗口中预定义的控件结构体，包括：BUTTON（按钮），EDIT（文本框），LISTBOX（列表），MDICLIENT（子窗口），SCROLLBAR（滚动条），RICHEDIT（富文本），STATIC（静态控件）；
  LPCTSTR lpWindowName,         //窗口控件中显示的内容，即Caption属性；
  DWORD dwStyle,                //控件样式，包括：WS_CHILD | WS_VISIBLE | WS_BORDER，还可以根据具体控件类型添加相应样式
  int x,                        //窗口或控件左上角（X,Y）的X坐标
  int y,                        //窗口或控件左上角（X,Y）的Y坐标
  int nWidth,                   //窗口或控件的宽度
  int nHeight,                  //窗口或控件的高度
  HWND hWndParent,              //父窗口句柄
  HMENU hMenu,                  //菜单或者子窗口或控件的ID
  HANDLE hInstance,             //实例
  PVOID lpParam                 //
);
```

```c++
/* 创建窗口 */
hwnd = CreateWindow (   szAppName, TEXT ("输出字符串演示"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, NULL ) ;
```

> 第1个参数：szAppName是字符串变量，如TEXT ("MyWindow")，表示为程序名称；
>
> 第2个参数：窗口标题名称；
>
> 第3个参数：窗口样式；
>
> 第4个参数：窗口左上角（X,Y）的X坐标，CW_USEDEFAULT表示使用缺省值；
>
> 第5个参数：窗口左上角（X,Y）的Y坐标，CW_USEDEFAULT表示使用缺省值；
>
> 第6个参数：窗口宽度，CW_USEDEFAULT表示使用缺省值；
>
> 第7个参数：窗口高度，CW_USEDEFAULT表示使用缺省值；
>
> 第8个参数：如果有父窗口，则是父窗口句柄，NULL表示没有父窗口；
>
> 第9个参数：如果有菜单，则是菜单的ID，NULL表示没有菜单；
>
> 第10个参数：执行实例代码；



+ CALLBACK函数

使用回调函数实际上就是在调用某个函数(通常是API函数)时，将自己的一个函数(这个函数为回调函数)的地址作为参数传递给那个函数。而那个函数在需要的时候,利用传递的地址调用回调函数，这时可以利用这个机会在回调函数中处理消息或完成一定的操作。 至于如何定义回调函数,跟具体使用的API函数有关，一般在帮助中有说明回调函数的参数和返回值等。C+ +中一般要求在回调函数前加CALLBACK,这主要是说明该函数的调用方式。DialogBox的回调函数实际 上是个窗口过程，用来处理所有消息。



**主要遇到的问题：**

+ WinMain函数里面，WindowProcedure函数里面，各个参数的用法，需要有所了解
+ 回调函数的具体用法
+ 滚动条，列表框，按钮的用法
+ 如何在左上角加一个小菜单？用AppendMenu实现，并且函数中的参数数字要对应到case当中。
+ 对坐标数据的调试，使界面可视化程度较好



**参考学习的网站如下：**

https://blog.csdn.net/sesiria/article/details/51817740?utm_medium=distribute.pc_relevant.none-task-blog-baidujs-5

https://www.cnblogs.com/petrol/p/9795401.html

https://blog.csdn.net/wmnmtm/article/details/82923311

https://blog.csdn.net/aixintianshideshouhu/article/details/88383587

https://blog.csdn.net/weixin_36929359/article/details/54342859