#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void printChar(char c, bool toggle) {
    if(toggle) {
        if(c>= 'a') {
            cout << (char)(c - 'a' + 'A');
        } else {
            cout << (char)(c - 'A' + 'a');
        }
    } else {
        cout << c;
    }
}

void dfs(int l, int r, bool toggle, string &s, vector<int> &matches) {
    // cout << "l : " << l << " r : " << r << " toggle : " << toggle << '\n';
    if(l > r) return;
    if(!toggle) {
        if(s[l] == '(') {
            dfs(l+1,matches[l]-1,1,s,matches);
            dfs(matches[l]+1,r,0,s,matches);
        } else {
            printChar(s[l],toggle);
            dfs(l+1,r,toggle,s,matches);
        }
    } else {
        if(s[r] == ')') {
            dfs(matches[r]+1,r-1,0,s,matches);
            dfs(l,matches[r]-1,1,s,matches);
        } else {
            printChar(s[r],toggle);
            dfs(l,r-1,toggle,s,matches);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    stack<int> st;
    vector<int> matches(s.size(), -1);

    //first precompute all pairings of brackets 
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') {
            st.push(i);
        } 
        if(s[i] == ')') {
            matches[st.top()] = i;
            matches[i] = st.top();
            st.pop();
        }
    }

    dfs(0,s.size()-1,0,s,matches);
    cout << '\n';

    return 0;
}