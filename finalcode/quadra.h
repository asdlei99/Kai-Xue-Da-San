
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
#include "token_out.h"

using namespace std;

class node {			//四元式的A B C位置的数据类型
public:
	string name;		//标识符名称
	bool IsAct;				//活跃信息
};

class quadra {		//每一条四元式的数据类型 (带活跃信息的)
public:
	int state = 0;		//块信息
	string op;		//op位置
	node B;			//B位置
	node C;			//C位置
	node A;			//A位置
};

class AimCodeunit {
public:
	string code;	//目标代码
	int count;		//标号
};

vector<quadra> Quadra; //四元式
int QT_num;		//四元式计数器
Synbl SYMBL=SYNBL;	//活跃信息表
int SY_num = 0;	//活跃信息表计数器
vector<AimCodeunit> AimCode;//目标代码容器
vector<int> SEM;				//SEM栈
//vector<nodeunit> Quater; //原先不带活跃信息的四元式

string str1[13]={"=", "*", "+", ">", "if", "=", "el", "=", "ie"};
string str2[13]={"2", "2", "t1", "b", "t2", "b", "_", "a", "_"};
string str3[13]={"_", "a", "4", "a", "_", "_", "_", "_", "_"};
string str4[13]={"a", "t1", "b", "t2", "_", "flag", "_", "flag", "_"};


//(w, B, C, A)
//w: <, ==, <=, >=, !=, +, -, *, /, ^, &, |, &&, ||

string OpToAss(string op) {
	if (op == "&&" || op == "&") {
		return "AND";
	}
	if (op == "||" || op == "|") {
		return "OR";
	}
	if (op == "^") {
		return "SQRT";
	}
	if (op == "~") {
		return "NOT";
	}
	if (op == ">") {
		return "GT";
	}
	if (op == "<") {
		return "LT";
	}
	if (op == "<=") {
		return "LE";
	}
	if (op == ">=") {
		return "GE";
	}
	if (op == "+") {
		return "ADD";
	}
	if (op == "-") {
		return "SUB";
	}
	if (op == "*") {
		return "MUL";
	}
	if (op == "/") {
		return "DIV";
	}
	return 0;
}

void OutputAss() {
	int state_temp = 0;		//块计数
	int Aim_count = 1; //标号计数 计现在有多少行汇编代码
	AimCodeunit AimTemp;//为AimCode vector作临时赋值用
						//strstream ss;		//int转字符串用
	string s_temp;
	node RNode;		//寄存器描述表
	RNode.name = " ";
	node SY_tem; //构造符号表时使用；
	for(unsigned int i = 0; i < Quadra.size(); i++) {

		if(Quadra[i].state != state_temp) {	//如果进入了下一块，就把RNode变为空
            RNode.name = " ";
			state_temp++;
		}


		if(Quadra[i].op == "+" || Quadra[i].op == "-" || Quadra[i].op == "*"
			|| Quadra[i].op == "/" || Quadra[i].op == "<" || Quadra[i].op == ">"
			|| Quadra[i].op == "<=" || Quadra[i].op == ">=") { // + - * / < >

			if (RNode.name == " ") {
				//cout << "LD    R, " << Quadra[i].B.name << endl;
				AimTemp.code = "LD    R, " + Quadra[i].B.name; //LD R, B
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;
				//R已存
				//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].C.name << endl;
				AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].C.name; //OP R, C
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;
			}
			else if (RNode.name == Quadra[i].B.name) {
				if (Quadra[i].B.IsAct) {
					//cout << "ST    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i].B.name; //ST R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
					//R已存
					//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].C.name << endl;
					AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].C.name; //OP R, C
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
                    //R已存
					//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].C.name << endl;
					AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].C.name; //OP R, C
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			else if (RNode.name == Quadra[i].C.name && (Quadra[i].op == "+" || Quadra[i].op == "*")) {
				if (Quadra[i].C.IsAct) {
					//cout << "ST    R, " << Quadra[i].C.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i].C.name; //ST R, C
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
					//R已存
					//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].B.name << endl;
					AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].B.name; //OP R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
                    //R已存
					//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].B.name << endl;
					AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].B.name; //OP R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			else {
				if (RNode.IsAct) {
					//cout << "ST    R, " << RNode.name << endl;
					AimTemp.code = "ST    R, " + RNode.name; //ST R, R.name
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name; //LD R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
					//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].C.name << endl;
					AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].C.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name; //LD R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
					//cout << OpToAss(Quadra[i].op) << "    R, " << Quadra[i].C.name << endl;
					AimTemp.code = OpToAss(Quadra[i].op) + "    R, " + Quadra[i].C.name; //OP R, C
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			RNode.name = Quadra[i].A.name;
			RNode.IsAct = Quadra[i].A.IsAct;
		}



		if(Quadra[i].op == "=") {
			if(RNode.name == " ") {
				//cout << "LD    R, " << Quadra[i].B.name << endl;
				AimTemp.code = "LD    R, " + Quadra[i].B.name; //LD R, B
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;
			}
			else if(RNode.name == Quadra[i].B.name) {
				//cout << "ST    R, " << Quadra[i].B.name << endl;
				if(Quadra[i].B.IsAct) {
                    //cout << "ST    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i].B.name; //ST R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			else {
				if(RNode.IsAct) {
					//cout << "ST    R, " << RNode.name << endl;
					AimTemp.code = "ST    R, " + RNode.name; //ST R, r.name
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name; //LD R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name; //LD R, B
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			RNode.name = Quadra[i].A.name;
			RNode.IsAct = Quadra[i].A.IsAct;
		}

		if(Quadra[i].op == "if") {
			if(RNode.name == " ") {
				//cout << "LD    R, " << Quadra[i].B.name << endl;
				AimTemp.code = "LD    R, " + Quadra[i].B.name;
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;
				//cout << "FJ    R, _" << endl;
				AimTemp.code = "FJ    R, _";
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);

				Aim_count++;
				SEM.push_back(AimCode.size());
			}
			if(RNode.name == Quadra[i].B.name) {
				if(Quadra[i].B.IsAct) {
					//cout << "ST    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				SEM.push_back(AimCode.size());
				RNode.name = " ";
			}
			else if(RNode.name != Quadra[i].B.name) {
				if(RNode.IsAct) {
					//cout << "ST    R, " << RNode.name << endl;
					AimTemp.code = "ST    R, " + RNode.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
					//cout << "LD    R, " << Quadra[i].B.name;
					AimTemp.code = "LD    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				SEM.push_back(AimCode.size());
				RNode.name = " ";
			}
		}

		if(Quadra[i].op == "el") {
			if(RNode.name == Quadra[i - 1].A.name) {
				if(Quadra[i - 1].A.IsAct) {
					//cout << "ST    R, " << Quadra[i - 1].A.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i - 1].A.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}

				AimTemp.count = SEM[SEM.size() - 1];	//栈顶元素 弹出
				SEM.pop_back();
				stringstream ss;
				ss << (Aim_count + 1);			//当前的代码行数+1
				ss >> s_temp;
				AimCode[AimTemp.count - 1].code = AimCode[AimTemp.count - 1].code.substr(0, AimCode[AimTemp.count - 1].code.length()-2);
				AimCode[AimTemp.count - 1].code.append(s_temp);

				//cout << "JMP    _, _" << endl;
				AimTemp.code = "JMP    _, _";
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;

				SEM.push_back(AimCode.size());		//push(p)
			}
		}

		if(Quadra[i].op == "ie") {
			if(RNode.name == Quadra[i - 1].A.name) {
				if(Quadra[i - 1].A.IsAct) {
					//cout << "ST    R, " << Quadra[i - 1].A.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i - 1].A.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}

				AimTemp.count = SEM[SEM.size() - 1];	//栈顶元素 弹出
				SEM.pop_back();

				//ss << (Aim_count);			//当前的代码行数
				stringstream ss;
				ss << Aim_count;
				ss >> s_temp;
				AimCode[AimTemp.count - 1].code = AimCode[AimTemp.count - 1].code.substr(0, AimCode[AimTemp.count - 1].code.length()-2);
				AimCode[AimTemp.count - 1].code.append(s_temp);
			}
		}

		if(Quadra[i].op == "wh") {
			SEM.push_back(AimCode.size());
		}

		if(Quadra[i].op == "do") {
			if (RNode.name == " ") {
				//cout << "LD    R, " << Quadra[i].B.name << endl;
				AimTemp.code = "LD    R, " + Quadra[i].B.name;
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;

				//cout << "FJ    R, _" << endl;
				AimTemp.code = "FJ    R, _";
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;

				SEM.push_back(AimCode.size());		//push(p)
			}
			if(RNode.name == Quadra[i].B.name) {
				if(Quadra[i].B.IsAct) {
					//cout << "ST    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				SEM.push_back(AimCode.size());		//push(p)
				RNode.name = " ";					//RNode置空    RNode:=0
			}
			else {
				if(RNode.IsAct) {
					//cout << "ST    R, " << RNode.name << endl;
					AimTemp.code = "ST    R, " + RNode.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

				}
				else {
					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				SEM.push_back(AimCode.size());		//push(p)
				RNode.name = " ";					//RNode置空    RNode:=0
			}
		}

		if(Quadra[i].op == "we") {
			if(RNode.name == Quadra[i - 1].A.name) {
				if(Quadra[i - 1].A.IsAct) {
					//cout << "ST    R, " << Quadra[i - 1].A.name;
					AimTemp.code = "ST    R, " + Quadra[i - 1].A.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			RNode.name = " ";

			AimTemp.count = SEM[SEM.size() - 1];	//栈顶元素 弹出
			SEM.pop_back();
            stringstream ss;
			ss << (Aim_count + 1);			//当前的代码行数+1
			ss >> s_temp;
			AimCode[AimTemp.count - 1].code.append(s_temp);

			AimTemp.count = SEM[SEM.size() - 1];	//栈顶元素 弹出
			SEM.pop_back();

			//cout << "JMP    _, " << AimTemp.count << endl;
			//stringstream ss;
			ss << (AimTemp.count);
			ss >> s_temp;
			AimTemp.code = "JMP    _, " + s_temp;
			AimTemp.count = Aim_count;
			AimCode.push_back(AimTemp);
			Aim_count++;
		}

		if(Quadra[i].op == "for") {
			SEM.push_back(AimCode.size());
		}

		if(Quadra[i].op == "dofor") {
			if(RNode.name == " ") {
				//cout << "LD    R, " << Quadra[i].B.name << endl;
				AimTemp.code = "LD    R, " + Quadra[i].B.name;
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;

				//cout << "FJ    R, _" << endl;
				AimTemp.code = "FJ    R, _";
				AimTemp.count = Aim_count;
				AimCode.push_back(AimTemp);
				Aim_count++;

				SEM.push_back(AimCode.size());		//push(p)
			}
			if(RNode.name == Quadra[i].B.name) {
				if(Quadra[i].B.IsAct) {
					//cout << "ST    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "ST    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				else {
					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				SEM.push_back(AimCode.size());		//push(p)
				RNode.name = " ";					//RNode置空    RNode:=0
			}
			else {
				if(RNode.IsAct) {
					//cout << "ST    R, " << RNode.name << endl;
					AimTemp.code = "ST    R, " + RNode.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

				}
				else {
					//cout << "LD    R, " << Quadra[i].B.name << endl;
					AimTemp.code = "LD    R, " + Quadra[i].B.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;

					//cout << "FJ    R, _" << endl;
					AimTemp.code = "FJ    R, _";
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
				SEM.push_back(AimCode.size());		//push(p)
				RNode.name = " ";					//RNode置空    RNode:=0
			}
		}

		if(Quadra[i].op == "iefor") {
			if(RNode.name == Quadra[i - 1].A.name) {
				if(Quadra[i - 1].A.IsAct) {
					//cout << "ST    R, " << Quadra[i - 1].A.name;
					AimTemp.code = "ST    R, " + Quadra[i - 1].A.name;
					AimTemp.count = Aim_count;
					AimCode.push_back(AimTemp);
					Aim_count++;
				}
			}
			RNode.name = " ";

			AimTemp.count = SEM[SEM.size() - 1];	//栈顶元素 弹出
			SEM.pop_back();
			stringstream ss;
			ss << (Aim_count+1);			//当前的代码行数+1
			ss >> s_temp;
			AimCode[AimTemp.count - 1].code.append(s_temp);

			AimTemp.count = SEM[SEM.size() - 1];	//栈顶元素 弹出
			SEM.pop_back();

			//cout << "JMP    _, " << AimTemp.count << endl;

			//stringstream ss;
			ss << (AimTemp.count);
			ss >> s_temp;
			AimTemp.code = "JMP    _, " + s_temp;
			AimTemp.count = Aim_count;
			AimCode.push_back(AimTemp);
			Aim_count++;
		}

		if(Quadra[i].op == "call") {
			//cout << "call    " << Quadra[i].B.name << endl;
			AimTemp.code = "call    " + Quadra[i].B.name;
			AimTemp.count = Aim_count;
			AimCode.push_back(AimTemp);
			Aim_count++;
		}

		if(Quadra[i].op == "ret") {
			//cout << "call    " << endl;
			AimTemp.code = "ret";
			AimTemp.count = Aim_count;
			AimCode.push_back(AimTemp);
			Aim_count++;
		}

		if(Quadra[i].op == "par") {
			//什么都不做
		}

		SY_tem.name = Quadra[i].A.name;
		SY_tem.IsAct = Quadra[i].A.IsAct;
		SY_num++;
		//SYMBL.push_back(SY_tem);
		SY_tem.name = Quadra[i].B.name;
		SY_tem.IsAct = Quadra[i].B.IsAct;
		SY_num++;
		//SYMBL.push_back(SY_tem);
		SY_tem.name = Quadra[i].C.name;
		SY_tem.IsAct = Quadra[i].C.IsAct;
		SY_num++;
		//SYMBL.push_back(SY_tem);
	}
}

void divide() {				//分块函数
	int state_temp = 0;
	for (unsigned int i = 0; i < Quadra.size(); i++) {		//遇到如下的 op 说明是下一块
		if (Quadra[i].op == "if" || Quadra[i].op == "el" || Quadra[i].op == "ie" ||
			Quadra[i].op == "wh" || Quadra[i].op == "do" || Quadra[i].op == "we" ||
			Quadra[i].op == "for" || Quadra[i].op == "dofor" || Quadra[i].op == "iefor") {
			Quadra[i].state = state_temp++;  //将块信息变为下一块 即 +1 操作
		}
		else {
			Quadra[i].state = state_temp;
		}
	}
}

void WriteActState() { //写入活跃信息
    divide();
    //查符号表得出四元式变量初始活跃信息
    for(int j=Quadra.size()-1; j>=0; j--) {
        //cout<<Quadra[j].B.name<<" "<<Quadra[j].C.name<<" "<<Quadra[j].A.name<<endl;
        int Act_flag=0;
        for(unsigned int i=0; i<SYNBL.name.size(); i++) {
            if(Quadra[j].B.name == SYNBL.name[i]) {
                Quadra[j].B.IsAct=SYNBL.IsAct[i];
                SYNBL.IsAct[i]=true;
                //cout<<"B"<<endl;
                Act_flag++;
                if(Act_flag==3) {
                    Act_flag=0;
                    break;
                }
            }
            if(Quadra[j].C.name == SYNBL.name[i]) {
                Quadra[j].C.IsAct=SYNBL.IsAct[i];
                SYNBL.IsAct[i]=true;
                //cout<<"C"<<endl;
                Act_flag++;
                if(Act_flag==3) {
                    Act_flag=0;
                    break;
                }
            }
            if(Quadra[j].A.name == SYNBL.name[i]) {
                Quadra[j].A.IsAct=SYNBL.IsAct[i];
                SYNBL.IsAct[i]=false;
                //cout<<"A"<<endl;
                Act_flag++;
                if(Act_flag==3) {
                    Act_flag=0;
                    break;
                }
            }
        }
    }
    //for结束
}

