#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

map<string, pair<string, pair<int,int>>> m;

string find(string s) {
    if(m[s].first == s) {
        return s;
    } else {
        m[s].first = find(m[s].first);
        return m[s].first;
    }
}

void unify(string a, string b) {
    a = find(a);
    b = find(b);
    if(a == b) { 
        return;
    }
    if(m[a].second.first == m[b].second.first) {
        m[a].second.second += m[b].second.second;
        m[b].first = a;
        m[a].second.first++;
    } else if(m[a].second.first < m[b].second.first) {
        m[b].second.second += m[a].second.second;
        m[a].first = b;
    } else {
        m[a].second.second += m[b].second.second;
        m[b].first = a;        
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string out = "";
    while(n-->0) {
        string first, second;
        cin >> first >> second;
        if(m.find(first) == m.end()) {
            m[first] = make_pair(first, make_pair(1,1));
        }
        if(m.find(second) == m.end()) {
            m[second] = make_pair(second, make_pair(1,1));
        }
        unify(first, second);
        cout << m[find(first)].second.second << "\n";
    }

    return 0;
}