#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1e6 + 1;
int n;
int t[2 * N];

void build() {
    for(int i = n - 1; i > 0; i--) {
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
        if(l % 2 == 1) {
            ans += t[l];
            l++;
        }
        if(r % 2 == 1) {
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
    
    int q;
    cin >> n >> q;
    string out = "";
    while(q-- > 0) {
        char action;
        cin >> action;
        if(action == 'F') {
            int p;
            cin >> p;
            modify(p, t[p + n] ^ 1);
        } else {
            int l, r;
            cin >> l >> r;
            out += to_string(query(l,r + 1)) + '\n';
        }
    }
    cout << out;

    return 0;
}