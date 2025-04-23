#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
BPBPBBBBBPBBBBB
BPBPBBBPBBBBBBB
BPBPBPBBBBBBBBB
BBPPBPBBBBBBBBB
BBBPPPBBBBBBBBB

PBPBPBPB

BPPBPBPB

BBPPPBPB

BBPBPPPB

BBPBPBPP

BBPBBPPP

BBBBPPPP



*/

template <typename T>
void printS(stack<T> x) {
    cout << "stack: ";
    while(x.size()) {
        cout << x.top() << ' ';
        x.pop();
    }
    cout << "\n";
}

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    while(s.size() && s.back() == 'P') s.pop_back();
    reverse(s.begin(), s.end());
    while(s.size() && s.back() == 'B') s.pop_back();
    reverse(s.begin(), s.end());

    stack<char> st;
    ll inv = 0, pc = 0;
    for(int i = 0; i < s.size(); i++) {
        if(st.empty() || s[i] != st.top()) {
            st.push(s[i]);
        } else if(st.size()) st.pop();
        if(s[i] == 'P') {
            pc++;
        } else {
            inv += pc;
        }
    }

    // cout << "inv : " << inv << " st size : " << st.size() << '\n';

    // cout << "st ... : ";
    // printS(st);
    // cout << '\n';

    ll oio = (st.size() + 2) / 4;
    inv -= oio;

    cout << inv / 2 + oio << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}