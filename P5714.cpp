#include <bits/stdc++.h>

using namespace std;

double m, h, bmi;

int main(){
    cin >> m >> h;
    bmi = m / (h * h);
    if (bmi < 18.5){
        cout << "Underweight" << endl;
    }
    else if (bmi >= 24){
        cout << bmi << endl << "Overweight" << endl;
    }
    else{
        cout << "Normal" << endl;
    }
    return 0;
}