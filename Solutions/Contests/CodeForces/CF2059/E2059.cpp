#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
This problem took a little bit to implement/plan how to implement/approach this.  
The idea is not too tricky to see. We first need to make the top array match, then make the following arrays match.
In general, we should keep track of the total number of operations done in previous row, which allows us to insert characters at any indices in the next row up to the number of operations done on previous rows.
Then, we greedily match the characters in a to a subsequence of characters in b and do kmp on the last part of b if we are not able to insert characters there. 
*/

vector<int> kmp(vector<int> s) {
    int n = s.size();
    vector<int> b(n+1,-1);
    int i = 0, j = -1;
    while(i != n) {
        while(j != -1 && s[i] != s[j]) {
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }
    return b;
}

//finds all occurences of m in n with kmp array of m. 
//modified to return the length of the longest match of suffix of n from prefix of m. 
int find_matches(vector<int> &n, vector<int> &m, vector<int> &a) {
    vector<int> matches;
    int i = 0;
    int j = 0;
    while(i < n.size()) {
        while(j == m.size() || (j != -1 && n[i] != m[j])) {
            j = a[j];
        }
        i++;
        j++;
        if(j == m.size()) {
            matches.push_back(i - m.size() + 1);
        }
    }
    return j;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n*m);
    for(int &x : a) cin >> x;
    vector<int> b(n*m);
    for(int &x : b) cin >> x;

    vector<array<int,2>> o;
    for(int i = 0; i < n; i++) {
        int s = i * m - o.size(); //starting index of a array
        int t = 0; //index of amt matched from a
        int j = 0; //index of match from b
        vector<array<int,2>> nx;
        for(; j < m && o.size(); j++) {
            if(a[s+t] == b[i*m+j]) { 
                nx.push_back(o.back());
                o.pop_back();
                t++;
            } else {
                nx.push_back({i,b[i*m+j]});
            }
        }

        int left = m - j;
        vector<int> c(a.begin() + s + t, a.begin() + s + t + left);
        vector<int> d(b.begin() + i * m + j, b.begin() + i * m + j + left);
        vector<int> ck = kmp(c);
        int len = find_matches(d,c,ck);
        
        for(; j + len < m; j++) {
            nx.push_back({i,b[i*m+j]});
        }
        reverse(nx.begin(), nx.end());
        o.insert(o.end(), nx.begin(), nx.end());
    }
    cout << o.size() << '\n';
    for(auto [r, x] : o) {
        cout << r + 1 << " " << x << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}