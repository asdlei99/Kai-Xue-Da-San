#include <iostream>
#include <vector>
#include <string>
#include "quadra.h"
#include "optimazition.h"
#include "assembler.h"

using namespace std;

class Block{
public:
    vector<int> sign;
};

class res_All{
public:
    string quat;  //四元式
    string opti;  //优化
    string aimCode; //目标代码
    string res;     //汇编
};


res_All divide(string quat0[], int ge)
{
    int i, k;
    Block block;
    res_All res_all;
    vector<string> res;
    vector<string> quat;
    block.sign.push_back(0);
    for(i = 0; i < ge; i = i + 4){
        string s = quat0[i] + "," + quat0[i + 1] + "," + quat0[i + 2] + "," + quat0[i + 3];
        quat.push_back(s);
    }

    for(i = 0; i < quat.size(); i++){
        string op; k = 0;
        while(k < quat[i].length() && quat[i][k] != ','){
            if(quat[i][k] != '(' && quat[i][k] != ' ')
                op = op + quat[i][k];
            k++;
        }
        //cout<<op<<endl;
        if(op.compare("if") == 0 || op.compare("el") == 0 || op.compare("wh") == 0 || op.compare("do") == 0 || op.compare("we") == 0){
            if(i  < quat.size() - 1)
            block.sign.push_back(i+1);
        }

        if(op.compare("ie") == 0)
            block.sign.push_back(i);
    }
    k = block.sign.size();
    //if(block.sign[k - 1] != 7)
        block.sign.push_back(quat.size());
    for(i = 0; i < block.sign.size()-1; i++){
        cout<<"block: ";
        for(k = block.sign[i]; k < block.sign[i+1]; k++){
            cout<<quat[k]<" ";
        }i++;
    }
    i = 0;

    for(i = 0; i < block.sign.size() - 1; i++){
        vector<string> quat1;
        for(k = block.sign[i]; k < block.sign[i+1]; k++){
            quat1.push_back(quat[k]);
            //cout<<quat[k]<<endl;
        }
        //cout<<"quat"<<endl;
        int m;
        res = optimazite(quat1);
        for(m = 0; m < res.size(); m++){
            res_all.opti = res_all.opti + res[m] + "\x0d\x0a";  //优化代码
        }
        int j;
        for(j = 0; j < res.size(); j++){
            quadra q;
            int k = 0;
            string op, v1, v2, v3;
            while(k < res[j].length() && res[j][k] != ','){
                if(res[j][k] != '(' && res[j][k] != ' ' && res[j][k] != '_')
                    op = op + res[j][k];
                k++;
            }
            q.op = op;
            k++;
            while(k < res[j].length() && res[j][k] != ','){
                if(res[j][k] != ' ')
                    v1 = v1 + res[j][k];
                k++;
            }
            node B;
            B.name = v1;
            if(v1[0] != 't')
               B.IsAct = true;
            else B.IsAct = false;
            q.B = B;
            k++;
            while(k < res[j].length() && res[j][k] != ','){
                if(res[j][k] != ' ')
                    v2 = v2 + res[j][k];
                k++;
            }
            node C;
            C.name = v2;
            if(v2[0] != 't')
              C.IsAct = true;
            else C.IsAct = false;
            q.C = C;
            k++;
            while(k < res[j].length()){
                if(res[j][k] != ' ')
                    v3 = v3 + res[j][k];
                k++;
            }
            node A;
            A.name = v3;
            if(v3[0] != 't')
               A.IsAct = true;
            else A.IsAct = false;
            q.A = A;
            Quadra.push_back(q);
            }
        }

        WriteActState();
        OutputAss();

    for( i=0; i<AimCode.size(); i++) {
        //cout<<AimCode[i].code<<endl;
        res_all.aimCode = res_all.aimCode + AimCode[i].code + "\x0d\x0a";  //目标代码
    }
    cout<<endl<<endl<<endl;


    vector<string> txt = assembler();
    for(i = 0; i < txt.size(); i++){
        res_all.res = res_all.res + txt[i] + "\x0d\x0a";
    }
    return res_all;
}
