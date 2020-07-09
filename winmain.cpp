#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>


#include "ControlNumber.h"
#include "Controls.h"

#undef UNICODE
using namespace std;

/* Declare Windows procedure */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/* 函数声明 */ 
void open_file(HWND); 
void display_file(char*);
//void save_file(HWND); 
void AddMenus(HWND);


// 全局变量 
HMENU hMenu; 			// 主窗口的菜单 
HINSTANCE hInst;		

/* Make the class name into a global variable */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,  HINSTANCE hPrevInstance,  LPSTR lpszArgument,  int nCmdShow){
	HWND hwnd; /* This is the handle for our window */
	MSG messages; /* Here messages to the application are saved*/
	WNDCLASSEX wincl; /* Data structure for the windowclass */
	hInst = hThisInstance;
	
	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure; /* This function is calledby windows */

	wincl.style = CS_DBLCLKS; /* Catch double-clicks */
	wincl.cbSize = sizeof (WNDCLASSEX);
	
	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL; /* No menu */
	wincl.cbClsExtra = 0; /* No extra bytes after thewindow class */
	wincl.cbWndExtra = 0; /* structure or the windowinstance */

	/* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+1;

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx (&wincl))
		return 0;
	
	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx (0, /* Extended possibilites for variation */
				 szClassName, /* Classname */
			_T("开学大三组"), /* Title Text */
		WS_OVERLAPPEDWINDOW , /* default window */
						   0, /* Windows decides the position */
						   0, /* where the window ends up on the screen */
						 850, /* The programs width */
						 600, /* and height in pixels */
				HWND_DESKTOP, /* The window is a child-window to desktop*/
						NULL, /* No menu */
			   hThisInstance, /* Program Instance handler */
						NULL /* No Window Creation data */
							);
							
	/* Make the window visible on the screen */
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
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

void display_file(char* path) {
    FILE* file;
    file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    int _size = ftell(file);
    rewind(file);
    char* data = new char(_size+1);
    fread(data, _size, 1, file);
    data[_size] = '\0';
    fclose(file);
    SetWindowText(codeTxt_dis, data);
}

void open_file(HWND hwnd) {
	OPENFILENAME ofname;
    char file_name[100];

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    int flag = GetOpenFileName(&ofn);

    if (flag)
        SetWindowText(exptxt_dis, "文件打开成功");
    else
        SetWindowText(exptxt_dis, "文件打开失败");
	char fileName[100];
    memset(fileName, 0, sizeof(fileName)/sizeof(char));
    strcpy(fileName, ofn.lpstrFile);
    display_file(ofn.lpstrFile);
}

	
void AddMenus(HWND hwnd){
		hMenu = CreateMenu();
		
		// 文件栏的容器 初始化 
		HMENU hFileMenu = CreateMenu();
		// 文件栏 弹出菜单 
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "文件");
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) /**/MENU_OPENFILE/**/, "打开文件");	
		AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线 
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) MENU_SAVEFILE/**/, "另存为");
		AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线 
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) MENU_EXIT, "退出");

		// 编辑栏的容器 初始化 
		HMENU hEditMenu = CreateMenu();
		// 编辑栏 弹出菜单 
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, "编辑");
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_TOKEN , "生成TOKEN串");	
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_QUADRA, "生成四元式");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_BETTER, "优化四元式");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_AIM, "生成目标代码");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_ASSEMB, "生成汇编代码");
		


		// 帮助栏的容器 初始化 
		HMENU hHelpMenu = CreateMenu();
		// 帮助栏弹出菜单 
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "帮助");
		AppendMenu(hHelpMenu, MF_STRING, (UINT_PTR) MENU_ABOUT, "关于");
		AppendMenu(hHelpMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);
		AppendMenu(hHelpMenu, MF_STRING, (UINT_PTR) MENU_GITHUB, "Github主页");
		
		
		SetMenu(hwnd, hMenu);
		
}

void create_window(HWND hwnd) {
		AddMenus(hwnd);
		
		codeTxt_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						//WS_BORDER | 
						WS_VISIBLE | 
						//WS_CAPTION|
						WS_SIZEBOX|
						WS_VSCROLL | 
						//WS_POPUP | 
						WS_CHILD|
						//WS_OVERLAPPEDWINDOW |
						ES_AUTOVSCROLL | 
						ES_AUTOHSCROLL |
						ES_MULTILINE 
						//WS_HSCROLL|
						,
						5, 40, 200, 200, hwnd, hMenu, NULL, NULL);
		
		token_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/  "",
						WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL|WS_SIZEBOX,
						215, 40, 200, 200, hwnd, NULL, NULL, NULL);
		
		Quadra_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL |WS_SIZEBOX,
						425, 40, 200, 200, hwnd, NULL, NULL, NULL);
	 
		optimize_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL|WS_THICKFRAME|WS_CHILD ,
						5, 300, 200, 200, hwnd, NULL, NULL, NULL);
		
		aimCode_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL|WS_THICKFRAME|WS_CHILD ,
						215, 300, 200, 200, hwnd, NULL, NULL, NULL);
		
		assem_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL|WS_THICKFRAME|WS_CHILD ,
						425, 300, 200, 200, hwnd, NULL, NULL, NULL);
		
		exptxt_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL|WS_THICKFRAME|WS_CHILD ,
						635, 40, 200, 460, hwnd, NULL, NULL, NULL);

		
		txt_button = CreateWindow("BUTTON", 	"打开文件", 
						WS_VISIBLE | WS_CHILD,
						5, 15, 200, 20,
						hwnd, (HMENU) BUTTON_ORIGION, NULL, NULL);

		token_button = CreateWindow("BUTTON",	"生成Token序列",
						WS_VISIBLE | WS_CHILD,
						215, 15, 200, 20,
						hwnd, (HMENU) BUTTON_TOKEN, NULL, NULL);

		Quadra_button = CreateWindow("BUTTON",	"生成四元式",
						WS_VISIBLE | WS_CHILD,
						425, 15, 200, 20,
						hwnd, (HMENU) BUTTON_QUADRA, NULL, NULL);
						
		optimize_button = CreateWindow("BUTTON",	"优化四元式",
						WS_VISIBLE | WS_CHILD,
						5, 265, 200, 20,
						hwnd, (HMENU) BUTTON_BETTER, NULL, NULL);

		aimCode_button = CreateWindow("BUTTON",	"生成目标代码",
						WS_VISIBLE | WS_CHILD,
						215, 265, 200, 20,
						hwnd, (HMENU) BUTTON_AIM, NULL, NULL);
						
		assem_button = CreateWindow("BUTTON",	"生成汇编",
						WS_VISIBLE | WS_CHILD,
						425, 265, 200, 20,
						hwnd, (HMENU) BUTTON_ASSEMB, NULL, NULL);
						
		label = CreateWindow("BUTTON",	"日志",
						WS_VISIBLE | WS_CHILD,
						635, 15, 200, 20,
						hwnd, (HMENU) LABEL_LOG, NULL, NULL);		
						
						
						
}
		
		
LRESULT CALLBACK WindowProcedure ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
		{
			case WM_CREATE:
				create_window(hwnd);
					break;
					
			case WM_COMMAND:
					{
						int wmId = LOWORD(wParam);
						switch(wmId) {
							/* 菜单栏的事件 */
							case MENU_OPENFILE:
								open_file(hwnd); 	// 打开文件的函数 
								break; 
							case MENU_SAVEFILE:
								break;
							case MENU_EXIT:
								{
									int val;
										val = MessageBox(hwnd, "确定退出？", "退出", MB_YESNO | MB_ICONEXCLAMATION);
									if (val==IDYES){
											PostQuitMessage (0);
									}
										break;
								} 
								break;
							case MENU_TOKEN:
								break;
							case MENU_QUADRA:
								break;
							case MENU_BETTER:
								break;	
							case MENU_AIM:
								break;
							case MENU_ASSEMB:
								break;
							case MENU_ABOUT:
								MessageBox(hwnd, "此编译器目前只能实现词法分析和语法分析功能。", "帮助", MB_OK | MB_ICONQUESTION);
								break;
							case MENU_GITHUB:
								system("start https://github.com/The-2020-Compiler-Project/Kai-Xue-Da-San");
								break;
								
							/* 按钮事件 */ 
							case BUTTON_ORIGION://打开源文件 
								break;
							case BUTTON_TOKEN: 
								break;
							case BUTTON_QUADRA :
								break;	
							case BUTTON_BETTER :
								break;
							case BUTTON_AIM :
								break;
							case BUTTON_ASSEMB:
								break;
							case LABEL_LOG:
								break;
								
						}
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



