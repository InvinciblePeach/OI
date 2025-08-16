#include <bits/stdc++.h>

using namespace std;

int n, a[1000005], b[1000005];
long long sum_a[1000005] = {0}, sum_b[1000005] = {0};
int a_lefts[1000005], b_lefts[1000005];
bool flag[1000005] = {false};
bool swap_flag = false;

inline int read() {
    char c = char(getchar());
    int x = 0, num = 1;
    while (c < '0' || c > '9') {
        if (c == '-') num = -1;
        c = char(getchar());
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = char(getchar());
    }
    return x * num;
}

template <typename T>
inline void Swap (T & x, T & y) {
    x ^= y; // NOLINT
    y ^= x; // NOLINT
    x ^= y; // NOLINT
}

int c_i = 0;
int a_l, a_r, b_l, b_r;

int main(){
    n = read();
    for (int i = 1; i <= n; i++){
        a[i] = read();
        sum_a[i] = sum_a[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        b[i] = read();
        sum_b[i] = sum_b[i - 1] + b[i];
    }

    if (sum_a[n] > sum_b[n]){
        swap_flag = true;
        for (int i = 1; i <= n; i++) {
            Swap(a[i], b[i]);
            Swap(sum_a[i], sum_b[i]);
        }
    }

    for (int i = 0; i <= n; i++){
        while (sum_a[i] >= sum_b[c_i] && c_i <= n){
            c_i ++;
        }
        c_i --;

        if (flag[sum_a[i] - sum_b[c_i]]){
            a_l = a_lefts[sum_a[i] - sum_b[c_i]] + 1;
            a_r = i;
            b_l = b_lefts[sum_a[i] - sum_b[c_i]] + 1;
            b_r = c_i;
            break;
        }

        flag[sum_a[i] - sum_b[c_i]] = true;
        a_lefts[sum_a[i] - sum_b[c_i]] = i;
        b_lefts[sum_a[i] - sum_b[c_i]] = c_i;
    }

    if (swap_flag){
        Swap(a_l, b_l);
        Swap(a_r, b_r);
    }

    printf("%d\n", a_r - a_l + 1);

    for (int i = a_l; i <= a_r; i++){
        printf("%d ", i);
    }

    printf("\n%d\n", b_r - b_l + 1);

    for (int i = b_l; i <= b_r; i++){
        printf("%d ", i);
    }
    return 0;
}