

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <malloc.h>
#include <cmath>
#include <stdlib.h>


//#include "token_out.h"
#include "allCode.h"
//#include "Quadra_out.h"
#undef UNICODE
using namespace std;


void display_file(char* );
void open_file(HWND);
void AddMenus(HWND);
void create_window(HWND);
void case2_func();
void case3_func();
void case4_func();
void case5_func();
void case6_func();
void case7_func();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND codeTxt_dis, token_dis, Quadra_dis, optimize_dis, aimCode_dis, assem_dis, exptxt_dis, blank_dis, label, blank_button, txt_button, token_button, Quadra_button, optimize_button, aimCode_button, assem_button;
HMENU hMenu;



/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

string to_string(int i)
{
    string s="";
    stringstream ss;
    ss<<i;
    ss>>s;
    return s;
}

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
           _T("开学大三"),       /* Title Text */
           WS_OVERLAPPEDWINDOW|WS_SYSMENU, /* default window */
           35,       /* Windows decides the position */
           0,       /* where the window ends up on the screen */
           850,                 /* The programs width */
           560,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
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
    OPENFILENAME ofn;
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

    memset(fileName, 0, sizeof(fileName)/sizeof(char));
    strcpy(fileName, ofn.lpstrFile);
    display_file(ofn.lpstrFile);

}

//原来的addmenus
void AddMenus(HWND hwnd){
		hMenu = CreateMenu();

		// 文件栏的容器 初始化
		HMENU hFileMenu = CreateMenu();
		// 文件栏 弹出菜单
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "文件");
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) 801, "打开文件");
		AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线
				AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) 800, "关闭文件");
		AppendMenu(hFileMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线
		AppendMenu(hFileMenu, MF_STRING, (UINT_PTR) 802, "退出");

		// 编辑栏的容器 初始化
		HMENU hEditMenu = CreateMenu();
		// 编辑栏 弹出菜单
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, "编辑");
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR)803 , "生成TOKEN串");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR)804, "生成四元式");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR)805, "优化四元式");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR)806, "生成目标代码");
		AppendMenu(hEditMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);	//分割线
		AppendMenu(hEditMenu, MF_STRING, (UINT_PTR)807, "生成汇编代码");



		// 帮助栏的容器 初始化
		HMENU hHelpMenu = CreateMenu();
		// 帮助栏弹出菜单
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "帮助");
		AppendMenu(hHelpMenu, MF_STRING, (UINT_PTR)808, "关于");
		AppendMenu(hHelpMenu, MF_SEPARATOR, (UINT_PTR) NULL, NULL);
		AppendMenu(hHelpMenu, MF_STRING, (UINT_PTR)809, "Github主页");


		SetMenu(hwnd, hMenu);

}

//--------------------------------------------switch case_func()----------------------------------------------------------------
//原来的create_window()
void create_window(HWND hwnd) {
		AddMenus(hwnd);

		codeTxt_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						 WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
						5, 40, 200, 200, hwnd, NULL, NULL, NULL);

		token_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/  "",
						WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
						215, 40, 200, 200, hwnd, NULL, NULL, NULL);

		Quadra_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL ,
						425, 40, 200, 200, hwnd, NULL, NULL, NULL);

		optimize_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
                        WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
						5, 300, 200, 200, hwnd, NULL, NULL, NULL);

		aimCode_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
                        WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
						215, 300, 200, 200, hwnd, NULL, NULL, NULL);

		assem_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						 WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
						425, 300, 200, 200, hwnd, NULL, NULL, NULL);

		exptxt_dis = CreateWindow("EDIT", /*ES_AUTOVSCROLL*/ "",
						 WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
						635, 300, 200, 200, hwnd, NULL, NULL, NULL);

        blank_dis = CreateWindow("EDIT", //ES_AUTOVSCROLL
                                 "",
                         WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL,
                        635, 40, 200, 200, hwnd, NULL, NULL, NULL);

		txt_button = CreateWindow("BUTTON", 	"打开文件",
						WS_VISIBLE | WS_CHILD,
						5, 15, 200, 20,
						hwnd, (HMENU)811, NULL, NULL);

		token_button = CreateWindow("BUTTON",	"生成Token序列",
						WS_VISIBLE | WS_CHILD,
						215, 15, 200, 20,
						hwnd, (HMENU)812, NULL, NULL);

		Quadra_button = CreateWindow("BUTTON",	"生成四元式",
						WS_VISIBLE | WS_CHILD,
						425, 15, 200, 20,
						hwnd, (HMENU)813, NULL, NULL);

		optimize_button = CreateWindow("BUTTON",	"优化四元式",
						WS_VISIBLE | WS_CHILD,
						5, 265, 200, 20,
						hwnd, (HMENU)814, NULL, NULL);

		aimCode_button = CreateWindow("BUTTON",	"生成目标代码",
						WS_VISIBLE | WS_CHILD,
						215, 265, 200, 20,
						hwnd, (HMENU)815, NULL, NULL);

		assem_button = CreateWindow("BUTTON",	"生成汇编",
						WS_VISIBLE | WS_CHILD,
						425, 265, 200, 20,
						hwnd, (HMENU)816, NULL, NULL);


        blank_button = CreateWindow("BUTTON",  "生成符号表",
                        WS_VISIBLE | WS_CHILD,
                        635, 15, 200, 20,
                        hwnd, (HMENU) 817, NULL, NULL);

		label = CreateWindow("STATIC",	"日志",
						WS_VISIBLE | WS_CHILD|ES_CENTER,
						635, 265,200,20,
						hwnd, NULL, NULL, NULL);
}


string token_string[1000] = {};
int string_int=0;

void case2_func() {
    case2();
    //cout<<"for1"<<endl;
    token_string[string_int]="";

    for(int i=0; i<Token.size(); i++) {
        //cout<<'<'<<Token[i].Table_cat<<", "<<Token[i].Table_key<<'>'<<endl;
        char Table_cat_temp[4]="";
        Table_cat_temp[0]=Token[i].Table_cat;
        string str_1 = Table_cat_temp;
        string str_2="";
        deserve(str_2, Token[i].Table_key);
        //cout<<"str_2: "<<str_2<<endl;
        if(i==0)
            token_string[string_int]="<"+str_1+", "+str_2+">"+"\x0d\x0a";
        else
            token_string[string_int]=token_string[string_int]+"<"+str_1+", "+str_2+">"+"\x0d\x0a";
    }
    //cout<<"for2"<<endl;
    cout<<token_string[string_int].length()<<endl;
    SetWindowText(token_dis, token_string[string_int].c_str());
    //cout<<"astring_int: "<<string_int<<endl;
    string_int++;
    //cout<<"bstring_int: "<<string_int<<endl;
    SetWindowText(exptxt_dis,"Token串生成成功");


}


void case3_func() {

    string error="";
    string err_1="";

    //Quadra.clear();
    curlin_num=1;
    Stack_Address=-1;
    Token_Address=0;
    inter_t=0;
    ge=0;
    Synbl_Address=0;
    Addr=0;

    //line_num.clear();
    token token_temp;
    token_temp.setToken('#', 100);
    Token.push_back(token_temp);
    PUSH(100); //100代表#
    PUSH(51); //51代表E
    NEXT(); //

    while(Stack_Address>=0){

        POP();

        if(fx>=0&&fx<=33){

            if(fx==Token_to_code(Current_Token_cat,Current_Token_key)){

                NEXT();
                continue;

            }
            else{
                //cout<<"Error111"<<endl;
                //::MessageBox(NULL, "Error111", "Error", MB_OK);
                err_1 = err_1 + "语法分析失败"+"\x0d\x0a"+"在第"+to_string(line_num[Token_Address-2])+"行“"+str[Token_Address-2]+"”下一处出现错误";
                //error += err_2+"\x0d\x0a"+err_3+"\x0d\x0a";
                error += err_1;
                break;
                //err_4="语法分析失败"+"\x0d\x0a"+"在第"+to_string(line_num[Token_Address-2])+"行“"+str[Token_Address-2]+"”下一处出现错误";
            }
        }
        else if((fx>=51&&fx<=74)||(fx>=101&&fx<=127)){////////////////////////////
            if(Search_LL1_Excel()){

                continue;

            }
            else{

               err_1= err_1 +"语法分析失败"+"\x0d\x0a"+"在第"+to_string(line_num[Token_Address-2])+"行“"+str[Token_Address-2]+"”下一处出现错误";
                //error += err_2+"\x0d\x0a"+err_3+"\x0d\x0a";
                error += err_1;
                break;
            }

        }
        else {
            err_1= err_1 +"语法分析失败"+"\x0d\x0a"+"在第"+to_string(line_num[Token_Address-2])+"行“"+str[Token_Address-2]+"”下一处出现错误";
            error += err_1;
            break;
        }
    }

    if(err_2!="")
        error += err_2+"\x0d\x0a";
    if(err_3!="")
        error += err_3+"\x0d\x0a";

    vector<quadra> Quadra_q;
    for(int j=0;j<ge;j+=4){
        quadra q;
        q.op=destination[j];
        q.B.name=destination[j+1];
        q.C.name=destination[j+2];
        q.A.name=destination[j+3];
        Quadra_q.push_back(q);
    }

    string Quadra_string="";
    for(int i=0; i<Quadra_q.size(); i++) {
       if(i==0)
            Quadra_string="("+Quadra_q[i].op+", "+Quadra_q[i].B.name+", "+Quadra_q[i].C.name+", "+Quadra_q[i].A.name+")"+"\x0d\x0a";
        else
            Quadra_string=Quadra_string+"("+Quadra_q[i].op+", "+Quadra_q[i].B.name+", "+Quadra_q[i].C.name+", "+Quadra_q[i].A.name+")"+"\x0d\x0a";
    }
    SetWindowText(Quadra_dis, Quadra_string.c_str());




if(error=="")
        SetWindowText(exptxt_dis,"语法分析成功");
    else
        SetWindowText(exptxt_dis, error.c_str());
}

string case4_string="", case5_string="", case6_string="", case7_string="";
void case4_func() {
    allCode allcode = getAll();
    case4_string=allcode.res.opti;

    for(int r=0; r<Quadra.size(); r++) {
        cout<<"Quadra: "<<Quadra[r].op<<", "<<Quadra[r].B.name<<", "<<Quadra[r].C.name<<", "<<Quadra[r].A.name<<endl;
    }

    case5_string=allcode.res.aimCode;
    case6_string=allcode.res.res;
    case7_string="synbl(符号表): \x0d\x0a";
    for(int j=0;j<Synbl_Address;j++){
        string temp_1="";
        deserve(temp_1, allcode.synbl.addr[j]);
        string temp_2="";
        if(allcode.synbl.IsAct[j]==true)
            temp_2="true";
        else
            temp_2="false";
        case7_string=case7_string+"("+allcode.synbl.name[j]+", "
            +allcode.synbl.cat[j]+", "+allcode.tapel.tval[allcode.synbl.typ[j]]+", "+temp_1+", "+temp_2+")"+"\x0d\x0a";
    }

    case7_string=case7_string+"\x0d\x0a"+"afinl(数组表): \x0d\x0a";
    for(int j=0;j<AINFL_Address;j++){
        string ain_temp1="0";
        string ain_temp2="";
        deserve(ain_temp2, Clen[j]);
        case7_string=case7_string+"("+ain_temp1+", "+Up[j]+", "+Ctp[j]+", "+ain_temp2+")"+"\x0d\x0a";
    }

    case7_string=case7_string+"\x0d\x0a"+"rinfl(结构体表): \x0d\x0a";
    for(int j=0;j<RINFL_Address;j++){
        string rin_temp1="";
        deserve(rin_temp1, OFF[j]);
        if(rin_temp1=="")
            rin_temp1="0";
        case7_string=case7_string+"("+ID[j]+", "+rin_temp1+", "+TP[j]+")"+"\x0d\x0a";
    }



    SetWindowText(optimize_dis, case4_string.c_str());
    SetWindowText(exptxt_dis,"优化生成成功");
}

void case5_func() {
    SetWindowText(aimCode_dis, case5_string.c_str());
    SetWindowText(exptxt_dis,"目标代码生成成功");
}

void case6_func() {
    SetWindowText(assem_dis, case6_string.c_str());
    SetWindowText(exptxt_dis,"汇编生成成功");
}

void case7_func() {
    SetWindowText(blank_dis, case7_string.c_str());
    SetWindowText(exptxt_dis,"符号表生成成功");
}

//--------------------------------------------switch case_func()----------------------------------------------------------------


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            create_window(hwnd);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case 801:
                    open_file(hwnd);
                    MessageBox(hwnd, "   打开文件成功  ", "消息", MB_OK | MB_ICONQUESTION);
                    break;
                case 802:
                    int val;
                    val = MessageBox(hwnd, "您是否确定退出？", "退出", MB_YESNO | MB_ICONEXCLAMATION);
                    if (val==IDYES)
                    {
                        PostQuitMessage (0);
                    }
                    break;
                case 803:
                    MessageBox(hwnd, "    case2_func(),正在生成Token", "消息", MB_OK | MB_ICONQUESTION);
                    case2_func();

                    break;

                case 804:
                    MessageBox(hwnd, "    case3_func()", "消息", MB_OK | MB_ICONQUESTION);
                    case3_func();
                    break;
                case 805:

                     MessageBox(hwnd, "   case4_func()", "帮助", MB_OK | MB_ICONQUESTION);
                     //
                     case4_func();
                    break;
                case 806:
                    MessageBox(hwnd, "    case5_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case5_func();
                    break;
                case 807:
                    MessageBox(hwnd, "    case6_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case6_func();
                    break;
                case 808:
                    MessageBox(hwnd, "    此编译器支持生成Token串、符号表、中间代码，优化并生成目标代码、汇编代码的编译功能。", "帮助", MB_OK | MB_ICONQUESTION);
                    break;
                case 809:
                    system("start https://github.com/The-2020-Compiler-Project/Kai-Xue-Da-San");
                    break;
                case 811:
                    open_file(hwnd);
                    break;
                case 812:
                    MessageBox(hwnd, "    正在运行case2_func() ", "检测", MB_OK | MB_ICONQUESTION);
                    case2_func();
                    MessageBox(hwnd, " 成功", "消息", MB_OK | MB_ICONQUESTION);
                    break;
                case 813:
                    MessageBox(hwnd, "    case3_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case3_func();
                    break;
                case 814:
                    {
                        MessageBox(hwnd, "  case4_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case4_func();
                    }
                    break;
                case 815:
                    MessageBox(hwnd, "    case5_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case5_func();
                    break;
                case 816:
                    MessageBox(hwnd, "    case6_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case6_func();
                    break;
                case 817:
                    MessageBox(hwnd, "   case7_func()", "帮助", MB_OK | MB_ICONQUESTION);
                    case7_func();
                    break;
            }
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
