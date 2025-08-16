#include<bits/stdc++.h>

using namespace std;

void print(int* a, int len){
    for (int i = 0; i < len; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
}

void heapify(int* a, int root_index, int _end){
    int lc_index = 2 * root_index;
    int rc_index = 2 * root_index + 1;
    int max_index = root_index;
    if (lc_index < _end && a[lc_index] > a[max_index]){
        max_index = lc_index;
    }
    if (rc_index < _end && a[rc_index] > a[max_index]){
        max_index = lc_index;
    }

    if (max_index != root_index){
        swap(a[root_index], a[max_index]);
        heapify(a, max_index, _end);
    }
}

void build_original_heap(int* a, int len){
    int n = len - 1;
    for (int i = n / 2; i > 0; i--){
        heapify(a, i, n);
    }
}

void heap_sort(int* a, int len){
    int n = len - 1;
    int _end = n;
    build_original_heap(a, n);
    for (int i = 1; i <= n; i++){
        swap(a[1], a[_end]);
        _end--;
        heapify(a, 1, _end);
    }
}

int main(){
    int n = 8;
    int a[n] = {1, 9, 3, 6, 0, 2358, 8, 0};
    heap_sort(a, n);
    print(a, n);
}
