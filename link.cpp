/*
关于链表的定义程序
作者：Invincible Peach
最近修改时间：2022/01/20
*/
#include <bits/stdc++.h>

using namespace std;

struct LNode{
    int data;
    LNode* p = nullptr;

    int print_all(){                                  // 输出整个链表
        LNode* tail = this;
        while (tail != nullptr){
            cout << tail -> data << " -> ";
            tail = tail -> p;
        }
        cout << "end" << endl;
        return 0;
    }


    int headin(LNode &other){                         // 使用头插法插入一个节点
        other.p = p;
        p = &other;
        return 0;
    }


    int putin(LNode &other, int index){               // 插入一个节点
        LNode* tail = this;
        for (int cnt = 0; cnt < index; cnt++){
            tail = tail -> p;
        }
        other.p = tail -> p;
        tail -> p = &other;
        return 0;
    }

    int backin(LNode &other){                         // 使用尾插法插入一个节点
        if (p == nullptr){
            p = &other;
        }
        else{
            LNode* tail=p;
            while (tail->p != nullptr){
                tail = tail->p;
            }
            tail->p = &other;
        }
        return 0;
    }

    int index(int index){                             // 索引节点值
        LNode* tail = this;
        for (int cnt = 0; cnt < index; cnt++){
            tail = tail->p;
        }
        return tail->data;
    }

    int del(int index){
        LNode* tail = this;
        for (int cnt = 0; cnt < index - 1; cnt++){   // 删除一个节点
            tail = tail->p;
        }
        tail->p = tail->p->p;
        return 0;
    }
};
// 构造结构体，无需定义主函数
