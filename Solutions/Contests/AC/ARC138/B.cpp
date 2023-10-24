#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//simulate by starting from beginning

void erasebackzeroes(vector<int> &v, bool flip) {
    while(v.size() && (v.back() ^ flip) == 0) v.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    bool toggleflip = false;
    erasebackzeroes(v,toggleflip);

    for(int i = 0; i < v.size(); i++) {
        int val = v[i] ^ toggleflip;
        if(val == 1 || (i != v.size() - 1 && (v[i+1] ^ toggleflip) == 0)) {
            cout << "No\n";
            return 0;
        }
        toggleflip ^= 1;
        erasebackzeroes(v,toggleflip);
    }

    cout << "Yes\n";

    return 0;
}