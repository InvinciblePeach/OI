#include<bits/stdc++.h>

using namespace std;

class _complex{
    friend ostream &operator<< (ostream &out, _complex &other);
private:
    int real, i;
    double mod;
public:
    _complex(){}
    _complex(int real, int i){
        this -> real = real;
        this -> i = i;
        this -> mod = sqrt(pow(real, 2) + pow(i, 2));
    }

    _complex operator+ (_complex &other){
        _complex tmp;
        tmp.real = this -> real + other.real;
        tmp.i = this -> i + other.i;
        return tmp;
    }

    _complex operator- (_complex &other){
        _complex tmp;
        tmp.real = this -> real - other.real;
        tmp.i = this -> i - other.i;
        return tmp;
    }

    bool operator> (_complex &other){
        if (this -> i == 0 && other.i == 0){
            return this -> real > other.real;
        }
        else{
            return this -> mod > other.mod;
        }
    }

    bool operator< (_complex &other){
        if (this -> i == 0 && other.i == 0){
            return this -> real < other.real;
        }
        else{
            return this -> mod < other.mod;
        }
    }

    bool operator>= (_complex &other){
        if (this -> i == 0 && other.i == 0){
            return this -> real >= other.real;
        }
        else{
            return this -> mod >= other.mod;
        }
    }

    bool operator<= (_complex &other){
        if (this -> i == 0 && other.i == 0){
            return this -> real <= other.real;
        }
        else{
            return this -> mod <= other.mod;
        }
    }

    bool operator== (_complex &other){
        return this -> real == other.real && this -> i == other.i;
    }

    bool operator!= (_complex &other){
        return !(*this == other);
    }
};

ostream &operator<< (ostream &out, _complex &other){
    out << other.real << '+' << other.i << 'i';
    return out;
}
