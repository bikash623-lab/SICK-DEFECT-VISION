#include <iostream>
using namespace std;

int calsum(int a, int b){
    return a + b;
}

int main(void){
    int x,y;
    cout <<"Enter x & y:";
    cin >> x >> y;
    int sum = calsum(x,y);
    cout <<"sum:" << sum << endl;

    return 0;
}