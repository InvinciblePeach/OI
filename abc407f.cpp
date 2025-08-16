#include <bits/stdc++.h>
#define int long long

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 10;
int n, a[MAXN], B[MAXN], C[MAXN], L[MAXN], R[MAXN];
stack<int> st;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.top()] <= a[i])
            st.pop();
        L[i] = st.empty() ? i : i - st.top();
        st.push(i);
    }
    while (!st.empty())
        st.pop();
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && a[st.top()] < a[i])
            st.pop();
        R[i] = st.empty() ? (n - i + 1) : (st.top() - i);
        st.push(i);
    }

    for(int i=1;i<=n;i++){
        int s = min(L[i], R[i]), b = max(L[i], R[i]), len = L[i] + R[i];
        if(s >= 1){
            C[1] += a[i];
            C[s + 1] -= a[i];
        }
        if (s + 1 <= b) {
            B[s + 1] += a[i] * s;
            B[b + 1] -= a[i] * s;
        }
        if (b + 1 <= len - 1) {
            C[b + 1] += -a[i];
            C[len] -= -a[i];
            B[b + 1] += a[i] * len;
            B[len] -= a[i] * len;
        }
    }

    for (int k = 1; k <= n; k++) {
        C[k] += C[k - 1];
        B[k] += B[k - 1];
        cout << C[k] * k + B[k] << '\n';
    }

    return 0;
}