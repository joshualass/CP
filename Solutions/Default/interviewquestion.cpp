#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int c, d;
    cin >> c >> d;

    vector<int> fizz(0);
    vector<int> buzz(0);

    for(int i = c; i <= d; i++) {
        string line;
        cin >> line;
        if(line == "Fizz") {
            fizz.push_back(i);
        }
        if(line == "Buzz") {
            buzz.push_back(i);
        }
        if(line == "FizzBuzz") {
            fizz.push_back(i);
            buzz.push_back(i);
        }
    }

    int a = (d == 1000000 ? c - 1 : d + 1);
    int b = (d == 1000000 ? c - 1 : d + 1);
    if(fizz.size() == 1) {
        a = fizz[0];
    }
    if(fizz.size() >= 2) {
        a = fizz[1] - fizz[0];
    }
    if(buzz.size() == 1) {
        b = buzz[0];
    }
    if(buzz.size() >= 2) {
        b = buzz[1] - buzz[0];
    }
    cout << a << ' ' << b << '\n';
    return 0;
}