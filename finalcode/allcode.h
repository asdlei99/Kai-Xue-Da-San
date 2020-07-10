
#include <iostream>
#include<map>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include<vector>
#include "divide.h"
//#include "token_out.h"

using namespace std;

class allCode{
public:
    res_All res;
    Synbl synbl;
    Tapel tapel;
    Ainfl ainfl;
    Dinfl dinfl;
};
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

string err_2 = "";
string err_3 = "";

//LL(1)语义分析之生成四元式
void GEQ(string Operator,int lable);
void PUSHSEM(string pushstr);
void POPSEM();
void ASSI();

int inter_t=0;
string intermadiateValue[50]={"t1","t2","t3","t4","t5","t6","t7","t8","t9","t10","t11","t12","t13","t14","t15","t16","t17","t18","t19","t20"};

string SEM1[100]={};
int Topstack=0;

string destination[1000]={};
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

//LL(1)语义分析之填写符号总表

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

//LL(1)语义分析之填写数组表
void WRITE_AINFL(string up);
int Low[50];
string Up[50];
string Ctp[50];
int Clen[50];

int AINFL_Address=0;

//错误处理
void ERROR1(string name);

//LL(1)语义分析之填写结构体表
void RINFL_T();
void WRITERINFL(string name);
void RINFL_F();

string ID[50];
int OFF[50];
string TP[50];
int RINFL_Address=0;
int Addr_Rinfl=0;

int count_R;

bool Rinfl=false;


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
            Stack[++Stack_Address]=126;//&&&&&&&&&&&&&&&&&&&&
            Stack[++Stack_Address]=3;
            Stack[++Stack_Address]=74;
            Stack[++Stack_Address]=2;
            Stack[++Stack_Address]=125;//&&&&&&&&&&&&&&&&&&
            Stack[++Stack_Address]=4;
            Stack[++Stack_Address]=124;//&&&&&&&&&&&&&&&&&&&
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
            Stack[++Stack_Address]=127;//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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
            Stack[++Stack_Address]=127;//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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
            Stack[++Stack_Address]=123;//&&&&&&&&&&&&&&&&&&
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
         GEQ("+",inter_t);////////////////////////////
         inter_t++;
         return true;
    case 103:
         GEQ("-",inter_t);////////////////////////////
         inter_t++;
         return true;
    case 104:
         GEQ("*",inter_t);////////////////////////////
         inter_t++;
         return true;
    case 105:
         GEQ("/",inter_t);////////////////////////////
         inter_t++;
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
    case 109://////////////////////////////////////////////////////////
        IF();
        return true;
    case 110:
        EL();
        return true;
    case 111:
        IE();
        return true;
    case 112:
        GEQ_Judge(">",inter_t);
        inter_t++;
        return true;
    case 113:
        GEQ_Judge("<",inter_t);
        inter_t++;
        return true;
    case 114:
        GEQ_Judge("==",inter_t);
        inter_t++;
        return true;
    case 115:
        GEQ_Judge(">=",inter_t);
        inter_t++;
        return true;
    case 116:
        GEQ_Judge("<=",inter_t);
        inter_t++;
        return true;
    case 117:
        GEQ_Judge("&&",inter_t);
        inter_t++;
        return true;
    case 118:
        GEQ_Judge("||",inter_t);
        inter_t++;
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
    case 123://&&&&&&&&&&&
        WRITE_AINFL(str[Token_Address-2]);
        return true;
    case 124://&&&&&&&&&&&&&&&
        RINFL_T();
        return true;
    case 125://*******************
       WRITERINFL(str[Token_Address-2]);
        return true;
    case 126://&&&&&&&&&&&
         RINFL_F();
        return true;
    case 127://&&&&&&&&&&&
         ERROR1(str[Token_Address-2]);
        return true;
    default :
        return false;
    }
}


void GEQ(string Operator,int lable){

    destination[ge++]=Operator;
    destination[ge++]=SEM1[Topstack-2];
    destination[ge++]=SEM1[Topstack-1];
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
         destination[ge++]=SEM1[Topstack-1];
         destination[ge++]="_";
         destination[ge++]=SEM1[Topstack-2];

         POPSEM();
         POPSEM();
    }
    else{//*********************
         destination[ge++]="=";
         destination[ge++]=SEM1[Topstack-1];
         destination[ge++]="_";
         destination[ge++]=SEM1[Topstack-2]+"["+ArraySem[ArraySem_Address-1]+"]";

         ArraySem_Address--;

         POPSEM();
         POPSEM();
    }
}

void PUSHSEM(string pushstr){

    SEM1[Topstack]=pushstr;
    Topstack++;
}

void POPSEM(){
    Topstack--;
}


void WRITE_SYNBL(string name,string l){

    string str1="int";
    string str2="float";
    string str3="char";
    string str4="bool";

   if(Rinfl){

    if(Current_Type==str1){
        Type[Synbl_Address]="itp";
         TP[RINFL_Address]="itp";
        Address[Synbl_Address]=4;
    }
    else if(Current_Type==str2){
        Type[Synbl_Address]="rtp";
         TP[RINFL_Address]="rtp";
        Address[Synbl_Address]=8;
    }
    else if(Current_Type==str3){
       Type[Synbl_Address]="ctp";
        TP[RINFL_Address]="ctp";
       Address[Synbl_Address]=1;
    }
    else if(Current_Type==str4){
       Type[Synbl_Address]="btp";
        TP[RINFL_Address]="btp";
       Address[Synbl_Address]=1;
    }

    Name[Synbl_Address]=name;
    ID[RINFL_Address]=name;

    OFF[RINFL_Address]=Addr_Rinfl;


    Cat[Synbl_Address]="d";

    if(Current_Type==str1){
        Addr=Addr+4;
        Addr_Rinfl=Addr_Rinfl+4;
    }
    else if(Current_Type==str2){
        Addr=Addr+8;
        Addr_Rinfl=Addr_Rinfl+8;
    }
    else if(Current_Type==str3){
        Addr=Addr+1;
        Addr_Rinfl=Addr_Rinfl+1;
    }
    else if(Current_Type==str4){
        Addr=Addr+1;
        Addr_Rinfl=Addr_Rinfl+1;
    }

    L[Synbl_Address]=l;

    Synbl_Address++;
    RINFL_Address++;

    }
    else{
        int i=0;
        for(i=0;i<Synbl_Address;i++){
            if(name==Name[i]){
                break;
            }
        }
        if(i!=Synbl_Address){
            cout<<"错误：标识符重定义！"<<endl;
            cout<<"重定义的标识符为："<<str[Token_Address-2]<<endl;//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

            err_2 = err_2+"语法分析失败"+"\x0d\x0a"+"错误：标识符重定义！"+"\x0d\x0a"+"重定义的标识符为："+str[Token_Address-2];
            //SetWindowText(exptxt_dis,err_2.c_str());
        }

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
}

void PUSHTYPE(string type){

     Current_Type=type;
}


void IF(){//////////////////
    destination[ge++]="if";
    destination[ge++]=SEM1[Topstack-1];
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
    destination[ge++]=SEM1[Topstack-2];
    destination[ge++]=SEM1[Topstack-1];
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
    destination[ge++]=SEM1[Topstack-1];
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

void WRITE_AINFL(string up){

    string str1="int";
    string str2="float";
    string str3="char";
    string str4="bool";

    Type[Synbl_Address-1]="a";
    Cat[Synbl_Address-1]="t";

    if(Current_Type==str1){
         Ctp[AINFL_Address]="itp";
         Addr=Addr-4+(4*atoi(up.c_str()));
         Address[Synbl_Address-1]=4*atoi(up.c_str());
    }
    else if(Current_Type==str2){
         Ctp[AINFL_Address]="rtp";
         Addr=Addr-8+(8*atoi(up.c_str()));
        Address[Synbl_Address-1]=8*atoi(up.c_str());
    }
    else if(Current_Type==str3){
        Ctp[AINFL_Address]="ctp";
        Addr=Addr-1+(1*atoi(up.c_str()));
        Address[Synbl_Address-1]=1*atoi(up.c_str());
    }
    else if(Current_Type==str4){
        Ctp[AINFL_Address]="btp";
        Addr=Addr-1+(1*atoi(up.c_str()));
        Address[Synbl_Address-1]=1*atoi(up.c_str());
    }

    Low[AINFL_Address]=0;
    Up[AINFL_Address]=up;

     if(Current_Type==str1){
          Clen[AINFL_Address]=4;
    }
    else if(Current_Type==str2){
          Clen[AINFL_Address]=8;
    }
    else if(Current_Type==str3){
         Clen[AINFL_Address]=1;
    }
    else if(Current_Type==str4){
         Clen[AINFL_Address]=1;
    }

         AINFL_Address++;
}

void RINFL_T(){
    Rinfl=true;
    count_R=Synbl_Address;
}
void WRITERINFL(string name){

    Name[Synbl_Address]=name;
    Type[Synbl_Address]="d";
    L[Synbl_Address]="y";
    Cat[Synbl_Address]="t";

    Synbl_Address++;

}
void RINFL_F(){
    Rinfl=false;
    Address[count_R]= Addr_Rinfl;//&&&&&&&&&&&&&&&&&&&&&7
    Addr_Rinfl=0;

}


void ERROR1(string name){
      int i=0;
        for(i=0;i<Synbl_Address;i++){
            if(name==Name[i]){
                break;
            }
        }
        if(i==Synbl_Address){
            cout<<"错误：标识符未声明！"<<endl;
            cout<<"未声明的标识符为："<<str[Token_Address-2]<<endl;//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

            err_3 = err_3+"语法分析失败"+"\x0d\x0a"+"错误：标识符未声明！"+"\x0d\x0a"+"未声明的标识符为："+str[Token_Address-2];
            //SetWindowText(exptxt_dis,err_3.c_str());
        }
}


void writeInR(string id[], int of[], string tp[],
             Dinfl& dinfl,Tapel& tapel, int len){
    int i;
    for(i = 0; i < len; i++){
        dinfl.id.push_back(id[i]);
        dinfl.off.push_back(of[i]);
        if(tp[i].compare("itp") == 0 ){
            dinfl.tp.push_back(0);
        }
        else if(tp[i].compare("rtp") == 0 ){
            dinfl.tp.push_back(1);
        }
        else if(tp[i].compare("ctp") == 0 ){
            dinfl.tp.push_back(2);
        }
        else if(tp[i].compare("btp") == 0 ){
            dinfl.tp.push_back(3);
        }
        else {
            int len = tapel.tval.size();
            dinfl.tp.push_back(len);
            tapel.tval.push_back(tp[i]);
            if(tp[i].compare("a") == 0){
                tapel.tpoint.push_back(i+1);
                //alen++;  //虚拟
            }
            if(tp[i].compare("d") == 0){
                tapel.tpoint.push_back(i+1);
                //dlen++;  //虚拟
            }

        }
    }
}


void writeInA(int low[], string up[], string ctp[], int clen[],
             //, string id[], string of[], string tp[],
             Ainfl& ainfl,Tapel& tapel, int len){
    int i, sum, k;
    cout<<"**********************************"<<endl;
    for(i = 0; i < tapel.tval.size(); i++){
        cout<<tapel.tval[i] << endl;
    }
    cout<<endl;
    for(i = 0; i < len; i++){
        sum = 0;
        ainfl.low.push_back(low[i]);
        ainfl.clen.push_back(clen[i]);
        for(k = 0; k < up[i].length(); k++){

            sum = sum * 10 + up[i][k] - '0';
        }
        ainfl.up.push_back(sum);
        if(ctp[i].compare("itp") == 0){
            ainfl.cat.push_back(0);
        }
        else if(ctp[i].compare("rtp") == 0){
            ainfl.cat.push_back(1);
        }
        else if(ctp[i].compare("ctp") == 0 ){
            ainfl.cat.push_back(2);
        }
        else if(ctp[i].compare("btp") == 0 ){
            ainfl.cat.push_back(3);
        }
        else {
            cout<<"in"<<endl;
            cout<<ctp[i]<<endl;
            int len = tapel.tval.size();
            ainfl.cat.push_back(len);
            tapel.tval.push_back(ctp[i]);
            if(ctp[i].compare("a") == 0){
                tapel.tpoint.push_back(i+1);
                //alen++;  //虚拟
            }
            if(ctp[i].compare("d") == 0){
                tapel.tpoint.push_back(i+1);
                //dlen++;  //虚拟
            }

        }
    }
    for(i = 0; i < tapel.tval.size(); i++){
        cout<<tapel.tval[i] << endl;
    }
    cout<<"********************************************************"<<endl;
}

void writeInS(string name[], string type[], string cat[], int addr[], string l[],
             //string low[], string up[], string ctp[], int clen[], string id[], string of[], string tp[],
             Synbl& s, Tapel& tapel, int len){
    int i, alen = 0, dlen = 0;
    for(i = 0; i < len; i++){
        s.name.push_back(name[i]);  //名字
        if(type[i].compare("itp") == 0){
            s.typ.push_back(0);


        }
        else if(type[i].compare("rtp") == 0){
            s.typ.push_back(1);
        }
        else if(type[i].compare("ctp") == 0){
            s.typ.push_back(2);
        }
        else if(type[i].compare("btp") == 0){
            s.typ.push_back(3);
        }
        else {
            int len = tapel.tval.size();
            s.typ.push_back(len);
            tapel.tval.push_back(type[i]);
            if(type[i].compare("a") == 0){
                tapel.tpoint.push_back(alen);
                alen++;  //虚拟
            }
            if(type[i].compare("d") == 0){
                tapel.tpoint.push_back(dlen);
                dlen++;  //虚拟
            }

        }
        s.cat.push_back(cat[i]);
        s.addr.push_back(addr[i]);
        if(l[i].compare("y") == 0)
            s.IsAct.push_back(true);
        else s.IsAct.push_back(false);
    }
}


allCode getAll()
{

    allCode allcode;

     PUSH(100);
     PUSH(51);
     NEXT();

    while(Stack_Address>=0){

    POP();

    if(fx>=0&&fx<=33){

       if(fx==Token_to_code(Current_Token_cat,Current_Token_key)){

        NEXT();
        continue;

       }
       else{
        cout<<"Error111"<<endl;
       }
    }
   else if((fx>=51&&fx<=74)||(fx>=101&&fx<=127)){////////////////////////////
       if(Search_LL1_Excel()){

        continue;

       }
       else{

         cout<<"Error222"<<endl;
         cout<<fx<<endl;
         cout<<Token_Address<<endl;
         cout<<Token[Token_Address].Table_cat<<endl;
         cout<<Token[Token_Address].Table_key<<endl;

       }

    }
   else if(Token_to_code(Current_Token_cat,Current_Token_key)==100){

       cout<<endl;
       cout<<endl;
       cout<<"LL(1):Victory!"<<endl;
    }
   else
       cout<<"Error333";
  }


       cout<<endl;
       cout<<endl;
       cout<<"----生成四元式----"<<endl;
       cout<<endl;

    for(int j=0;j<ge;j++){
        cout<<"  "<<"("<<destination[j]<<","<<destination[j+1]<<","<<destination[j+2]<<","<<destination[j+3]<<")"<<endl;
        j=j+3;
    }

     cout<<endl;
     cout<<endl;
     cout<<"----符号表----"<<endl;
     cout<<endl;

    for(int j=0;j<Synbl_Address;j++){
        cout<<"  "<<"("<<Name[j]<<","<<Type[j]<<","<<Cat[j]<<","<<Address[j]<<","<<L[j]<<")"<<endl;
    }
    Synbl sy;
    Tapel tapel_t;
    tapel_t.tval.push_back("itp"); tapel_t.tpoint.push_back(-1);
    tapel_t.tval.push_back("rtp"); tapel_t.tpoint.push_back(-1);
    tapel_t.tval.push_back("ctp"); tapel_t.tpoint.push_back(-1);
    tapel_t.tval.push_back("btp"); tapel_t.tpoint.push_back(-1);
    writeInS(Name, Type, Cat, Address, L, sy, tapel_t, Synbl_Address);

     cout<<endl;
     cout<<endl;
     cout<<"----数组表----"<<endl;
     cout<<endl;

    for(int j=0;j<AINFL_Address;j++){
        cout<<"  "<<"("<<Low[j]<<","<<Up[j]<<","<<Ctp[j]<<","<<Clen[j]<<")"<<endl;
    }
    Ainfl ain;
    writeInA(Low, Up, Ctp, Clen, ain, tapel_t, AINFL_Address);

     cout<<endl;
     cout<<endl;
     cout<<"----结构体表----"<<endl;
     cout<<endl;

    for(int j=0;j<RINFL_Address;j++){
        cout<<"  "<<"("<<ID[j]<<","<<OFF[j]<<","<<TP[j]<<")"<<endl;
    }
    Dinfl df;
    writeInR(ID, OFF, TP, df, tapel_t, RINFL_Address);
    res_All res_all = divide(destination, ge);
    for(int j=0;j<ge;j++){
        res_all.quat = res_all.quat + destination[j] + ","+destination[j+1] + "," + destination[j+2] + ","+destination[j+3] + "\x0a\x0d";
        j=j+3;
    }
    cout<<endl<<endl<<endl;
    cout<<res_all.quat<<endl;
    cout<<res_all.opti<<endl;
    cout<<res_all.aimCode<<endl;
    cout<<res_all.res<<endl;
    cout<<endl<<endl<<endl;
    int i;
    for(i = 0; i < sy.name.size(); i++){
        cout<<sy.name[i]<<"  "<<tapel_t.tval[sy.typ[i]]<<"  "<<sy.cat[i]<<sy.addr[i]<<endl;
    }
    cout<<endl;
    for(i = 0; i < tapel_t.tval.size(); i++){
        cout<<tapel_t.tval[i] << endl;
    }
    cout<<endl;
    for(i = 0; i < ain.low.size(); i++){
        cout<<ain.low[i]<<" "<<ain.up[i]<<" "<<tapel_t.tval[ain.cat[i]]<<" "<<ain.clen[i]<<endl;
    }
    cout<<endl;
    for(i = 0; i < df.id.size(); i++){
        cout<<df.id[i]<<"  "<<tapel_t.tval[df.tp[i]]<<"  "<<df.off[i]<<endl;
    }
    allcode.res = res_all;
    allcode.synbl = sy;
    allcode.tapel = tapel_t;
    allcode.ainfl = ain;
    allcode.dinfl = df;
    return allcode;
}
