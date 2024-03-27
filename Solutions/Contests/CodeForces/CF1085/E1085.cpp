#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//we need a string that is between strings a and b. 
//try to template string s into the lexicographically smallest string that is >= a
//then check if this new string t is <= b.
//problem is just finding this lexicgraphically smallest string t

/*
s - 11111231
a - 11111232

s - 1231
a - 1232

1321

res - 11111321

want it to be low, but in sometimes, have to change earlier do dfs. 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

bool dfs(int i, string &s, string &a, vector<int> &used, vector<int> &iused, bool isover, int &k) {
    // cout << "i : " << i << " used : " << used << " iused : " << iused << " isover : " << isover << '\n';
    if(i == s.size()) return 1;
    if(used[s[i] - 'a'] != -1) {
        if(isover == 0 && used[s[i] - 'a'] < a[i] - 'a') return 0;
        if(isover == 0 && used[s[i] - 'a'] > a[i] - 'a') {
            return dfs(i+1,s,a,used,iused,1,k);
        } else {
            return dfs(i+1,s,a,used,iused,isover,k);
        }
    }
    if(isover) {
        for(int j = 0; j < k; j++) {
            if(iused[j] == -1) {
                used[s[i] - 'a'] = j;
                iused[j] = s[i] - 'a';
                dfs(i+1,s,a,used,iused,1,k);
                return 1;
            }
        }
    } else {
        for(int j = 0; j < k; j++) {
            if(iused[j] == -1 && j == a[i] - 'a') {
                used[s[i] - 'a'] = j;
                iused[j] = s[i] - 'a';
                if(dfs(i+1,s,a,used,iused,0,k)) {
                    return 1;
                }
                used[s[i] - 'a'] = -1;
                iused[j] = -1;
            }
            if(iused[j] == -1 && j > a[i] - 'a') {
                used[s[i] - 'a'] = j;
                iused[j] = s[i] - 'a';
                dfs(i+1,s,a,used,iused,1,k);
                return 1;
            }
        }
        return 0;
    }
    return 42069;
}

void solve(int x) {
    int k; cin >> k;
    string a, b, s; cin >> s >> a >> b;
    // if(x == 25) {
    //     cout << "s---" << s << "a---" << a << "b---" << b << "\n";
    // }
    bool is_over = 0;
    vector<int> used(k,-1); //used[i] shows what character i is mapped to
    vector<int> iused(k,-1); //iused[i] shows that the character i is mapped from

    bool v = dfs(0,s,a,used,iused,0,k);

    string res = "";
    for(int i = 0; i < a.size(); i++) {
        res.push_back(used[s[i] - 'a'] + 'a');
    }

    // cout << "v : " << v << '\n';
    // cout << "used : " << used << '\n';
    // cout << "iused : " << iused << '\n';
    // cout << "res : " << res << '\n';

    if(res <= b && v) {
        cout << "YES\n";

        for(int i = 0; i < k; i++) {
            if(used[i] == -1) {
                int j = 0;
                while(iused[j] != -1) j++;
                used[i] = j;
                iused[j] = i;
            }
        }
        // cout << "after used : " << used << '\n';
        for(int i = 0; i < k; i++) {
            cout << (char) (used[i] + 'a');
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    for(int i = 0; i < tc; i++) {
        solve(i);
    }

    return 0;
}