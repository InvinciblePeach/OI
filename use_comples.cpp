#include<bits/stdc++.h>
#include "complex.cpp"

using namespace std;

int main(){
    _complex a(1, 2), b(2, 3);
    cout << "a:" << a << " b:" << b << endl << endl;

    cout << "a > b?: ";
    if (a > b){
        cout << "TRUE";
    }
    else{
        cout << "FALSE";
    }
    cout << endl;


    cout << "a < b?: ";
    if (a < b){
        cout << "TRUE";
    }
    else{
        cout << "FALSE";
    }
    cout << endl;

    cout << "a >= b?: ";
    if (a >= b){
        cout << "TRUE";
    }
    else{
        cout << "FALSE";
    }
    cout << endl;

    cout << "a <= b?: ";
    if (a <= b){
        cout << "TRUE";
    }
    else{
        cout << "FALSE";
    }
    cout << endl;

    cout << "a == b?: ";
    if (a == b){
        cout << "TRUE";
    }
    else{
        cout << "FALSE";
    }
    cout << endl;

    cout << "a != b?: ";
    if (a != b){
        cout << "TRUE";
    }
    else{
        cout << "FALSE";
    }
    cout << endl;

    return 0;
}

