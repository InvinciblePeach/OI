#include <bits/stdc++.h>

using namespace std;

int n, m, P, nums[100005], tree[400010], mark_add[400010] = {0}, mark_times[400010];

inline void push_up(const long long & p){
    tree[p] = tree[p * 2] + tree[p * 2 + 1] % P;
}

inline void build(const long long & l = 1, const long long & r = n, const long long & p = 1){
    if (l == r){
        tree[p] = nums[l] % P;
        return;
    }

    long long mid = (l + r) / 2;
    build(l, mid, p * 2);
    build(mid + 1, r, p * 2 + 1);
    push_up(p);
}

inline void push_down_add(const long long & p, const long long & len){
    mark_add[p * 2] += mark_add[p] % P;
    mark_add[p * 2 + 1] += mark_add[p] % P;
    tree[p * 2] += mark_add[p] * (len - len / 2) % P; // NOLINT
    tree[p * 2 + 1] += mark_add[p] * (len / 2) % P; // NOLINT
    mark_add[p] = 0;
}

void update_add(const long long & d, const long long & cl = 1, const long long & cr = n, const long long & l = 1, const long long & r = n, const long long & p = 1){
    if (cl > r || cr < l){
        return;
    } else if (cl >= l && cr <= r){
        tree[p] += d * (cr - cl + 1) % P; // NOLINT
        if (cr > cl){ mark_add[p] += d % P; } // NOLINT
    } else{
        long long mid = (cl + cr) / 2;

        push_down_add(p, cr - cl + 1);

        update_add(d, cl, mid, l, r, p * 2);
        update_add(d, mid + 1, cr, l, r, p * 2 + 1);

        push_up(p);
    }
}

inline void push_down_times(const long long & p, const long long & len){
    mark_add[p * 2] *= mark_add[p] % P;
    mark_add[p * 2 + 1] *= mark_add[p] % P;
    tree[p * 2] *= mark_add[p] * (len - len / 2) % P; // NOLINT
    tree[p * 2 + 1] *= mark_add[p] * (len / 2) % P; // NOLINT
    mark_add[p] = 1;
}

void update_times(const long long & d, const long long & cl = 1, const long long & cr = n, const long long & l = 1, const long long & r = n, const long long & p = 1){
    if (cl > r || cr < l){
        return;
    } else if (cl >= l && cr <= r){
        tree[p] += d * (cr - cl + 1) % P; // NOLINT
        if (cr > cl){ mark_add[p] *= d % P; } // NOLINT
    } else{
        long long mid = (cl + cr) / 2;

        push_down_times(p, cr - cl + 1);

        update_times(d, cl, mid, l, r, p * 2);
        update_times(d, mid + 1, cr, l, r, p * 2 + 1);

        push_up(p);
    }
}

long long get_sum(long long l, long long r, long long cl = 1, long long cr = n, long long p = 1){
    if (cl > r || cr < l) {
        return 0;
    }

    else if (cl >= l && cr <= r){
        return tree[p];
    }

    else {
        long long mid = (cl + cr) / 2;

        push_down_add(p, cr - cl + 1);
        push_down_times(p, cr - cl + 1);

        return get_sum(l, r, cl, mid, p * 2) + get_sum(l, r, mid + 1, cr, p * 2 + 1);
    }
}

int main(){
    fill(mark_times, mark_times + 40005, 1);

    cin >> n >> m >> P;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    build();

    for (int i = 1; i <= m; i++){
        int op;
        long long l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            long long d;
            cin >> d;
            update_times(d, l, r);
        } else if (op == 2){
            long long d;
            cin >> d;
            update_add(d, l, r);

        } else if (op == 3){
            cout << get_sum(l, r) << endl;
        }
    }

    return 0;
}