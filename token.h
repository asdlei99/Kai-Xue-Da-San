#include <bits/stdc++.h>
using namespace std;
/*
-----------------------------------------------������ű�-----------------------------------------------
*/
//���ű�ṹ��
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
int const_i=1; //������ĩβ
int ii=1; //��ʶ����ĩβ
int cc=1; //�ַ���ĩβ
int ss=1; //�ַ�����ĩ


/*
-------------------------------------------token�ඨ��--------------------------------------------------
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

int curlin_num=1;  //��ǰ����
vector<int> line_num;  //��ӦToken���е�����
double const_value=0;
string str[1000]= {};
int str_index=0;
char phrase[50]= {};
char flag[10]= {"continue"}, e[10]= {"error"}, t[10]= {"return"}, r[10]= {"next"};
int index=0, state=1;
map<int, string> K_keywords; //�ؼ���
map<int, string> P_delimiters; //���
/*P: ��� K: �ؼ��� I: ��ʶ�� C: ���� c: �ַ� S: �ַ���*/
char KT[14][10]= {"main","void", "int", "float", "char", "if", "else", "while", "break", "return",
                  "continue", "struct"
                 };
char PT[40][10]= {";", ",", "(", ")", "[", "]", "{", "}", "=", ">", "<", "==", "<=", ">=", "!=", "+", "-",
                  "*", "/", "^", "%", "+=", "-=", "*=", "/=", ":", ".", "e", "\'", "\"", "\\", "&", "|", "!", "&&", "||",
                  "<<", ">>"
                 };

/*�����Զ���*/
bool hasE=false; //�ж��Ƿ���eָ��
float Em=0; //Eָ��: Em e En
int En=0;
bool EnSign=true; //true: EnΪ�� false: EnΪ��
bool IsChar=false; //�ж��ַ���־
bool IsString=false; //�ж��ַ�����־


/*
----------------------------------------��������--------------------------------------------
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

int findToken(char phrase[])   //Ѱ�ҺϷ��ַ���������Token����
{
    str[str_index]=phrase;
    str_index++;
    int s=0;
    token tk;
    if(IsChar==true)
    {
        IsChar=false;
        char c_value=phrase[0];
        CHARL.c.push_back(c_value);//�ʷ�����
        tk.setToken('c', cc);//����ű�
        cc++;//��βָ����һ
        Token.push_back(tk);//����token����
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
    /*���ж��Ƿ��ڹؼ��ֱ���*/
    else if((phrase[0]>='a'&&phrase[0]<='z')||(phrase[0]>='A'&&phrase[0]<='Z'))
    {
        for(int j=1; j<=12; j++)
        {
            if(strcmp(phrase, K_keywords[j].c_str())==0)
            {
                /*��phrase��K_keywords��ÿһ��һά��������ַ����Ƚϣ�
                ���һ����ֱ��ѹ��Token���У����ؽ�����
                �����һ������ִ�����������Ƿ��������ؼ���
                ѭ�����������ǹؼ��ֵĻ������Ǳ�ʶ��*/
                tk.setToken('K', j);
                cout<<"<K,"<<j<<">"<<endl;
                Token.push_back(tk);
                line_num.push_back(curlin_num);
                return 0;
            }
        }

        //�����ʶ����
        string name_value=phrase;
        bool name_flag=false; //true: �ڱ��� false: δ�ڱ���
        for(int i=0; i<SYNBL.name.size(); i++)
        {
            string s_value=SYNBL.name[i];
            if(name_value==s_value)
            {
                /*����ڱ��������ű�
                    ���ڱ��д���ʶ����������ű�*/
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
            /*��Ϊ���ڱ�����ʱ��ָ�����һλ*/
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


        //���볣����
        bool const_flag=false; //true: �ڱ��� false: δ�ڱ���
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

        //cout<<"<C,"<<const_value<<">"<<endl;//�ʷ�����
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
char* stateChange(char ch)   //����ch�ı��Զ���״̬���жϴʷ��Ƿ���ȷ
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
            cout<<"\n�ʷ���������"<<endl;
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
            memset(phrase,0,sizeof(phrase)/sizeof(char));//phrase�������
            index=0;
            state=1;//�ص���ʼ״̬
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
            cout<<"\n�ʷ���������"<<endl;
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
                cout<<"\n�ʷ���������"<<endl;
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
            cout<<"\n�ʷ���������"<<endl;
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
            cout<<"\n�ʷ���������"<<endl;
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
            cout<<"\n�ʷ���������"<<endl;
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
            cout<<"\n�ʷ���������"<<endl;
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
        cout<<"\n�ʷ���������"<<endl;
        return e;
    }
}


char fileName[20]="test.txt";
void CIFA()
{
    char ch='a', re[50]= {""};
    int count=0;
    //cout<<"�������ļ�����(��test.txt)"<<endl;
    //cin>>fileName;
    FILE* fp=fopen(fileName, "r"); //c�ļ���ȡ����
    initial();
    while((ch=fgetc(fp)) != EOF)
    {

        memset(re, 0, sizeof(re)/sizeof(char)); //chÿǰ��һλ�����re
        strcpy(re, stateChange(ch)); //��ȡ��ǰ�Զ���״̬�����Դ�������Ӧ
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

