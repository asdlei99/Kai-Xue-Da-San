
#ifndef TOKEN_OUT_H_INCLUDED
#define TOKEN_OUT_H_INCLUDED



#endif // TOKEN_OUT_H_INCLUDED
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

map<int, string> keyWord; //关键字
map<int, string> delimiters; //界符

int curlin_num=1;  //当前行数
vector<int> line_num;  //对应Token序列的行数

char phrase[50]={}, code[50]={}, zero[50]={}, flag[10]={"!"}, e[10]={"@"}, t[10]={"~"}, r[10]={"r"};
int i=0, state=1, key=0;

//P: 界符 K: 关键字 I: 标识符 C: 常数 c: 字符 S: 字符串
char KT[14][10]={"main", "void", "int", "float", "char", "if", "else", "while", "break", "return",
        "continue", "struct"};  //定义关键字
char PT[40][10]={";", ",", "(", ")", "[", "]", "{", "}", "=", ">", "<", "==", "<=", ">=", "!=", "+", "-",
        "*", "/", "^", "%", "+=", "-=", "*=", "/=", ":", ".", "e", "\'", "\"", "\\", "&", "|", "!", "&&", "||",
        "<<", ">>"}; //定义运算符，界符等

//stateChange()
bool hasE=false; //是否是e指数
float Em=0; //E指数: Em e En
int En=0;
bool EnSign=true; //true: En为正 false: En为负
bool IsChar=false; //判断字符标志
bool IsString=false; //判断字符串标志

//符号表结构类
class stringl{
public:
    vector<string> s;
};

class charl{
public:
    vector<char> c;
};

class Lenl{
public:
    vector<int> len;
};

class Consl{
public:
    vector<double> con;
};

class Dinfl{
public:
    vector<string> id;
    vector<int>  off, tp;
    int level;
    //Typel*  tp;
    Dinfl(string id){
        this->id[0] = id;
        level = 0;
        //setoff()
    }
    Dinfl(){
        level = -1;
    }
    void add(string id, string type){
        this->id[++level] = id;

    }
    int getLevel(){
        return level;
    }
};

class Tapel{
public:
    vector<string> tval;
    //Ainfl*  tpoint;
    vector<int>   tpoint;
    string s[6] = {"i", "r", "c", "b", "a", "d"};
};

class Ainfl{
public:
    //int low, up, clen;
    vector<int> low, up, clen, cat;
    int level;
    Ainfl(int low, int up){

    }
    Ainfl(){
        level = -1;
    }
    void add(int low, int up){
        this->low[++level] = low;
        this->up[level] = up;
        //this.clen[level
        //Typel.add()
        //this.cat =
    }
    int getLevel(){
        return level;
    }

};

class Pfinfl{
public:
    vector<int> level, off, fn, entry;
    //Synbl*  param;
    Pfinfl(){

    }
};

class Synbl{
public:
    //name typ cat addr
    vector<string> name, cat, addr_table;
    vector<bool> IsAct;
    vector<int> typ, addr;
    string cat_arr[7]={"f", "C", "t", "d", "v", "vn", "vf"};
    int type_last=1, pfinf_last=1, cons_last=1, len_last=1, val_last=1;
    void add(string name_value, string cat_value){
        name.push_back(name_value);
        cat.push_back(cat_value);
        typ.push_back(type_last);
        type_last++;
        //类型表创建或新加
    }
};
//

//定义符号表
Synbl SYNBL;
Pfinfl PFINFL;
Ainfl AINFL;
Tapel TAPEL;
Dinfl RINFL;
Consl CONSL;
Lenl LENL;
charl CHARL;
stringl STRINGL;

//token
class token {
    public:
        char Table_cat;
        int Table_key;
        void setToken(char T, int K){
            Table_cat=T;
            Table_key=K;
        };
};
vector<token> Token;
int tt=0;//
int const_i=1; //常数表末尾
int ii=1; //标识符表末尾
int cc=1; //字符表末尾
int ss=1; //字符串表末

//findToken()
double const_value=0;

void initialTable() {
    cout<<"initialTable"<<endl;
    for(int i=0; i<12; i++) {
        keyWord.insert(map<int, string> :: value_type(i+1, KT[i]));
    }
    for(int i=0; i<38; i++) {
        delimiters.insert(map<int, string> :: value_type(i+1, PT[i]));
    }
}

void deserve(string& s, int t){
    if(t>=10)
        cout<<"t"<<t<<endl;
    //unsigned i;
    while(t != 0){
         s = (char)(t % 10 + '0')+s ;
         t = t / 10;
    }

}

string str[1000]={};
int str_int=0;
//stringstream sss;
int findToken(char phrase[]) { //寻找合法字符串并返回Token序列
    str[str_int]=phrase;
	str_int++;

	/*
	cout<<"!"<<" ";
	cout<<"str "<<str[str_int-1]<<" ";
	cout<<"#"<<" ";
	*/

	strcpy(code, phrase);

    token tk;
    if(IsChar==true) {
        IsChar=false;
        char c_value=phrase[0];
        CHARL.c.push_back(c_value);
        tk.setToken('c', cc);
        cc++;
        Token.push_back(tk);
        line_num.push_back(curlin_num);
    }

    else if(IsString==true) {
        IsString=false;
        string s_value=phrase;

        STRINGL.s.push_back(s_value);
        tk.setToken('s', ss);
        ss++;
        Token.push_back(tk);
        line_num.push_back(curlin_num);
    }

    else if((phrase[0]>='a'&&phrase[0]<='z')||(phrase[0]>='A'&&phrase[0]<='Z')) {
        for(int j=1; j<=12; j++) {
            if(strcmp(phrase, keyWord[j].c_str())==0) {
                tk.setToken('K', j);
                cout<<"K "<<j<<endl;
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                return 0;
            }
        }
        //否则填入标识符表
        string name_value=phrase;

        bool name_flag=false; //true: 在表里 false: 未在表里
        for(unsigned int i=0; i<SYNBL.name.size(); i++) {
            string s_value=SYNBL.name[i];
            if(name_value==s_value) {
               tk.setToken('I', i+1);
               Token.push_back(tk);
               line_num.push_back(curlin_num);
               name_flag=true;
            }
        }
        if(name_flag==false) {
            SYNBL.add(name_value, "null");
            tk.setToken('I', ii);
            ii++;
            Token.push_back(tk);
            line_num.push_back(curlin_num);
        }
        return 0;
    }

    else if(phrase[0]>='0'&&phrase[0]<='9') {
        cout<<"c"<<endl;
        if(hasE==true) {
            if(EnSign==true) {
                const_value=Em*pow(10, En);
            }
            else {
                const_value=Em*pow(10, 0-En);
                EnSign=true;
            }
            hasE=false;
        }
        else {

            const_value=atoi(phrase);
        }
        //填入常数表
        bool const_flag=false; //true: 在表里 false: 未在表里
        for(unsigned int i=0; i<CONSL.con.size(); i++) {
            double C_value=CONSL.con[i];
            if(const_value==C_value) {
               tk.setToken('C', i+1);
               Token.push_back(tk);
               line_num.push_back(curlin_num);
               const_flag=true;
            }
        }
        if(const_flag==false) {
            CONSL.con.push_back(const_value);
            tk.setToken('C', const_i);
            Token.push_back(tk);
            line_num.push_back(curlin_num);
            const_i++;
        }
        return 0;
    }

    else {
        for(int j=1; j<38; j++) {
            if(strcmp(phrase, delimiters[j].c_str())==0) {
                tk.setToken('P', j);
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                return 0;
            }
        }
    }
    return 1;
}


int ZhuanYi_count=0;
char* stateChange(char ch) { //根据ch改变自动机状态，判断词法是否正确
    switch(state) {

        case 1:
            if(ch==' '||ch=='\n'||ch=='\t')
            {
                if(ch=='\n')
                    curlin_num++;
                return flag;
            }
            else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) {
                state=2;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch>='0'&&ch<='9') {
                state=3;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='\'') {
                state=9;
                phrase[i++]=ch;
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));

                i=0;
                return flag;
            }
            else if(ch=='\"') {
                state=11;
                phrase[i++]=ch;
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                return flag;
            }
            else if(ch=='>') {
                state=4;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='<') {
                state=5;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='=') {
                state=6;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch==','||ch==';'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='['||ch==']') {
                phrase[i++]=ch;
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                return t;
            }
            else {
                cout<<"\ncode error or other things that we can't recognize!"<<endl;
                return e;
            }

        case 2:
            if( ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) || (ch>='0'&&ch<='9') ) {
                state=2;
                phrase[i++]=ch;
                return flag;
            }
            else {
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        case 3:
            if(ch>='0'&&ch<='9') {
                state=3;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='.') {
                state=8;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='e' || ch=='E') {
                state=14;
                hasE=true;

                Em=atoi(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                return flag;
            }
            else {
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        case 4:
            if(ch=='=') {
                state=13;
                phrase[i++]=ch;
                return flag;
            }
            else {
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        case 5:
            if(ch=='=') {
                state=13;
                phrase[i++]=ch;
                return flag;
            }
            else {
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        case 6:
            if(ch=='=') {
                state=13;
                phrase[i++]=ch;
                return flag;
            }
             else {
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        case 7:
            if(ch>='0'&&ch<='9') {
                state=7;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='e') {
                state=14;
                hasE=true;

                Em=atoi(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                return flag;
            }
            else {
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        case 8:
            if(ch>='0'&&ch<='9') {
                state=7;
                phrase[i++]=ch;
                return flag;
            }
            else {
                cout<<"\ncode error or other things that we can't recognize!"<<endl;
                return e;
            }

        case 9:
            //cout<<"ch:"<<ch<<endl;
            if(ch!='\\') {
                state=10;
                phrase[i++]=ch;
                IsChar=true;
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                return flag;
            }
            else{
                if(ZhuanYi_count==0) {
                   state=9;
                    ZhuanYi_count++;
                    return flag;
                }
                else {
                    cout<<"\nchar type define error"<<endl;
                    return e;
                }
            }

        case 10:
            if(ch=='\'') {
                state=1;
                phrase[i++]=ch;
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                return flag;
            }
            else {
                cout<<"\ncode error or other things that we can't recognize!"<<endl;
                return e;
            }

        case 11:
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')) {
                state=12;
                phrase[i++]=ch;
                return flag;
            }
            else {
                cout<<"\ncode error or other things that we can't recognize!"<<endl;
                return e;
            }

        case 12:
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')) {
                state=12;
                phrase[i++]=ch;
                return flag;
            }
            else if(ch=='\"'){
                state=13;
                IsString=true;
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                phrase[i++]=ch;
                return flag;
            }
            else {
                cout<<"\ncode error or other things that we can't recognize!"<<endl;
                return e;
            }

        case 13:
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            i=0;
            state=1;
            return r;

        case 14:
            if(ch=='+' || ch=='-') {
                state=15;
                if(ch=='-') {
                    EnSign=false;
                }
                else {
                    EnSign=true;
                }
                return flag;
            }
            else if(ch>='0'&&ch<='9'){
                state=15;
                phrase[i++]=ch;
                return flag;
            }
            else {
                cout<<"\ncode error or other things that we can't recognize!"<<endl;
                return e;
            }

        case 15:
            if(ch>='0'&&ch<='9') {
                state=15;
                phrase[i++]=ch;
                return flag;
            }
            else {
                /*
                stringstream ss; //stringstream无法识别正负数(带符号的)
                ss<<phrase;
                ss>>En;
                */
                En=atoi(phrase);
                findToken(phrase);
                memset(phrase,0,sizeof(phrase)/sizeof(char));
                i=0;
                state=1;
                return r;
            }

        default:
            printf("\ncode error or other things that we can't recognize!\n");
            return e;




    }
}


char fileName[100];
void case2() {
    char ch='a', re[50]={""};
    //int count=0;
    //cout<<"file"<<endl;
    FILE* fp=fopen(fileName, "r"); //c文件读取操作
    initialTable();
    //int checkpoint=0;
    //int cpf22y=0;
    //int mem22set=0;
    while((ch=fgetc(fp)) != EOF) {

       //printf("check round %d\n",checkpoint++);
        memset(re, 0, sizeof(re)/sizeof(char)); //ch每前进一位就清空re
         //printf("check memset %d\n",mem22set++);
        strcpy(re, stateChange(ch)); //获取当前自动机状态，并以此做出回应
        //printf("check cpy %d\n",cpf22y++);
        if(re[0]=='!')
            continue;
        else if(re[0]=='@')
            break;
        else if(re[0]=='r'||re[0]=='~') {
            if(re[0]=='r') {
                fseek(fp, -1L, SEEK_CUR);
            }
        }
    }
    printf("checkpoint2dasdasdasdasdasd\n");
    //cout<<"while"<<endl;
    str[str_int++]="#";
    for(unsigned int i=0; i<SYNBL.name.size(); i++) {
        bool Act=true;
        SYNBL.IsAct.push_back(Act);
    }
    fclose(fp);
}
