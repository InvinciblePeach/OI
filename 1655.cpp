#include<bits/stdc++.h>

using namespace std;

class ticket{
public:
    int time;
    int money;

    ticket(){}

    ticket(int time, int money){
        this -> time = time;
        this -> money = money;
    }

    bool effective(int &time){
        if (time - this -> time <= 45){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(){
    int n;
    cin >> n;
    ticket a[n] = ticket(-46, 0);
    ticket t;
    int num = 0;
    long long all_money = 0;
    for (int i = 0; i < n; i++){
        bool kind;
        int time, money;
        cin >> kind >> money >> time;
        if (!kind){
            t.time = time;
            t.money = money;
            a[num++] = t;
            all_money += money;
        }
        else{
            bool flag = false;
            for (int j = 0; j < n; j++){
                if (a[j].effective(time) && a[j].money >= money){
                    a[j].time = -46;
                    flag = true;
                    break;
                }
            }
            if (!flag){
                all_money += money;
            }
        }
    }
    cout << all_money;
    return 0;
}
