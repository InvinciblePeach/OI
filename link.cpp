/*
��������Ķ������
���ߣ�Invincible Peach
����޸�ʱ�䣺2022/01/20
*/
#include <bits/stdc++.h>

using namespace std;

struct LNode{
    int data;
    LNode* p = nullptr;

    int print_all(){                                  // �����������
        LNode* tail = this;
        while (tail != nullptr){
            cout << tail -> data << " -> ";
            tail = tail -> p;
        }
        cout << "end" << endl;
        return 0;
    }


    int headin(LNode &other){                         // ʹ��ͷ�巨����һ���ڵ�
        other.p = p;
        p = &other;
        return 0;
    }


    int putin(LNode &other, int index){               // ����һ���ڵ�
        LNode* tail = this;
        for (int cnt = 0; cnt < index; cnt++){
            tail = tail -> p;
        }
        other.p = tail -> p;
        tail -> p = &other;
        return 0;
    }

    int backin(LNode &other){                         // ʹ��β�巨����һ���ڵ�
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

    int index(int index){                             // �����ڵ�ֵ
        LNode* tail = this;
        for (int cnt = 0; cnt < index; cnt++){
            tail = tail->p;
        }
        return tail->data;
    }

    int del(int index){
        LNode* tail = this;
        for (int cnt = 0; cnt < index - 1; cnt++){   // ɾ��һ���ڵ�
            tail = tail->p;
        }
        tail->p = tail->p->p;
        return 0;
    }
};
// ����ṹ�壬���趨��������
