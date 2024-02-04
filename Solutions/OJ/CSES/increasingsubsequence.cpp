#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 2e5;
int n;
int t[2 * N];

void build() {
    for(int i = n - 1; i > 0; i--) {
        t[i] = max(t[i*2],t[i * 2 + 1]);
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = max(t[p],t[p ^ 1]);
        p /= 2;
    }
}

int query(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    while(l < r) {
        if(l % 2 == 1) {
            ans = max(t[l],ans);
            l++;
        }
        if(r % 2 == 1) {
            r--;
            ans = max(ans,t[r]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < N * 2; i++) {
        t[i] = 0;
    }
    cin >> n;
    vector<pair<int,int>> v(0);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v.push_back({num,i});
    }
    sort(v.begin(),v.end(), [](const pair<int,int>&lhs, const pair<int,int>& rhs) {
        if(lhs.first == rhs.first) {
            return lhs.second > rhs.second;
        } else {
            return lhs.first < rhs.first;
        }
    });
    for(int i = 0; i < v.size(); i++) {
        // cout << "queryyy: " << query(0,v[i].second)+1 << "\n";
        modify(v[i].second,query(0,v[i].second)+1);
    }
    cout << query(0,n) << "\n";
    return 0;
}