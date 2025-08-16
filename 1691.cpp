#include <bits/stdc++.h>

using namespace std;

int n, nums[100005];

struct tree_node{
    unsigned int left = 0;
    unsigned int right = 0;
}tree[100005];


void tree_built(unsigned int index){
    if (index * 2 > n){
        return;
    }
    if (index * 2 + 1 > n){
        tree[index].left = index * 2;
    }
    else {
        tree[index].left = index * 2;
        tree[index].right = index * 2 + 1;
        tree_built(index * 2);
        tree_built(index * 2 + 1);
    }
}


void mirror(unsigned int index){
    tree[index].left ^= tree[index].right;
    tree[index].right ^= tree[index].left;
    tree[index].left ^= tree[index].right;

    if (tree[index].left){mirror(tree[index].left);}
    if (tree[index].right){mirror(tree[index].right);}
}


void bfs(){
    queue<unsigned int> q;

    q.push(1);
    while (!q.empty()){
        unsigned int tmp = q.front();
        q.pop();
        if (!tmp){
            continue;
        }
        cout << nums[tmp] << ' ';
        q.push(tree[tmp].left);
        q.push(tree[tmp].right);
    }
    cout << endl;
}


void vlr(unsigned int index){
    cout << nums[index] << ' ';
    if (tree[index].left){
        vlr(tree[index].left);
    }
    if (tree[index].right){
        vlr(tree[index].right);
    }
}


void ldr(unsigned int index){
    if (tree[index].left){
        ldr(tree[index].left);
    }
    cout << nums[index] << ' ';
    if (tree[index].right){
        ldr(tree[index].right);
    }
}


void lrd(unsigned int index){
    if (tree[index].left){
        lrd(tree[index].left);
    }
    if (tree[index].right){
        lrd(tree[index].right);
    }
    cout << nums[index] << ' ';
}


int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    tree_built(1);
    mirror(1);

    bfs();
    vlr(1);
    cout << endl;
    ldr(1);
    cout << endl;
    lrd(1);
    cout << endl;
    return 0;
}