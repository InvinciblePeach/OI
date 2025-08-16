#include <bits/stdc++.h>

using namespace std;

struct LongLongLong{
    int len = 0;
    int nums[505] = {0};

    int operator[](int i){
        return nums[i];
    }

    explicit LongLongLong(const long long &n){
        string s = "0" + to_string(n);
        for (int i = 1; i < s.size(); i++){
             nums[i] = s[s.size() - i] - '0';
             len++;
        }
    }

    void print(){
        for (int i = 1; i <= len; i++){
            cout << nums[len - i + 1];
        }
    }

    LongLongLong operator+ (LongLongLong other){
        int _max_len = max(len, other.len);
        int num[505] = {0};
        for (int i = 1; i <= _max_len; i++){
            if (nums[i] + other[i] >= 10){
                num[i] += nums[i] + other[i] - 10;
                nums[i + 1] == 
            }
        }
    }
};


int main(){
    return 0;
}