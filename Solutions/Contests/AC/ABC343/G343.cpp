#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll M1 = 998244353, B1 = 9973;
const ll M2 = 1e9 + 9, B2 = 9931;
struct stringhash {
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    int n;

    stringhash(string s) {
        this->n = s.size();
        p1.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p1.push_back(p1.back() * B1 % M1);
        }
        p2.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p2.push_back(p2.back() * B2 % M2);
        }
        h1.push_back(0);
        for(int i = 0; i < n; i++) {
            h1.push_back((h1[i] * B1 + s[i]) % M1);
        }
        h2.push_back(0);
        for(int i = 0; i < n; i++) {
            h2.push_back((h2[i] * B2 + s[i]) % M2);
        }
    }

    ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
        ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
        return num1 + num2 * M1;
    }

};

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

const int MAXN = 20;
int dp[1 << MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<string> v(n);
    vector<stringhash> sh;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        v[i] = s;
        sh.push_back(stringhash(s));
    }

    for(int i = 0; i < v.size(); i++) {
        bool found = 0;
        ll ihash = sh[i].get_hash(0,v[i].size());
        for(int j = 0; j < v.size(); j++) {
            if(i != j) {
                if(v[i].size() <= v[j].size()) {
                    for(int k = 0; k + v[i].size() <= v[j].size(); k++) {
                        if(sh[j].get_hash(k,k+v[i].size()) == ihash) {
                            found = 1;
                        }
                    }
                }
            }
        }
        if(found) {
            v.erase(v.begin() + i);
            sh.erase(sh.begin() + i);
            i--;
        }
    }

    // cout << "v : " << v << '\n';
    n = v.size();
    vector<vector<int>> mat(n,vector<int>(n,-1));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                mat[i][j] = v[j].size();
                for(int k = 0; k < v[i].size(); k++) {
                    int d = min(v[i].size() - k, v[j].size());
                    if(sh[i].get_hash(k,k+d) == sh[j].get_hash(0,d)) {
                        mat[i][j] = v[j].size() - v[i].size() + k;
                        break;
                    }
                }
            }
        }
    }

    // cout << "mat\n" << mat;

    for(int i = 0; i < 1 << MAXN; i++) {
        for(int j = 0; j < MAXN; j++) {
            dp[i][j] = 1e9;
        }
    }

    for(int i = 0; i < n; i++) {
        dp[1 << i][i] = v[i].size();
    }

    for(int i = 0; i < 1 << n; i++) {
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) {
                int p = i ^ (1 << j);
                for(int k = 0; k < n; k++) {
                    dp[i][j] = min(dp[i][j], dp[p][k] + mat[k][j]);
                }
            }
        }
    }

    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        ans = min(ans,dp[(1 << n) - 1][i]);
    }
    cout << ans << '\n';

    return 0;
}