#include <bits/stdc++.h>

using namespace std;

int n, k, cnt;
int pre[50005], father[50005] /*eat you*/, son[50005]/*you eat*/;
queue<int> nums[5005]; // NOLINT

void merge(int x, int y) {
    if (nums[x].size() > nums[y].size()) { swap(x, y); } // merge the small one (x) into the big one (y)

    if (father[pre[y]] == 0) { father[pre[y]] = father[pre[x]]; }
    else { father[pre[x]] = father[pre[y]]; }

    if (son[pre[y]] == 0) { son[pre[y]] = son[pre[x]]; }
    else { son[pre[x]] = son[pre[y]]; }


    while (!nums[x].empty()) {
        int top = nums[x].front();
        nums[x].pop();
        nums[y].emplace(top);
        pre[top] = pre[y];
        father[x] = father[y];
        son[x] = son[y];
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
        pre[i] = i;
    }
    for (int i = 1; i <= k; i ++) {
        int opr, x, y;
        cin >> opr >> x >> y;

        if (x > n || y > n) { end_ ++; continue; }
        if (opr == 1 && ((father[x] != father[y] && father[x] != 0 && father[y] != 0) ||
        (son[x] != son[y] && son[x] != 0 && son[y] != 0))) { cnt ++; continue; }
        if (opr == 2 && x == y) { cnt ++; continue; }
        if (opr == 2 && pre[x] == pre[y]) { cnt ++; continue; }
        if (opr == 2 && son[x] != father[y] && son[y] != father[x]) { cnt ++; continue; }

        if (opr == 1) {
            merge(x, y);
        } else {
            father[y] = pre[x];
            son[x] = pre[y];
        }
    }

    cout << endl;

    cout << cnt << endl;
}