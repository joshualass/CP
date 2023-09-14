#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool sortbyfirst(const pair<int,int> &a, const pair<int,int> &b) {
    return (a.first < b.first);
}

int main() {
    freopen("blist.in","r",stdin);
    freopen("blist.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    vector<pair<int,int>> v{};
    
    while(N-->0) {

        int s, t, b;
        cin >> s >> t >> b;
        v.push_back(make_pair(s,b));
        v.push_back(make_pair(t,-b));
    }
    sort(v.begin(),v.end());
    ll big {};
    ll amt {};
    for(int i = 0; i < v.size(); i++) {
        amt += v[i].second;
        big = max(big,amt);
    }
    cout << big << "\n";
    return 0;
}