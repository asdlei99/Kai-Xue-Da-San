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

/* �������� */ 
void open_file(HWND); 
void display_file(char*);
//void save_file(HWND); 
void AddMenus(HWND);


// ȫ�ֱ��� 
HMENU hMenu; 			// �����ڵĲ˵� 
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
			_T("��ѧ������"), /* Title Text */
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
        SetWindowText(exptxt_dis, "�ļ��򿪳ɹ�");
    else
        SetWindowText(exptxt_dis, "�ļ���ʧ��");
	char fileName[100];
    memset(fileName, 0, sizeof(fileName)/sizeof(char));
    strcpy(fileName, ofn.lpstrFile);
    display_file(ofn.lpstrFile);
}

	
void AddMenus(HWND hwnd){
		hMenu = CreateMenu();
		
		// �ļ��������� ��ʼ�� 
		HMENU hFileMenu = CreateMenu();
		// �ļ��� �����˵� 
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "�ļ�");
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) /**/MENU_OPENFILE/**/, "���ļ�");	
		AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//�ָ��� 
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) MENU_SAVEFILE/**/, "���Ϊ");
		AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//�ָ��� 
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) MENU_EXIT, "�˳�");

		// �༭�������� ��ʼ�� 
		HMENU hEditMenu = CreateMenu();
		// �༭�� �����˵� 
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, "�༭");
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_TOKEN , "����TOKEN��");	
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//�ָ��� 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_QUADRA, "������Ԫʽ");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//�ָ��� 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_BETTER, "�Ż���Ԫʽ");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//�ָ��� 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_AIM, "����Ŀ�����");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//�ָ��� 
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR) MENU_ASSEMB, "���ɻ�����");
		


		// ������������ ��ʼ�� 
		HMENU hHelpMenu = CreateMenu();
		// �����������˵� 
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "����");
		AppendMenu(hHelpMenu, MF_STRING, (UINT_PTR) MENU_ABOUT, "����");
		AppendMenu(hHelpMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);
		AppendMenu(hHelpMenu, MF_STRING, (UINT_PTR) MENU_GITHUB, "Github��ҳ");
		
		
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

		
		txt_button = CreateWindow("BUTTON", 	"���ļ�", 
						WS_VISIBLE | WS_CHILD,
						5, 15, 200, 20,
						hwnd, (HMENU) BUTTON_ORIGION, NULL, NULL);

		token_button = CreateWindow("BUTTON",	"����Token����",
						WS_VISIBLE | WS_CHILD,
						215, 15, 200, 20,
						hwnd, (HMENU) BUTTON_TOKEN, NULL, NULL);

		Quadra_button = CreateWindow("BUTTON",	"������Ԫʽ",
						WS_VISIBLE | WS_CHILD,
						425, 15, 200, 20,
						hwnd, (HMENU) BUTTON_QUADRA, NULL, NULL);
						
		optimize_button = CreateWindow("BUTTON",	"�Ż���Ԫʽ",
						WS_VISIBLE | WS_CHILD,
						5, 265, 200, 20,
						hwnd, (HMENU) BUTTON_BETTER, NULL, NULL);

		aimCode_button = CreateWindow("BUTTON",	"����Ŀ�����",
						WS_VISIBLE | WS_CHILD,
						215, 265, 200, 20,
						hwnd, (HMENU) BUTTON_AIM, NULL, NULL);
						
		assem_button = CreateWindow("BUTTON",	"���ɻ��",
						WS_VISIBLE | WS_CHILD,
						425, 265, 200, 20,
						hwnd, (HMENU) BUTTON_ASSEMB, NULL, NULL);
						
		label = CreateWindow("BUTTON",	"��־",
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
							/* �˵������¼� */
							case MENU_OPENFILE:
								open_file(hwnd); 	// ���ļ��ĺ��� 
								break; 
							case MENU_SAVEFILE:
								break;
							case MENU_EXIT:
								{
									int val;
										val = MessageBox(hwnd, "ȷ���˳���", "�˳�", MB_YESNO | MB_ICONEXCLAMATION);
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
								MessageBox(hwnd, "�˱�����Ŀǰֻ��ʵ�ִʷ��������﷨�������ܡ�", "����", MB_OK | MB_ICONQUESTION);
								break;
							case MENU_GITHUB:
								system("start https://github.com/The-2020-Compiler-Project/Kai-Xue-Da-San");
								break;
								
							/* ��ť�¼� */ 
							case BUTTON_ORIGION://��Դ�ļ� 
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



