#include<bits/stdc++.h>

using namespace std;

void print(int* a, int len){
    for (int i = 0; i < len; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
}

void bubble_sort(int* a, int len){
    bool label = false;
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len - i - 1; j++){
            if (a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                label = true;
            }
        }
        if (!label){
            break;
        }
    }
}


int main(){
    int n = 8;
    int a[n] = {1, 9, 3, 6, 0, 2358, 8, 0};
    bubble_sort(a, n);
    print(a, n);
    return 0;
}
