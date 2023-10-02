//https://www.spoj.com/problems/INVCNT/
//inversion count problem

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
first solution using seg tree
const int N = 2e5;
int n;
int t[2 * N];

void build() {
    for (int i = n - 1; i > 0; --i) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = t[p] + t[p ^ 1];
        p /= 2;
    }
}

int query(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    while(l < r) {
        if (l % 2 == 1) {
            ans += t[l];
            l++;
        }
        if (r % 2 == 1) {
            r--;
            ans += t[r];
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

void solve() {
    cin >> n;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        t[i+n] = 0;
        v[i] = {num,i};
    }
    build();
    sort(v.begin(),v.end());

    ll ops = 0;
    for(int i = 0; i < n; i++) {
        pair<int,int> p = v[i]; //value, index
        int index = p.second;
        index += query(index,n);
        //to index - i, from index - p.second
        if(i < index) {
            ops += index - i;
            modify(p.second,1);
        }
    }
    cout << ops << "\n";
}*/

#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

void solve() {
    int n; cin >> n;
    ordered_set os;
    ll ops = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        ops += i - os.order_of_key(num);
        os.insert(num);
    }
    cout << ops << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}