#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//could solve this with string hashing, but try KMP

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n, m; cin >> n >> m;
    
    vector<int> a = kmp(m);
    vector<int> matches = find_matches(n,m,a);
    // cout << "matches : " << matches << '\n';
    cout << matches.size() << '\n';
    return 0;
}
