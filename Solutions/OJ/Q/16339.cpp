#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
The 2025 ICPC Asia East Continent Final Contest (EC-Final 2025)
L. Logical Resonance
*/

/*
pretty cool bijection that unfortunately takes more than 5 hours to come up with or something. 

The answer is to recursively string the nodes together from low to high. For each node, find the max element in each of it's children subtrees and then 
sort in increasing order. Then, add an edge between the node and the smallest max element child, as well as edges adjacent in the sorted children's list. 

How to arrive to this answer
I did a lot of thinking of some cases and tried to guess some patterns. I got decently far and made some observations, but ultimately while doing this,
I was able to see we needed some recursive structure that made sure the children in its subtree were already valid. i.e. within each subtree, the 
requirements were already satisfied - all leaves were a parent of some node and all the non-leaves are already leaves. To do this for 
each subtree, it makes sense to do the chain and we arbitrarily chose the keeping the largest in each group because it worked. 

High level of why it works ? - 

This idea works because ...

pros have a nice way of testing that this works. 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve_first() {
    int n; cin >> n;
    vector<vector<int>> ch(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        if(i) {
            ch[x].push_back(i);
        }
    }
    vector<int> res(n);
    auto dfs = [&](auto self, int i) -> int {
        int mx = i;
        vector<int> a;
        for(int c : ch[i]) {
            a.push_back(self(self, c));
        }
        sort(a.begin(), a.end());
        // cout << "i : " << i << endl;
        // cout << "a : " << a << endl;
        for(int j = 0; j < sz(a); j++) {
            if(j) {
                res[a[j-1]] = a[j] + 1;
            } else {
                res[i] = a[j] + 1;
            }
        }
        if(sz(a)) return a.back();
        return i;
    };
    dfs(dfs, 0);
    for(int i = 0; i < sz(res); i++) {
        cout << res[i] << " \n"[i == sz(res) - 1];
    }
}

void solve_second() {
    int n; cin >> n;
    vector<vector<int>> ch(n);
    for(int i = 0; i < n; i++) {
        int p; cin >> p;
        p--;
        if(i != n - 1) {
            ch[p].push_back(i);
        }
    }
    vector<int> res(n);
    auto dfs = [&](auto self, int i) -> int {
        int mx = i;
        vector<int> a;
        for(int c : ch[i]) {
            a.push_back(self(self, c));
        }
        sort(a.rbegin(), a.rend());
        for(int j = 0; j < sz(a); j++) {
            if(j) {
                res[a[j-1]] = a[j] + 1;
            } else {
                res[i] = a[j] + 1;
            }
        }
        if(sz(a)) return a.back();
        return i;
    };
    dfs(dfs, n - 1);
    for(int i = 0; i < sz(res); i++) {
        cout << res[i] << " \n"[i == sz(res) - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, casi; cin >> r >> casi;
    while(casi-->0) {
        if(r == 1) solve_first();
        if(r == 2) solve_second();
    }

    return 0;
}
