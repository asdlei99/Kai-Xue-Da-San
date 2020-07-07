#include "token.h"
#include "parse.h"
#include <bits/stdc++.h>
using namespace std;

void deserve(string& s, int t){
    if(t>=10)
        cout<<"t"<<t<<endl;
    unsigned i;
    while(t != 0){
         s = (char)(t % 10 + '0')+s ;
         t = t / 10;
    }
}


string token_string[1000] = {};
int string_int=0;
void CIFA_in_WINDOW() {
    CIFA();
    token_string[string_int]="";
    for(int i=0; i<Token.size(); i++) {
        char Table_cat_temp[4]="";
        Table_cat_temp[0]=Token[i].Table_cat;
        string str_1 = Table_cat_temp;
        string str_2="";
        cout<<"Token[i].Table_key: "<<Token[i].Table_key<<endl;
        deserve(str_2, Token[i].Table_key);
        cout<<"str_2: "<<str_2<<endl;
        if(i==0)
            token_string[string_int]="<"+str_1+", "+str_2+">"+"\x0d\x0a";
        else
            token_string[string_int]=token_string[string_int]+"<"+str_1+", "+str_2+">"+"\x0d\x0a";
    }
    cout<<token_string[string_int].length()<<endl;
    cout<<"astring_int: "<<string_int<<endl;
    string_int++;
    cout<<"bstring_int: "<<string_int<<endl;



}

int main()
{
    CIFA_in_WINDOW();
}

