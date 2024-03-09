#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, n; cin >> x >> n;
    multiset<int> ms;
    set<int> s;
    s.insert(0); s.insert(x);
    ms.insert(x);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        set<int>::iterator upper = s.upper_bound(num);
        // cout << "upper?  "<< *upper << "\n";
        set<int>::iterator lower = --s.upper_bound(num);
        // cout << "searching for: " << *upper << " " << *lower << "\n";
        ms.erase(ms.find(*upper - *lower));
        ms.insert(*upper - num);
        ms.insert(num - *lower);
        s.insert(num);
        cout << *--ms.end() << "\n";
    }

    return 0;
}