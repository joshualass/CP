#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
we see that if the brackets are alternating, we can't increase one of the sides. 
we make sure that the first (( is before the first )) and the latest )) is later than the lates ((.
Store all the indices in a set. 
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    string s; cin >> s;

    set<int> opens, closes;

    auto update = [&](int i) {

        if(s[i] == '(' && s[i+1] == '(') {
            opens.insert(i);
        } else {
            opens.erase(i);
        }

        if(s[i] == ')' && s[i+1] == ')') {
            closes.insert(i);
        } else {
            closes.erase(i);
        }

    };

    for(int i = 0; i < n - 1; i++) {
        update(i);
    }

    for(int i = 0; i < q; i++) {
        int j; cin >> j;
        j--;
        if(s[j] == ')') {
            s[j] = '(';
        } else {
            s[j] = ')';
        }
        if(j != n - 1) {
            update(j);
        }
        if(j != 0) {
            update(j-1);
        }

        if(s[0] == ')' || s[n - 1] == '(' || (s.size() & 1)) {
            cout << "No\n";
        } else if(opens.empty() && closes.empty()) {
            cout << "Yes\n";
        } else if(opens.size() && closes.size()) {

            int loopen = *opens.begin();
            int hiopen = *--opens.end();
            int loclose = *closes.begin();
            int hiclose = *--closes.end();

            if(loopen <= loclose && hiclose >= hiopen) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }

        } else {
            cout << "No\n";
        }

    }

    return 0;
}