#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    set<int> s;
    for(int i = 1; i <= n; i++) {
        s.insert(i);
    }
    set<int>::iterator magic = s.begin();
    while(s.size()) {
        if(magic == s.end()) {
            magic = s.begin();
        }
        magic++;
        if(magic == s.end()) {
            magic = s.begin();
        }
        int val = *magic;
        s.erase(magic);
        magic = s.upper_bound(val);
        cout << val << " ";
    }
    cout << "\n";
    return 0;
}