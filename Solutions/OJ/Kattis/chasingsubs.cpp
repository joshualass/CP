#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<int> getprevs(string s) {
    vector<int> idxs(26,-1);
    vector<int> prevs(s.size());
    for(int i = 0; i < s.size(); i++) {
        int v = s[i] - 'a';
        prevs[i] = idxs[v];
        idxs[v] = i;
    }
    return prevs;
}

vector<int> kmp(string s) {
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
vector<int> find_matches(string &n, string &m, vector<int> &a) {
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
    return matches;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string n, m; cin >> n >> m;

    vector<int> prevn = getprevs(n);
    vector<int> prevm = getprevs(m);

    cout << "pn : " << prevn << '\n';
    cout << "pm : " << prevm << '\n';

    return 0;
}