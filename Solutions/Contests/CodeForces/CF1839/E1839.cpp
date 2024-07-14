#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//used editorial to solve this basic programming exercise

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int sum = accumulate(a.begin(), a.end(), 0);

    vector<int> dp(sum + 1, -1);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = sum; j >= a[i]; j--) {
            if(dp[j - a[i]] != -1 && dp[j] == -1) {
                dp[j] = i;
            }
        }
    }

    // cout << "dp :( " << dp << '\n';

    if(sum % 2 == 0 && dp[sum / 2] != -1) {
        cout << "Second" << endl;
        set<int> s1;
        int curr = sum / 2;
        while(curr) {
            s1.insert(dp[curr]);
            curr -= a[dp[curr]];
        }
        set<int> s2;
        for(int i = 0; i < n; i++) {
            if(s1.count(i) == 0) {
                s2.insert(i);
            }
        }

        // cout << "s1 : " << s1 << endl;
        // cout << "s2 : " << s2 << endl;
        
        while(s1.size()) {
            int input; cin >> input;
            input--;

            if(s1.count(input) == 0) {
                swap(s1,s2);
            }

            int me = (*s2.begin());
            cout << me + 1 << endl;
            int val = min(a[input], a[me]);
            a[input] -= val;
            a[me] -= val;
            if(a[input] == 0) {
                s1.erase(input);
            }
            if(a[me] == 0) {
                s2.erase(me);
            }

        }


    } else {
        cout << "First" << endl;
        set<int> s;
        for(int i = 0; i < n; i++) {
            s.insert(i);
        }
        while(1) {
            int me = *s.begin();
            cout << me + 1 << endl;
            int you; cin >> you;
            if(you == 0) break;
            you--;
            int val = min(a[me], a[you]);
            a[me] -= val;
            a[you] -= val;

            if(a[me] == 0) {
                s.erase(me);
            }
            if(a[you] == 0) {
                s.erase(you);
            }
        }

    }


    return 0;
}