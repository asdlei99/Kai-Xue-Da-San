
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Node{
public:
    vector<string> name; //变量名字
    string op; //运算符
	string load; //不操作的字符串
    string low[2];
    int down[2];
    map<string, int> nodeMap; //符号对应节点map
};

void eraseName(Node& node, string s, map<string, int>& dagMap);
bool isConst(string s){  //常数
    if(s[0] <= '9' && s[0] >= '0')
        return true;
    return false;
}

bool isVc(string s){  //临时变量
    if(s[0] == 't'){
        return true;
    }
    return false;
}

bool isV(string s){
    if(s[0] != 't')
        return true;
    return false;
}

string uniqueString(string s, int sum){
    while(sum != 0){
        s = s + (char)(sum % 10 + '0');
        sum = sum / 10;
    }
    return s;
}

void addNext(Node& node, string s){
    if(node.name.empty()){
        node.name.push_back(s);
        return;
    }
    if(isVc(s)){
        node.name.push_back(s);
        return;
    }
    if(isConst(s)){
        string s2 = node.name[0];
        node.name[0] = s;
        node.name.push_back(s2);
        return;
    }
    if(isV(s)){
        if(isVc(node.name[0])){
            string s2 = node.name[0];
            node.name[0] = s;
            node.name.push_back(s2);
        }
        else
            node.name.push_back(s);
    }
    return;
}

void eraseName(Node& node, string s, map<string, int>& dagMap){
    unsigned k;
    for(k = 1; k < node.name.size(); k++){
        if(node.name[k].compare(s) == 0){
            break;
        }
    }
	if(k < node.name.size()){
        vector<string>::iterator it = node.name.begin() + k;
        node.name.erase(it);
	}
    dagMap.erase(s);
}

string caculate(string s1, string s2, string op){
     int sum1 = 0, sum2 = 0, sum, cofficient = 10;
     unsigned i;
     for(i = 0; i < s1.length(); i++){
         sum1 = sum1 * cofficient + s1[i] - '0';
     }
     for(i = 0; i < s2.length(); i++){
         sum2 = sum2 * cofficient + s2[i] - '0';
     }
     if(op.compare("+") == 0){
         sum = sum1 + sum2;
     }
     if(op.compare("-") == 0){
         sum = sum1 - sum2;
     }
     if(op.compare("*") == 0){
         sum = sum1 * sum2;
     }
     if(op.compare("/") == 0){
         sum = sum1 / sum2;
     }
     string s;
     while(sum != 0){
        s = s + (char)(sum % 10 + '0');
        sum = sum / 10;
     }
     for(i = 0; i <= (s.length() - 1) / 2; i++){
        char ch = s[i];
        s[i] = s[s.length() - i -1];
        s[s.length() - i -1] = ch;
     }
     return s;
}

void equ(string v1, string v3, vector<Node>& dag, map<string, int>& dagMap, int& length){
    if(dagMap.count(v3) > 0){
        int key = dagMap[v3];

        eraseName(dag[key], v3, dagMap);
    }
    if(dagMap.count(v1) == 0){
        Node node;
        dagMap.insert(pair<string, int>(v1, length));
        dagMap.insert(pair<string, int>(v3, length++));
        node.name.push_back(v1);
        addNext(node, v3);  //v1|v3
        dag.push_back(node);
    }
    else{
        Node node = dag[dagMap[v1]];
        addNext(node, v3);
        dag[dagMap[v1]] = node;
        dagMap.insert(pair<string, int>(v3, dagMap[v1]));
    }
}

vector<string> optimazite(vector<string> quat)
{
    //int i;
    unsigned i,k;
	int length = 0;
	vector<string> res;
	vector<Node> dag;
    map<string, int> dagMap;

	for(i = 0; i < quat.size(); i++){
		//cout<<quat[i]<<endl;
	}
    for(i = 0; i < quat.size(); i++){
        string op, v1, v2, v3;
        k = 0;
        while(k < quat[i].length() && quat[i][k] != ','){
            if(quat[i][k] != '(' && quat[i][k] != ' ')
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
        while(k < quat[i].length() && quat[i][k] != ','){
            if(quat[i][k] != ' ')
                v2 = v2 + quat[i][k];
            k++;
        }
        k++;
        while(k < quat[i].length() && quat[i][k] != ')'){
            if(quat[i][k] != ' ')
                v3 = v3 + quat[i][k];
            k++;
        }
        //cout<<i<<endl;
        if(op.compare("=") == 0){

            equ(v1, v3, dag, dagMap, length);
            //cout<<"out"<<endl;
        }
        else if(op.compare("+") == 0 || op.compare("-") == 0 || op.compare("*") == 0 || op.compare("/") == 0){
            if(isConst(v1) && isConst(v2)){  //都是常数
                string s = caculate(v1, v2, op);
                equ(s, v3, dag, dagMap, length);
            }
            else{
                if(dagMap.count(v3) > 0){ //v3节点存在
                    int key = dagMap[v3];
                    eraseName(dag[key], v3, dagMap); //去除v3
                }
                if(dagMap.count(v1) > 0 && dagMap.count(v2) > 0){ //v1, v2存在节点
                    int key1 = dagMap[v1], key2 = dagMap[v2];
                    if(dag[key1].nodeMap.count(uniqueString(op,key2)) > 0 /*&& dag[key2].nodeMap.count(op) > 0*/){  //公共表达式节点存在
                        int key = dag[key1].nodeMap[uniqueString(op,key2)]; //key为公共表达式节点标志
                        addNext(dag[key], v3);
                        dagMap.insert(pair<string, int>(v3, key));
                        //cout<<v1<<" "<<v2<<" in "<<v3<<endl;
                    }
                    else{ //创造新节点
                        //cout<<v1<<" "<<v2<<" out "<<v3<<endl;
                        Node node;
                        addNext(node, v3);
                        node.op = op;
                        node.low[0] = dag[key1].name[0];
                        node.low[1] = dag[key2].name[0];
                        node.down[0] = key1;
                        node.down[1] = key2;
                        dag.push_back(node);  //建立公共表达式节点
                        dagMap.insert(pair<string, int>(v3, length));  //v3索引
                        dag[key1].nodeMap.insert(pair<string, int>(uniqueString(op,key2), length));  //v1指向公公表达式节点
                        dag[key2].nodeMap.insert(pair<string, int>(uniqueString(op,key1), length++)); // v2指向公共表达式节点

                    }
                }
                else{   //v1||v2不存在
                    int key1, key2;
                    if(dagMap.count(v1) == 0){ //v1不存在
                        Node node;
                        addNext(node, v1);
                        dag.push_back(node);
                        dagMap.insert(pair<string, int>(v1, length++));  //v1索引
                    }
                    if(dagMap.count(v2) == 0){ //v1不存在
                        Node node;
                        addNext(node, v2);
                        dag.push_back(node);
                        dagMap.insert(pair<string, int>(v2, length++));  //v1索引
                    }
                    key1 = dagMap[v1];
                    key2 = dagMap[v2];
                    Node node;
                    addNext(node, v3);
                    node.op = op;
                    node.low[0] = dag[key1].name[0];
                    node.low[1] = dag[key2].name[0];
                    node.down[0] = key1;
                    node.down[1] = key2;
                    dag.push_back(node);  //建立公共表达式节点
                    dagMap.insert(pair<string, int>(v3, length));  //v3索引
                    dag[key1].nodeMap.insert(pair<string, int>(uniqueString(op,key2), length));  //v1指向公公表达式节点
                    dag[key2].nodeMap.insert(pair<string, int>(uniqueString(op,key1), length++)); // v2指向公共表达式节点
                }

            }
        }
        else{
            Node node;
			node.load = op + "," + v1 + "," + v2 + "," + v3;
			dag.push_back(node);
			length++;
        }


    }
    for( i = 0; i < dag.size(); i++){
		if(dag[i].load.length() != 0){
			//cout<<dag[i].load<<endl;
			res.push_back(dag[i].load);
		}

        else if(dag[i].op.length() == 0){  //叶节点
            string s,s1;
            unsigned k;
            //if(!dag[i].name.empty()){
                s1 = dag[i].name[0];
            //}
            for(k = 1; k < dag[i].name.size(); k++){
                if(isV(dag[i].name[k])){
                    //cout<<dag[i].name[k]<<"="<<s1<<endl;
					s = "=,"+s1+", ,"+dag[i].name[k];
					res.push_back(s);
                }
            }
        }
        else{
            string s,s1;
            unsigned k;
            //if(!dag[i].name.empty()){
                s1 = dag[i].name[0];
                int key1 = dag[i].down[0], key2 = dag[i].down[1];
                //cout<<s1<<"="<<dag[key1].name[0]<<dag[i].op<<dag[key2].name[0]<<endl;
				s = dag[i].op+","+ dag[key1].name[0] + ","+dag[key2].name[0] + "," + s1;
				res.push_back(s);
            //}
            for(k = 1; k < dag[i].name.size(); k++){
                if(isV(dag[i].name[k])){
                   // cout<<dag[i].name[k]<<"="<<s1<<endl;
					s = "=,"+s1+", ,"+dag[i].name[k];
					res.push_back(s);
                }
            }
        }//节点状态输出
        /*unsigned k;
        for(k = 0; k < dag[i].name.size(); k++){
            cout<<" "<<dag[i].name[k];
        }
        cout<<endl;*/
    }
    return res;
}
