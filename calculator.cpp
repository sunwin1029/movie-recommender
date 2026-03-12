#include <iostream>
using namespace std;
// 함수정의
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
double divide(int a, int b) {
    if(b == 0) {
        cout << "Error: 0으로나눌수없습니다!" << endl;
        return 0;
    }
    return static_cast<double>(a) / b;
}
int main() {
    int x = 10, y = 3;
    cout << "=== 계산기테스트===" << endl;
    cout << x << " + " << y << " = " << add(x, y) << endl;
    cout << x << " -" << y << " = " << subtract(x, y) << endl;
    cout << x << " * " << y << " = " << multiply(x, y) << endl;
    cout << x << " / " << y << " = " << divide(x, y) << endl;
    return 0;
}