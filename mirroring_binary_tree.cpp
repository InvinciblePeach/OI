#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int left = 0, right = 0;
} tree[100001];

int n, seq[100001];

void build(int index);
void dfs(int now_p);

void pre_order(int index);
void in_order(int index);
void post_order(int index);
void bfs();

int main()
{
    cin >> n;
    seq[0] = 0x7f7f7f7f;
    for (int i = 1; i <= n; i++)  {cin >> seq[i]; }

    build(1);
    dfs(1);

    bfs();
    cout << endl;
    pre_order(1);
    cout << endl;
    in_order(1);
    cout << endl;
    post_order(1);
    cout << endl;

    return 0;
}

void build(int index)
{
    if (index * 2 > n)  { return ; }
    if (index * 2 + 1 > n)  { tree[index].left = index * 2; }
    else
    {
        tree[index].left = index * 2;
        tree[index].right = index * 2 + 1;
        build(index * 2);
        build(index * 2 + 1);
    }
}

void dfs(int index)
{
    tree[index].left ^= tree[index].right;
    tree[index].right ^= tree[index].left;
    tree[index].left ^= tree[index].right;

    if (tree[index].left)  { dfs(tree[index].left); }
    if (tree[index].right)  { dfs(tree[index].right); }
}

void pre_order(int index)
{
    cout << seq[index] << ' ';
    if (tree[index].left)  { pre_order(tree[index].left); }
    if (tree[index].right)  { pre_order(tree[index].right); }
}

void in_order(int index)
{
    if (tree[index].left)  { in_order(tree[index].left); }
    cout << seq[index] << ' ';
    if (tree[index].right)  { in_order(tree[index].right); }
}

void post_order(int index)
{
    if (tree[index].left)  { post_order(tree[index].left); }
    if (tree[index].right)  { post_order(tree[index].right); }
    cout << seq[index] << ' ';
}

void bfs()
{
    queue<int> q;

    q.push(1);
    while (q.size())
    {
        auto temp = q.front();

        q.pop();
        if (!temp)  { continue; }

        cout << seq[temp] << ' ';

        q.push(tree[temp].left);
        q.push(tree[temp].right);
    }
}
