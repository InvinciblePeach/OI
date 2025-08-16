#include<bits/stdc++.h>

using namespace std;

void print(int* a, int len){
    for (int i = 0; i < len; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
}

int ground_partition(int* a, int i, int j){
    int pivot = a[i];
    while (i < j){
        while (a[j] >= pivot && i < j){
                j--;
        }
        a[i] = a[j];
        while (a[i] <= pivot && i < j){
            i++;
        }
        a[j] = a[i];
    }
    a[i] = pivot;
    return i;
}

void quick_sort(int* a, int i, int j){
    if (i >= j){
        return;
    }
    else{
        int p_i = ground_partition(a, i, j);
        quick_sort(a, i, p_i - 1);
        quick_sort(a, p_i + 1, j);
    }
}

int main(){
    int b[] = {3, 5, 1, 2, 4};
    quick_sort(b, 0, 4);
    print(b, 5);
    return 0;
}

