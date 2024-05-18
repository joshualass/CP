#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int v[400000];
int casi; 
//need to build sieve, typically with N
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
    std::fill (prime_factor, prime_factor + n, -1);
    for (int i = 2; i < n; ++i) {
        if (prime_factor[i] == -1) {
            prime.push_back(i);
            prime_factor[i] = i;
        }
        for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
            prime_factor[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}

void find_divs(map<int,int>::iterator i, int p, map<int,int> &pdivs, unordered_map<int,vector<int>> &divs, int &num, set<pair<int,int>> &nup, set<int> &nu, unordered_map<int,pair<int,int>> &used) {
    // cout << "inf p : " << p << " cnt : " << cnt << endl;
    if(i == pdivs.end()) {
        if(used.count(p) == 0) {
            for(int i = 0; i < divs[p].size(); i++) {
                if(nup.count({num,divs[p][i]}) == 0 && nu.count(num) == 0 && nu.count(divs[p][i]) == 0) {
                    used[p] = {divs[p][i], num};
                    break;
                }
            }
            divs[p].push_back(num);
        }
        return;
    }
    for(int j = 0; j <= (*i).second; j++) {
        find_divs(++i,p,pdivs,divs, num, nup, nu, used);
        p *= (*--i).first;
    }
}

pair<int,pair<int,int>> tb(vector<int> &a, int i, int n) {
    // cout << "a : " << a << "\ni : " << i << '\n';
    int md = 0;
    pair<int,int> p = {-1,-1};
    v[i] = INT_MAX;

    for(int j = i - 1; j >= 0; j--) {
        v[j] = v[j+1] & a[j];
    }
    int nd = INT_MAX;
    for(int j = i + 1; j < n; j++) {
        nd &= a[j];
    }
    int bnd = INT_MAX;
    for(int j = 0; j < i; j++) {
        int x = gcd(a[i], a[j]) - (bnd & nd & v[j+1]);
        // cout << "ff : " << j << " " << x << '\n';
        if(x > md) {
            md = x;
            p = {i,j};
        }
        bnd &= a[j];
    }
    return {md,p};
}

void solve(int zzzzzzzzz) {
    
    int n, x; cin >> n >> x;
    vector<int> a(n);
    

    unordered_map<int,vector<int>> divs;

    vector<vector<int>> bits(31);
    int nd = INT_MAX;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i] = num;
        for(int bit = 0; bit < 31; bit++) {
            if((num & (1 << bit)) == 0 && bits[bit].size() < 3) {
                bits[bit].push_back(i);
            }
        }
        nd &= num;
    }

    vector<int> rev = a;
    reverse(rev.begin(), rev.end());

    // if(zzzzzzzzz == 4522 && casi == 20000) {
    //     cout << "n-" << n << "-x-" << x << "_v:";
    //     for(int x : a) cout << x << '_';
    //     return;
    // }

    int md = 0;
    pair<int,int> p = {-1,-1};
    set<pair<int,int>> nup;
    set<int> nu;
    for(int b = 0; b < 31; b++) {
        // cout << "b : " << b << " size : " << bits[b].size() << '\n';
        if(bits[b].size() == 1) {
            int i = bits[b][0];
            // cout << "try i : " << i << ' ';
            // cout << "ex num : " << a[i] << ' ';
            pair<int, pair<int,int>> pp = tb(a,i,n);
            if(pp.first > md) {
                md = pp.first;
                p = pp.second;
            }
            // cout << "bi : " << i << " val : " << a[i] << '\n';
            // cout << pp.first << ' ';
            pp = tb(rev, n- i - 1, n);
            // cout << pp.first << '\n';
            if(pp.first > md) {
                md = pp.first;
                p = {n - 1 - pp.second.first, n - 1 - pp.second.second};
            }
            nu.insert(i);

        } else if(bits[b].size() == 2) {
            // cout << "try i j : " << bits[b].front() << " " << bits[b].back() << " ";
            int tnd = INT_MAX;
            int g = gcd(a[bits[b].front()], a[bits[b].back()]);
            for(int i = 0; i < n; i++) {
                if(i != bits[b].front() && i != bits[b].back()) {
                    tnd &= a[i];
                }
            }
            if(g - tnd > md) {
                md = g - tnd;
                p = {bits[b][0], bits[b][1]};
            }
            nup.insert({bits[b][0], bits[b][1]});
            nup.insert({bits[b][1], bits[b][0]});
        }
    }

    // cout << "nup\n";
    // for(auto p : nup) {
    //     cout << p.first << " " << p.second << '\n';
    // }
    // cout << "nu\n";
    // for(int x : nu) {
    //     cout << x << '\n';
    // }

    unordered_map<int,pair<int,int>> used(n);
    for(int i = 0; i < n; i++) {
        map<int,int> pdivs;
        int t = a[i];
        // cout << "mgcd t : " << t << " ";
        while(t != 1) {
            pdivs[prime_factor[t]]++;
            t /= prime_factor[t];
        }
        // cout << "pdivs\n" << pdivs;
        find_divs(pdivs.begin(), 1, pdivs, divs, i, nup, nu, used);
    }
    // cout << "nd : " << nd << '\n';
    for(auto [u, v] : used) {
        if(u - nd > md) {
            md = u - nd;
            p = v;
            // cout << "better md : " << md << " u : " << u << " idxs : " << v.first << " " << v.second << '\n';
        }
    }

    // cout << "md : " << md << '\n';
    if(md > x) {
        cout << "YES\n";
        cout << "2 " << a[p.first] << " " << a[p.second] << '\n';
        cout << n - 2 << " ";
        for(int i = 0; i < n; i++) {
            if(i != p.first && i != p.second) {
                cout << a[i] << " ";
            }
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("h.in","r",stdin);
    // freopen("h.out","w",stdout);

    sieve();
    cin >> casi;
    for(int i = 0; i < casi; i++) {
        solve(i);
    }

    return 0;
}