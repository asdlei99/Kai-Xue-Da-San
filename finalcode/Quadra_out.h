
#ifndef QUADRA_OUT_H_INCLUDED
#define QUADRA_OUT_H_INCLUDED



#endif // QUADRA_OUT_H_INCLUDED

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

using namespace std;

//LL(1)语法分析
void PUSH(int token);
void NEXT();
void POP();
int Token_to_code(char cat,int key);
bool Search_LL1_Excel();

int Stack[1000];
int Stack_Address=-1;
int Token_Address=0;
char Current_Token_cat;
int Current_Token_key;
int fx;

//LL(1)语义分析之生成四元式
void GEQ(string Operator,int lable);
void PUSHSEM(string pushstr);
void POPSEM();
void ASSI();

int _t=0;
string intermadiateValue[50]={"t1","t2","t3","t4","t5","t6","t7","t8","t9","t10","t11","t12","t13","t14","t15","t16","t17","t18","t19","t20"};

string SEM[100];
int Topstack=0;

string destination[1000];
int ge=0;


//语法分析之生成跳转四元式
void IF();
void EL();
void IE();
void GEQ_Judge(string Operator,int lable);

void WH();
void DO();
void WE();

//语法分析之生成数组四元式
string ArraySem[50];
int ArraySem_Address=0;
void PUSHARRAYSEM(string i);

//LL(1)语义分析之填写符号表

void WRITE_SYNBL(string name,string l);
void PUSHTYPE(string type);

string Name[50];
string Type[50];
string Cat[50];
int Address[50];
string L[50];

string Current_Type;
int Synbl_Address=0;
int Addr=0;

//string str[200]={};


class node {			//四元式的A B C位置的数据类型
public:
	string name;		//标识符名称
	bool IsAct;				//活跃信息
};

class quadra {		//每一条四元式的数据类型 (带活跃信息的)
public:
	int state;		//块信息
	string op;		//op位置
	node B;			//B位置
	node C;			//C位置
	node A;			//A位置
};

vector<quadra> Quadra; //四元式

void NEXT(){
     Current_Token_cat=Token[Token_Address].Table_cat;
     Current_Token_key=Token[Token_Address].Table_key;
     Token_Address++;
}

void PUSH(int code){
    Stack[++Stack_Address]=code;
}

void POP(){
    fx=Stack[Stack_Address];
    Stack_Address--;
}

int Token_to_code(char cat,int key){

    if(cat=='K'){
    switch(key)
    {
    case 1:
        return 4;////////////////
    case 2:
        return 18;
    case 3:
        return 15;
    case 4:
        return 16;
    case 5:
        return 17;
    case 6:
        return 5;
    case 7:
        return 6;
    case 8:
        return 28;
    case 12:
        return 33;///////////////////////
    default:
        return -1;
    }
  }
  else if(cat=='P'){
     switch(key)
    {
    case 1:
        return 9;
    case 2:
        return 8;
    case 3:
        return 0;
    case 4:
        return 1;
    case 7:
        return 2;
    case 8:
        return 3;
    case 9:
        return 7;
    case 10:
        return 20;
    case 11:
        return 19;
    case 12:
        return 21;
    case 13:
        return 23;
    case 14:
        return 22;
    case 16:
        return 10;
    case 17:
        return 11;
    case 18:
        return 12;
    case 19:
        return 13;
    case 35:
        return 25;
    case 36:
        return 24;
    case 5://///////////////////////
        return 30;
    case 6:
        return 31;
    case 29:
        return 32;
    default:
        return -1;
    }
  }
  else if(cat=='I'){
      return 4;
  }
  else if(cat=='C'){
      return 14;
  }
  else if(cat=='c'){
      return 29;//////////////////////////////
  }
  else if(cat=='#'){
      //cout<<"#"<<endl;
      return 100;
  }
  else {
    return -1;
  }
}

bool Search_LL1_Excel(){
    switch(fx){
     case 51:
          if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {
            Stack[++Stack_Address]=64;
            Stack[++Stack_Address]=52;
            return true;
        }
         else if(Token_to_code(Current_Token_cat,Current_Token_key)==33){/////////////////////////////////////////////

            Stack[++Stack_Address]=51;
            Stack[++Stack_Address]=3;
            Stack[++Stack_Address]=74;
            Stack[++Stack_Address]=2;
            Stack[++Stack_Address]=4;
            Stack[++Stack_Address]=33;
            return true;
        }
        else
            return false;
    case 64:
        if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {
            Stack[++Stack_Address]=64;/////////////////
            Stack[++Stack_Address]=52;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==100){

            return true;
        }
        else
            return false;
    case 52:
        if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {
            Stack[++Stack_Address]=3;
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=2;
            Stack[++Stack_Address]=1;
            Stack[++Stack_Address]=0;
            Stack[++Stack_Address]=4;
            Stack[++Stack_Address]=53;
            return true;
        }
        else
            return false;
    case 54:
        if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=55;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==3){

            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==4){

            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=56;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==5){

            Stack[++Stack_Address]=65;
            Stack[++Stack_Address]=3;
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=2;
            Stack[++Stack_Address]=109;///////
            Stack[++Stack_Address]=1;
            Stack[++Stack_Address]=57;
            Stack[++Stack_Address]=0;
            Stack[++Stack_Address]=5;
            return true;
        }
        else if((Token_to_code(Current_Token_cat,Current_Token_key)==26)&&(Token_to_code(Current_Token_cat,Current_Token_key)==27))
        {
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=58;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==28){//////////

            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=3;
            Stack[++Stack_Address]=121;/////////////////
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=2;
            Stack[++Stack_Address]=120;////////////////
            Stack[++Stack_Address]=1;
            Stack[++Stack_Address]=57;
            Stack[++Stack_Address]=0;
            Stack[++Stack_Address]=119;////////////////
            Stack[++Stack_Address]=28;
            return true;
        }
        else
            return false;
    case 65:
        if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=111;///////
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==6){

            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=111;///////
            Stack[++Stack_Address]=3;
            Stack[++Stack_Address]=54;
            Stack[++Stack_Address]=2;
            Stack[++Stack_Address]=110;///////
            Stack[++Stack_Address]=6;
            return true;
        }
        else
            return false;
    case 55:
        if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {
            Stack[++Stack_Address]=59;
            Stack[++Stack_Address]=107;//////
            Stack[++Stack_Address]=53;
            return true;
        }
        else
            return false;
             return false;
    case 56:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==4)
        {
            Stack[++Stack_Address]=70;
            Stack[++Stack_Address]=101;
            //Stack[++Stack_Address]=106;/////////////////////////////
            //Stack[++Stack_Address]=60;
            //Stack[++Stack_Address]=7;
            //Stack[++Stack_Address]=101;/////////////////////////////
            Stack[++Stack_Address]=4;
            return true;
        }
        else
            return false;
    case 59:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==4)
        {

            Stack[++Stack_Address]=71;
            Stack[++Stack_Address]=101;//********************
            Stack[++Stack_Address]=108;//////
            Stack[++Stack_Address]=4;
            return true;
        }
        else
            return false;
   case 66:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==8)
        {
            //Stack[++Stack_Address]=9;//////////////////////////
            Stack[++Stack_Address]=59;
            Stack[++Stack_Address]=8;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==9)
        {
            Stack[++Stack_Address]=9;
            return true;
        }
        else
            return false;
    case 57:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==0||Token_to_code(Current_Token_cat,Current_Token_key)==4||Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=67;
            Stack[++Stack_Address]=60;
            return true;
        }
        else
            return false;
    case 67:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==1)
        {
            return true;
        }
        else if((Token_to_code(Current_Token_cat,Current_Token_key)>=19)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=25))///////
        {
            if(Token_to_code(Current_Token_cat,Current_Token_key)==19){
                 Stack[++Stack_Address]=112;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else if(Token_to_code(Current_Token_cat,Current_Token_key)==20){
                 Stack[++Stack_Address]=113;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else if(Token_to_code(Current_Token_cat,Current_Token_key)==21){
                 Stack[++Stack_Address]=114;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else if(Token_to_code(Current_Token_cat,Current_Token_key)==22){
                 Stack[++Stack_Address]=115;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else if(Token_to_code(Current_Token_cat,Current_Token_key)==23){
                 Stack[++Stack_Address]=116;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else if(Token_to_code(Current_Token_cat,Current_Token_key)==24){
                 Stack[++Stack_Address]=118;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else if(Token_to_code(Current_Token_cat,Current_Token_key)==25){
                 Stack[++Stack_Address]=117;
                 Stack[++Stack_Address]=60;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
        }
        else
            return false;
    case 58:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==26)
        {
            Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=26;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==27)
        {
            Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=27;
            return true;
        }
        else
            return false;
    case 60:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==0||Token_to_code(Current_Token_cat,Current_Token_key)==4||Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=68;
            Stack[++Stack_Address]=61;
            return true;
        }
        else
            return false;
    case 68:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==10||Token_to_code(Current_Token_cat,Current_Token_key)==11)
        {
            if(Token_to_code(Current_Token_cat,Current_Token_key)==10){
                 Stack[++Stack_Address]=68;
                 Stack[++Stack_Address]=102;///////////////////////////////
                 Stack[++Stack_Address]=61;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
            return true;
            }
            else{
                 Stack[++Stack_Address]=68;
                 Stack[++Stack_Address]=103;/////////////////////////////
                 Stack[++Stack_Address]=61;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==1||Token_to_code(Current_Token_cat,Current_Token_key)==9
        ||((Token_to_code(Current_Token_cat,Current_Token_key)>=19)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=25))){
            return true;
        }
        else
            return false;
    case 61:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==0||Token_to_code(Current_Token_cat,Current_Token_key)==4||Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=69;
            Stack[++Stack_Address]=62;
            return true;
        }
        else
            return false;
    case 69:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==12||Token_to_code(Current_Token_cat,Current_Token_key)==13)
        {
             if(Token_to_code(Current_Token_cat,Current_Token_key)==12){
                 Stack[++Stack_Address]=69;
                 Stack[++Stack_Address]=104;/////////////////////////////
                 Stack[++Stack_Address]=62;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
            else{
                 Stack[++Stack_Address]=69;
                 Stack[++Stack_Address]=105;////////////////////////////
                 Stack[++Stack_Address]=62;
                 Stack[++Stack_Address]=Token_to_code(Current_Token_cat,Current_Token_key);
                 return true;
            }
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==1||Token_to_code(Current_Token_cat,Current_Token_key)==9
        ||Token_to_code(Current_Token_cat,Current_Token_key)==10||Token_to_code(Current_Token_cat,Current_Token_key)==11
        ||((Token_to_code(Current_Token_cat,Current_Token_key)>=19)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=25))){
            return true;
        }
        else
            return false;
    case 62:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==0)
        {
            Stack[++Stack_Address]=1;
            Stack[++Stack_Address]=60;
            Stack[++Stack_Address]=0;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==4||Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=63;
            return true;
        }
        else
            return false;
    case 63:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==4)
        {
            Stack[++Stack_Address]=101;///////////////////////////
            Stack[++Stack_Address]=4;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=101;//////////////////////////
            Stack[++Stack_Address]=14;
            return true;
        }
        else
            return false;
    case 53:
        if(Token_to_code(Current_Token_cat,Current_Token_key)==15)
        {
            Stack[++Stack_Address]=15;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==16)
        {
            Stack[++Stack_Address]=16;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==17)
        {
            Stack[++Stack_Address]=17;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==18)
        {
            Stack[++Stack_Address]=18;
            return true;
        }
        else
            return false;
    case 70://///////////////////////////////////////////////////////////////////////////
         if(Token_to_code(Current_Token_cat,Current_Token_key)==7)
        {
            Stack[++Stack_Address]=73;
            Stack[++Stack_Address]=7;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==30)
        {
            Stack[++Stack_Address]=73;
            Stack[++Stack_Address]=7;
            Stack[++Stack_Address]=31;
            Stack[++Stack_Address]=122;//**********************
            Stack[++Stack_Address]=14;
            Stack[++Stack_Address]=30;
            return true;
        }
        else
            return false;
    case 71://///////////////////////////////////////////////////////////////////////////
         if(Token_to_code(Current_Token_cat,Current_Token_key)==7)
        {
            Stack[++Stack_Address]=72;
            Stack[++Stack_Address]=7;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==8||Token_to_code(Current_Token_cat,Current_Token_key)==9)
        {
            Stack[++Stack_Address]=66;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==30)
        {
             Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=31;
            Stack[++Stack_Address]=14;
            Stack[++Stack_Address]=30;
            return true;
        }
        else
            return false;
    case 72://///////////////////////////////////////////////////////////////////////////
         if(Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=106;//**************
            Stack[++Stack_Address]=101;//***************
            Stack[++Stack_Address]=14;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==32)
        {
            Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=32;
            Stack[++Stack_Address]=106;//**************
            Stack[++Stack_Address]=101;//***************
            Stack[++Stack_Address]=29;
            Stack[++Stack_Address]=32;
            return true;
        }
        else
            return false;
    case 73://///////////////////////////////////////////////////////////////////////////
         if(Token_to_code(Current_Token_cat,Current_Token_key)==0||Token_to_code(Current_Token_cat,Current_Token_key)==4||Token_to_code(Current_Token_cat,Current_Token_key)==14)
        {
            Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=106;/////////////////////////////
            Stack[++Stack_Address]=60;
            return true;
        }
        else if(Token_to_code(Current_Token_cat,Current_Token_key)==32)
        {
            Stack[++Stack_Address]=9;
            Stack[++Stack_Address]=32;
            Stack[++Stack_Address]=106;//**************
            Stack[++Stack_Address]=101;//***************
            Stack[++Stack_Address]=29;
            Stack[++Stack_Address]=32;
            return true;
        }
        else
            return false;
    case 74://///////////////////////////////////////////////////////////////////////////
         if(Token_to_code(Current_Token_cat,Current_Token_key)==3)
        {
            return true;
        }
        else if((Token_to_code(Current_Token_cat,Current_Token_key)>=15)&&(Token_to_code(Current_Token_cat,Current_Token_key)<=18))
        {

            Stack[++Stack_Address]=74;
            Stack[++Stack_Address]=55;
            return true;
        }
        else
            return false;
    case 101:
        PUSHSEM(str[Token_Address-2]);
        return true;
    case 102:
         GEQ("+",_t);////////////////////////////
         _t++;
         return true;
    case 103:
         GEQ("-",_t);////////////////////////////
         _t++;
         return true;
    case 104:
         GEQ("*",_t);////////////////////////////
         _t++;
         return true;
    case 105:
         GEQ("/",_t);////////////////////////////
         _t++;
         return true;
    case 106:
         ASSI();///////////////////
         return true;
    case 107:
         PUSHTYPE(str[Token_Address-2]);//////
         return true;
    case 108:
         WRITE_SYNBL(str[Token_Address-2],"y");
         return true;
    case 109:
        IF();
        return true;
    case 110:
        EL();
        return true;
    case 111:
        IE();
        return true;
    case 112:
        GEQ_Judge(">",_t);
        _t++;
        return true;
    case 113:
        GEQ_Judge("<",_t);
        _t++;
        return true;
    case 114:
        GEQ_Judge("==",_t);
        _t++;
        return true;
    case 115:
        GEQ_Judge(">=",_t);
        _t++;
        return true;
    case 116:
        GEQ_Judge("<=",_t);
        _t++;
        return true;
    case 117:
        GEQ_Judge("&&",_t);
        _t++;
        return true;
    case 118:
        GEQ_Judge("||",_t);
        _t++;
        return true;
    case 119:
        WH();
        return true;
    case 120:
        DO();
        return true;
    case 121:
        WE();
        return true;
    case 122://*******************
        PUSHARRAYSEM(str[Token_Address-2]);
        return true;
    default :
        return false;
    }
}


void GEQ(string Operator,int lable){

    destination[ge++]=Operator;
    destination[ge++]=SEM[Topstack-2];
    destination[ge++]=SEM[Topstack-1];
    destination[ge++]=intermadiateValue[lable];

    Current_Type="int";//////
    WRITE_SYNBL(intermadiateValue[lable],"n");//////

    POPSEM();
    POPSEM();
    PUSHSEM(intermadiateValue[lable]);

}

void ASSI(){

    if(ArraySem_Address==0){
         destination[ge++]="=";
         destination[ge++]=SEM[Topstack-1];
         destination[ge++]="_";
         destination[ge++]=SEM[Topstack-2];

         POPSEM();
         POPSEM();
    }
    else{//*********************
         destination[ge++]="=";
         destination[ge++]=SEM[Topstack-1];
         destination[ge++]="_";
         destination[ge++]=SEM[Topstack-2]+"["+ArraySem[ArraySem_Address-1]+"]";

         ArraySem_Address--;

         POPSEM();
         POPSEM();
    }
}

void PUSHSEM(string pushstr){
    SEM[Topstack]=pushstr;
    Topstack++;
}

void POPSEM(){
    Topstack--;
}

////////////////////////////////
void WRITE_SYNBL(string name,string l){

    string str1="int";
    string str2="float";
    string str3="char";
    string str4="bool";

     if(Current_Type==str1){
        Type[Synbl_Address]="itp";
    }
    else if(Current_Type==str2){
        Type[Synbl_Address]="rtp";
    }
    else if(Current_Type==str3){
       Type[Synbl_Address]="ctp";
    }
    else if(Current_Type==str4){
       Type[Synbl_Address]="btp";
    }

    Name[Synbl_Address]=name;
    Cat[Synbl_Address]="v";
    Address[Synbl_Address]=Addr;

    if(Current_Type==str1){
        Addr=Addr+4;
    }
    else if(Current_Type==str2){
        Addr=Addr+8;
    }
    else if(Current_Type==str3){
        Addr=Addr+1;
    }
    else if(Current_Type==str4){
        Addr=Addr+1;
    }

    L[Synbl_Address]=l;

    Synbl_Address++;
}

void PUSHTYPE(string type){

     Current_Type=type;
}


void IF(){//////////////////
    destination[ge++]="if";
    destination[ge++]=SEM[Topstack-1];
    destination[ge++]="_";
    destination[ge++]="_";

    POPSEM();
}

void EL(){
    destination[ge++]="el";
    destination[ge++]="_";
    destination[ge++]="_";
    destination[ge++]="_";
}

void IE(){
    destination[ge++]="ie";
    destination[ge++]="_";
    destination[ge++]="_";
    destination[ge++]="_";
}

void GEQ_Judge(string Operator,int lable){////////

    destination[ge++]=Operator;
    destination[ge++]=SEM[Topstack-2];
    destination[ge++]=SEM[Topstack-1];
    destination[ge++]=intermadiateValue[lable];

    Current_Type="bool";//////
    WRITE_SYNBL(intermadiateValue[lable],"n");//////


    POPSEM();
    POPSEM();
    PUSHSEM(intermadiateValue[lable]);
}

///////////////////////
void WH(){
    destination[ge++]="wh";
    destination[ge++]="_";
    destination[ge++]="_";
    destination[ge++]="_";
}

void DO(){
    destination[ge++]="do";
    destination[ge++]=SEM[Topstack-1];
    destination[ge++]="_";
    destination[ge++]="_";

    POPSEM();
}

void WE(){
    destination[ge++]="we";
    destination[ge++]="_";
    destination[ge++]="_";
    destination[ge++]="_";
}


void PUSHARRAYSEM(string i){
    ArraySem[ArraySem_Address]=i;
    ArraySem_Address++;
}

