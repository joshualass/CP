#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    stack<int> s;
    int moves = 0;
    for(int i = 0; i < 2*n; i++) {
        int num; cin >> num;
        if(s.size()) {
            if(num == s.top()) {
                s.pop();
            } else {
                s.push(num);
            }
        } else {
            s.push(num);
        }
        
    }
    cout << (s.empty() ? to_string(2 * n) : "impossible") << "\n";
    return 0;
}