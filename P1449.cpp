#include <bits/stdc++.h>

using namespace std;

stack<int> nums; /* NOLINT */
char c;
int n, i, j;

int main(){
    while (true){
        c = char(getchar());

        if (c == '@'){
            break;
        }

        switch (c) {
            case '+':
                i = nums.top();
                nums.pop();
                j = nums.top();
                nums.pop();
                nums.push(i + j);
                break;

            case '-':
                i = nums.top();
                nums.pop();
                j = nums.top();
                nums.pop();
                nums.push(j - i);
                break;

            case '*':
                i = nums.top();
                nums.pop();
                j = nums.top();
                nums.pop();
                nums.push(i * j);
                break;

            case '/':
                i = nums.top();
                nums.pop();
                j = nums.top();
                nums.pop();
                nums.push(j / i);
                break;

            case '.':
                nums.push(n);
                n = 0;
                break;

            default:
                n = 10 * n + c - '0';

        }
    }

    cout << nums.top() << endl;

    return 0;
}