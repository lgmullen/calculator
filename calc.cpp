#include <iostream>
#include <cmath>
#include <list>
#include "Stack.h"
#include <ctype.h>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {
    cout.precision(4);
    Stack<double> s;
    bool quit = false;
    string input;
    cout << "enter some operations: " << endl;
    // stringstream class check1
    while(!quit) {
//        getline(cin, input);
            while(cin >> input) {
                if (input == "q") {
                    quit = true;
                    break;
                }
                else if (input == "+") {
                    int tmp = s.pop();
                    int tmp2 = s.pop();
                    s.push(tmp + tmp2);
                }
                else if (input == "-") {
                    if (s.size() < 2) {
                        return -1;
                    }
                    int tmp = s.pop();
                    int tmp2 = s.pop();
                    s.push(tmp2 - tmp);
                }
                else if (input == "*") {
                    if (s.size() < 2) {
                        return -1;
                    }
                    double tmp = s.pop();
                    double tmp2 = s.pop();
                    s.push(tmp2 * tmp);
                }
                else if (input == "/") {
                    if (s.size() < 2) {
                        return -1;
                    }
                    double tmp = s.pop();
                    double tmp2 = s.pop();
                    if (tmp2 == 0) {
                        cout << "Error: Division by zero" << endl;
                        s.push(tmp2);
                        s.push(tmp);
                        break;
                    }
                    s.push(tmp2 / tmp);
                }
                else if (input == "d") {
                    if (s.size() < 1) {
                        return -1;
                    }
                    int tmp = s.pop();
                    s.push(tmp);
                    s.push(tmp);
                }
                else if (input == "n") {
                    if (s.size() < 1) {
                        return -1;
                    }
                    int tmp = s.pop();
                    s.push(tmp * - 1);
                }
                else {
                    s.push(stoi(input));
                }
            }
        cout << s.top();
    }
    return 0;
}
