
#include <iostream>
//#include "Synbl.h"

using namespace std;

string make(string& label, string& op, string& v1, string v2){
    unsigned i = 8, j = 8;
    while(label.size() < i){
        label = label + " ";
    }
    while(op.size() < j){
        op = op + " ";
    }
    if(v1.length() && v2.length())
        v1 = v1 + ",";
    return label + op + v1 + v2;

}

void deserve(string& s){
    unsigned i;
    for(i = 0; i <= (s.size() - 1) / 2; i++){
        s[i] = s[s.size() - 1 - i];
    }
}

int isSingle(string s){

    return 0;
}

vector<string> assembler()
{
    Synbl synbl = SYNBL;
    vector<string> txt;
    vector<int> line;  //ÐÐÊý
    txt.push_back("DSEG    SEGMENT");
    //string label, op, v1, v2;
    vector<string> quat;
    unsigned i, k, j = 0;
    for(i = 0; i < synbl.name.size(); i++){
        //if(synbl.name)
        string s = synbl.name[i];
        while(s.length() < 8){
            s = s + " ";
        }
        txt.push_back(s+ "DD      0");
    }
    txt.push_back("DSEG    ENDS");
    txt.push_back("CSEG    SEGMENT");
    txt.push_back("        ASSUME  CS:CSEG, DS:DSEG");
    txt.push_back("START:  MOV     AX, DSEG");
    txt.push_back("        MOV     DS, AX");
    for(i = 0; i < AimCode.size(); i++){
        quat.push_back(AimCode[i].code);
        cout<<AimCode[i].code<<endl;
    }
    for(i = 0; i < quat.size(); i++){
        string label, op, v1, v2;
        k = 0;
        while(k < quat[i].length() && quat[i][k] != ' '){
            op = op + quat[i][k];
            k++;
        }
        k++;
        while(k < quat[i].length() && quat[i][k] != ','){
            if(quat[i][k] != ' ')
                v1 = v1 + quat[i][k];
            k++;
        }
        k++;
        while(k < quat[i].length()){
            if(quat[i][k] != ' ')
                v2 = v2 + quat[i][k];
            k++;
        }
        if(op.compare("FJ") == 0 || op.compare("TJ") == 0){
            int sum = 0;
            for(k = 0; k < v2.length(); k++){
                if(v2[k]!=' ' && v2[k]!='_')
                    sum = sum * 10 + v2[k] - '0';
            }
            line.push_back(sum);
        }
        if(op.compare("JMP") == 0){
            int sum = 0;
            for(k = 0; k < v2.length(); k++){
                if(v2[k]!=' ' && v2[k]!='_')
                    sum = sum * 10 + v2[k] - '0';
            }
            line.push_back(sum);
        }
    }
    for(i = 0; i < quat.size(); i++){
        string label, op, v1, v2;
        k = 0;
        while(k < quat[i].length() && quat[i][k] != ' '){
            op = op + quat[i][k];
            k++;
        }
        //cout<<op;
        k++;
        while(k < quat[i].length() && quat[i][k] != ','){
            if(quat[i][k] != ' ')
                v1 = v1 + quat[i][k];
            k++;
        }
        //cout<<" "<<v1;
        k++;
        while(k < quat[i].length()){
            if(quat[i][k] != ' ')
                v2 = v2 + quat[i][k];
            k++;
        }
        //cout<<","<<v2<<"  ";
        if(j < line.size() && line[j] == i){
            int t = i;
            string s;
            while(t != 0){
                s = (char)(t % 10 + '0')+s;
                t = t / 10;
            }
            //deserve(s);
            label = "Line" + s + ":";
            j++;
        }
        if(isSingle(v2)){
            v1 = "AL";
        }
        else{
            if(v1.compare("15") != 0)
            v1 = "AX";
        }
        if(op.compare("LD") == 0){
           op = "MOV";
        }
        else if(op.compare("ST") == 0){
            op = "MOV";
            string s;
            s = v1;
            v1 = v2;
            v2 = s;
        }
        else if( op.compare("LT") == 0 || op.compare("GT") == 0 || op.compare("EQ") == 0 || op.compare("LE") == 0 ||
        op.compare("GE") == 0 || op.compare("NE") == 0 || op.compare("AND") == 0 || op.compare("OR") == 0 ){
            string op1 = op;
            op = "MOV";
            v2 = v1 + " " + op1 + " " + v2;
        }
        else if(op.compare("MUL") == 0 || op.compare("DIV") == 0){
            v1 = "";
        }
        else if(op.compare("FJ") == 0){
            string s = "        "; s = s + "CMP     "; s = s + v1; s = s + ",0H";
            txt.push_back(s);
            op = "JE";
            v1 =  "Line" + v2;
            v2 = "";
        }
        else if(op.compare("TJ") == 0){
            string s = "        "; s = s + "CMP     "; s = s + v1; s = s + ",0H";
            txt.push_back(s);
            op = "JNE";
            v1 =  "Line" + v2;
            v2 = "";
        }
        else if(op.compare("NO") == 0){
            op = "MOV";
            v2 =  op + " " + v1;
        }
        else if(op.compare("JMP") == 0){
            v1="Line"+v2;
            v2="";
        }
        //cout<<v1<<endl;
        string s = make(label, op, v1, v2);
        txt.push_back(s);
    }
    if(j == line.size())
        txt.push_back("        MOV     AH,4CH");
    else{
        int t = line[j];
        cout<<t<<endl;
        string s;
        while(t != 0){
            s = (char)(t % 10 + '0') + s;
            t = t / 10;
        }
        s = "Line" + s + ":";
        while(s.size() < 8)
            s = s + " ";
        txt.push_back(s+"MOV     AH,4CH");
    }
    txt.push_back("        INT     21H");
    txt.push_back("CSEG    ENDS    ");
    txt.push_back("        END     START");
    for(i = 0; i < txt.size(); i++){
        cout<<txt[i]<<endl;
    }
    return txt;
}
