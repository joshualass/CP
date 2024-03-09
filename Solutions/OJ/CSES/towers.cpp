#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    multiset<int> ms;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        multiset<int>::iterator it = ms.upper_bound(num);
        if(it != ms.end()) {
            ms.erase(it);
        }
        ms.insert(num);
    }
    cout << ms.size() << "\n";
    return 0;
}