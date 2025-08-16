#include<bits/stdc++.h>
// AC

using namespace std;

int n, k;
vector<int> a;

void mq(){
    deque<int> dq;
    for (int i = 0; i < n; i++){
        if (dq.front() <= i - k){
            dq.pop_front();
        }

        while (!dq.empty()){
            if (a[dq.back()] >= a[i]){
                dq.pop_back();
            }
            else{
                dq.push_back(i);
                break;
            }
        }
        if (dq.empty()){
            dq.push_back(i);
        }

        if (i >= k - 1){
            cout << a[dq.front()] << ' ';
        }
    }

    cout << endl;
    dq.clear();

    for (int i = 0; i < n; i++){
        if (dq.front() <= i - k){
            dq.pop_front();
        }

        while (!dq.empty()){
            if (a[dq.back()] <= a[i]){
                dq.pop_back();
            }
            else{
                dq.push_back(i);
                break;
            }
        }
        if (dq.empty()){
            dq.push_back(i);
        }

        if (i >= k - 1){
            cout << a[dq.front()] << ' ';
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        a.push_back(x);
    }
    mq();
    return 0;
}
