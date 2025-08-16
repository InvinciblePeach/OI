#include<bits/stdc++.h>

using namespace std;

string eq;

vector<string> split(string &str, char n = '='){
    vector<string> a;
    string tmp = "";
    for (auto i: str){
        if (i == n){
            a.push_back(tmp);
            tmp.clear();
        }
        else{
            tmp += i;
        }
    }
    a.push_back(tmp);
    return a;
}

string district(string &v, int left, int right){
    string ans = "";
    for (int i = left; i < right; i++){
        ans += v[i];
    }
    return ans;
}

vector<string> getNode(string &a){
    int start = 0;
    vector<string> nodes;
    for (int i = 1; i < a.size(); i++){
        if (a[i] == '+' || a[i] == '-'){
            nodes.push_back(district(a, start, i));
            start = i;
        }
    }
    nodes.push_back(district(a, start, a.size()));
    return nodes;
}

void getAns(vector<string> &left, vector<string> &right){
    string unknown;
    for (char i: eq){
        if (isalpha(i)){
            unknown = i;
            break;
        }
    }
    int nleft = 0;
    int nright = 0;
    for (string i: left){
        if (isalpha(*(i.end() - 1))){
            if (i.size() == 2){
                string tmp = "1";
                nleft += stoi(i[0] + tmp);
            }
            else{
                nleft += stoi(district(i, 0, i.size()));
            }
        }
        else if (isdigit(*(i.end() - 1))){
            nright += -stoi(i);
        }
    }
    for (string i: right){
        if (isalpha(*(i.end() - 1))){
            if (i.size() == 2){
                string tmp = "1";
                nleft += -stoi(i[0] + tmp);
            }
            else{
                nleft += -stoi(district(i, 0, i.size()));
            }
        }
        else if (isdigit(*(i.end() - 1))){
            nright += stoi(i);
        }
    }
    cout << unknown + "=" << fixed << setprecision(3) << (double(nright) / nleft == 0? abs(double(nright) / nleft): double(nright) / nleft);
}

int main(){
    cin >> eq;
    string left = split(eq)[0];
    string right = split(eq)[1];
    if (left[0] != '-'){
        left = "+" + left;
    }
    if (right[0] != '-'){
        right = "+" + right;
    }
    vector<string> left_nodes = getNode(left);
    vector<string> right_nodes = getNode(right);
    getAns(left_nodes, right_nodes);
    return 0;
}
