#include <bits/stdc++.h>
using namespace std;
/*
-----------------------------------------------定义符号表-----------------------------------------------
*/
//符号表结构类
class stringl
{
public:
    vector<string> s;
};

class charl
{
public:
    vector<char> c;
};

class Lenl
{
public:
    vector<int> len;
};

class Consl
{
public:
    vector<double> con;
};

class Dinfl
{
public:
    vector<string> id;
    vector<int>  off, tp;
    int level;
    Dinfl(string id)
    {
        this->id[0] = id;
        level = 0;
    }
    Dinfl()
    {
        level = -1;
    }
    void add(string id, string type)
    {
        this->id[++level] = id;
    }
    int getLevel()
    {
        return level;
    }
};

class Tapel
{
public:
    vector<string> tval;
    vector<int>   tpoint;
    string s[6] = {"i", "r", "c", "b", "a", "d"};
};

class Ainfl
{
public:
    vector<int> low, up, clen, cat;
    int level;
    Ainfl(int low, int up)
    {

    }
    Ainfl()
    {
        level = -1;
    }
    void add(int low, int up)
    {
        this->low[++level] = low;
        this->up[level] = up;
    }
    int getLevel()
    {
        return level;
    }

};

class Pfinfl
{
public:
    vector<int> level, off, fn, entry;
    Pfinfl()
    {

    }
};

class Synbl
{
public:
    vector<string> name, cat, addr_table;
    vector<bool> IsAct;
    vector<int> typ, addr;
    string cat_arr[7]= {"f", "C", "t", "d", "v", "vn", "vf"};
    int type_last=1, pfinf_last=1, cons_last=1, len_last=1, val_last=1;
    void add(string name_value, string cat_value)
    {
        name.push_back(name_value);
        cat.push_back(cat_value);
        typ.push_back(type_last);
        type_last++;
    }
};

Synbl SYNBL;
Pfinfl PFINFL;
Ainfl AINFL;
Tapel TAPEL;
Dinfl RINFL;
Consl CONSL;
Lenl LENL;
charl CHARL;
stringl STRINGL;

int tt=0;//
int const_i=1; //常数表末尾
int ii=1; //标识符表末尾
int cc=1; //字符表末尾
int ss=1; //字符串表末


/*
-------------------------------------------token类定义--------------------------------------------------
*/
class token
{
public:
    char Table_cat;
    int Table_key;
    void setToken(char T, int K)
    {
        Table_cat=T;
        Table_key=K;
    };
};
vector<token> Token;

int curlin_num=1;  //当前行数
vector<int> line_num;  //对应Token序列的行数
double const_value=0;
string str[1000]= {};
int str_index=0;
char phrase[50]= {};
char flag[10]= {"continue"}, e[10]= {"error"}, t[10]= {"return"}, r[10]= {"next"};
int index=0, state=1;
map<int, string> K_keywords; //关键字
map<int, string> P_delimiters; //界符
/*P: 界符 K: 关键字 I: 标识符 C: 常数 c: 字符 S: 字符串*/
char KT[14][10]= {"main","void", "int", "float", "char", "if", "else", "while", "break", "return",
                  "continue", "struct"
                 };
char PT[40][10]= {";", ",", "(", ")", "[", "]", "{", "}", "=", ">", "<", "==", "<=", ">=", "!=", "+", "-",
                  "*", "/", "^", "%", "+=", "-=", "*=", "/=", ":", ".", "e", "\'", "\"", "\\", "&", "|", "!", "&&", "||",
                  "<<", ">>"
                 };

/*常数自动机*/
bool hasE=false; //判断是否是e指数
float Em=0; //E指数: Em e En
int En=0;
bool EnSign=true; //true: En为正 false: En为负
bool IsChar=false; //判断字符标志
bool IsString=false; //判断字符串标志


/*
----------------------------------------函数定义--------------------------------------------
*/
void initial()
{
    for(int i=0; i<12; i++)
    {
        K_keywords.insert(map<int, string> :: value_type(i+1, KT[i]));
    }
    for(int i=0; i<38; i++)
    {
        P_delimiters.insert(map<int, string> :: value_type(i+1, PT[i]));
    }
}

int findToken(char phrase[])   //寻找合法字符串并返回Token序列
{
    str[str_index]=phrase;
    str_index++;
    int s=0;
    token tk;
    if(IsChar==true)
    {
        IsChar=false;
        char c_value=phrase[0];
        CHARL.c.push_back(c_value);//词法分析
        tk.setToken('c', cc);//填符号表
        cc++;//表尾指针增一
        Token.push_back(tk);//填入token序列
        line_num.push_back(curlin_num);
    }

    else if(IsString==true)
    {
        IsString=false;
        string s_value=phrase;
        STRINGL.s.push_back(s_value);
        tk.setToken('s', ss);
        ss++;
        Token.push_back(tk);
        line_num.push_back(curlin_num);
    }
    /*先判断是否在关键字表中*/
    else if((phrase[0]>='a'&&phrase[0]<='z')||(phrase[0]>='A'&&phrase[0]<='Z'))
    {
        for(int j=1; j<=12; j++)
        {
            if(strcmp(phrase, K_keywords[j].c_str())==0)
            {
                /*用phrase和K_keywords的每一个一维数组进行字符串比较，
                如果一样，直接压入Token串中，返回结束；
                如果不一样，不执行这条，看是否是其他关键字
                循环结束都不是关键字的话，就是标识符*/
                tk.setToken('K', j);
                cout<<"<K,"<<j<<">"<<endl;
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                return 0;
            }
        }

        //填入标识符表
        string name_value=phrase;
        bool name_flag=false; //true: 在表里 false: 未在表里
        for(int i=0; i<SYNBL.name.size(); i++)
        {
            string s_value=SYNBL.name[i];
            if(name_value==s_value)
            {
                /*如果在表里，填入符号表；
                    不在表里，写入标识符表，填入符号表*/
                tk.setToken('I', i+1);
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                name_flag=true;
            }
        }
        if(name_flag==false)
        {
            SYNBL.add(name_value, "null");
            tk.setToken('I', ii);
            ii++;
            /*因为不在表里，填表时候，指针后移一位*/
            Token.push_back(tk);
            line_num.push_back(curlin_num);
        }
        return 0;
    }

    else if(phrase[0]>='0'&&phrase[0]<='9')
    {
        if(hasE==true)
        {
            if(EnSign==true)
            {
                const_value=Em*pow(10, En);
            }
            else
            {
                const_value=Em*pow(10, 0-En);
                EnSign=true;
            }
            hasE=false;
        }
        else
        {
            const_value=atoi(phrase);
        }


        //填入常数表
        bool const_flag=false; //true: 在表里 false: 未在表里
        for(int i=0; i<CONSL.con.size(); i++)
        {
            double C_value=CONSL.con[i];
            if(const_value==C_value)
            {
                tk.setToken('C', i+1);
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                const_flag=true;
            }
        }
        if(const_flag==false)
        {
            CONSL.con.push_back(const_value);
            tk.setToken('C', const_i);
            Token.push_back(tk);
            line_num.push_back(curlin_num);
            const_i++;
        }

        //cout<<"<C,"<<const_value<<">"<<endl;//词法分析
        return 0;
    }

    else
    {
        for(int j=1; j<38; j++)
        {
            if(strcmp(phrase, P_delimiters[j].c_str())==0)
            {
                tk.setToken('P', j);
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                cout<<"<P,"<<j<<">"<<endl;
                return 0;
            }
        }
    }
}


int flaga=0;
char* stateChange(char ch)   //根据ch改变自动机状态，判断词法是否正确
{
    switch(state)
    {

    case 1:
        if(ch==' '||ch=='\n'||ch=='\t')
        {
            if(ch=='\n')
                curlin_num++;
            return flag;
        }
        else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
        {
            state=2;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch>='0'&&ch<='9')
        {
            state=3;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='\'')
        {
            state=9;
            phrase[index++]=ch;
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return flag;
        }
        else if(ch=='\"')
        {
            state=11;
            phrase[index++]=ch;
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return flag;
        }
        else if(ch=='>')
        {
            state=4;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='<')
        {
            state=5;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='=')
        {
            state=6;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch==','||ch==';'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='['||ch==']')
        {
            phrase[index++]=ch;
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return t;
        }
        else
        {
            cout<<"\n词法分析错误！"<<endl;
            return e;
        }

    case 2:
        if( ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) || (ch>='0'&&ch<='9') )
        {
            state=2;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));//phrase清空重来
            index=0;
            state=1;//回到初始状态
            return r;
        }

    case 3:
        if(ch>='0'&&ch<='9')
        {
            state=3;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='.')
        {
            state=8;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='e' || ch=='E')
        {
            state=14;
            hasE=true;
            Em=atoi(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return flag;
        }
        else
        {
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            state=1;
            return r;
        }

    case 4:
        if(ch=='=')
        {
            state=13;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            state=1;
            return r;
        }

    case 5:
        if(ch=='=')
        {
            state=13;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            state=1;
            return r;
        }

    case 6:
        if(ch=='=')
        {
            state=13;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            state=1;
            return r;
        }

    case 7:
        if(ch>='0'&&ch<='9')
        {
            state=7;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='e')
        {
            state=14;
            hasE=true;
            Em=atoi(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return flag;
        }
        else
        {
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            state=1;
            return r;
        }

    case 8:
        if(ch>='0'&&ch<='9')
        {
            state=7;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            cout<<"\n词法分析出错！"<<endl;
            return e;
        }

    case 9:
        if(ch!='\\')
        {
            state=10;
            phrase[index++]=ch;
            IsChar=true;
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return flag;
        }
        else
        {
            if(flaga==0)
            {
                state=9;
                flaga++;
                return flag;
            }
            else
            {
                cout<<"\n词法分析出错！"<<endl;
                return e;
            }
        }
    case 10:
        if(ch=='\'')
        {
            state=1;
            phrase[index++]=ch;
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            return flag;
        }
        else
        {
            cout<<"\n词法分析出错！"<<endl;
            return e;
        }

    case 11:
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
        {
            state=12;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            cout<<"\n词法分析出错！"<<endl;
            return e;
        }

    case 12:
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
        {
            state=12;
            phrase[index++]=ch;
            return flag;
        }
        else if(ch=='\"')
        {
            state=13;
            IsString=true;
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            cout<<"\n词法分析出错！"<<endl;
            return e;
        }

    case 13:
        findToken(phrase);
        memset(phrase,0,sizeof(phrase)/sizeof(char));
        index=0;
        state=1;
        return r;

    case 14:
        if(ch=='+' || ch=='-')
        {
            state=15;
            if(ch=='-')
            {
                EnSign=false;
            }
            else
            {
                EnSign=true;
            }
            return flag;
        }
        else if(ch>='0'&&ch<='9')
        {
            state=15;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            cout<<"\n词法分析出错！"<<endl;
            return e;
        }

    case 15:
        if(ch>='0'&&ch<='9')
        {
            state=15;
            phrase[index++]=ch;
            return flag;
        }
        else
        {
            En=atoi(phrase);
            findToken(phrase);
            memset(phrase,0,sizeof(phrase)/sizeof(char));
            index=0;
            state=1;
            return r;
        }

    default:
        cout<<"\n词法分析出错！"<<endl;
        return e;
    }
}


char fileName[20]="test.txt";
void CIFA()
{
    char ch='a', re[50]= {""};
    int count=0;
    //cout<<"请输入文件名：(如test.txt)"<<endl;
    //cin>>fileName;
    FILE* fp=fopen(fileName, "r"); //c文件读取操作
    initial();
    while((ch=fgetc(fp)) != EOF)
    {

        memset(re, 0, sizeof(re)/sizeof(char)); //ch每前进一位就清空re
        strcpy(re, stateChange(ch)); //获取当前自动机状态，并以此做出回应
        //cout<<ch<<" : "<<re<<endl;
        if(re=="continue")
            continue;
        else if(re=="error")
            break;
        else if(re=="next"||re=="return")
        {
            if(re=="next")
            {
                fseek(fp, -1L, SEEK_CUR);
            }
        }
    }
    str[str_index++]="#";
    for(int i=0; i<SYNBL.name.size(); i++)
    {
        bool Act=true;
        SYNBL.IsAct.push_back(Act);
    }
    fclose(fp);
}

