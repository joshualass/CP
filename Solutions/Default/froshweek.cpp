#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1e6;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    vector<int> original(n);
    vector<int> sorted(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        original[i] = num;
        sorted[i] = num;
    }
    sort(sorted.begin(),sorted.end());
    map<int,int> m;
    map<int,int> o;
    for(int i = 0; i < n; i++) {
        o.insert({original[i],i});
    }
    build();

    ll swaps = 0;
    for(int i = 0; i < n; i++) {
        int num = sorted[i];
        int startindex = o[num];
        int startposition = startindex + query(startindex,n);
        swaps += startposition - i;
        modify(startindex,1);
    }
    cout << swaps;

    return 0;
}