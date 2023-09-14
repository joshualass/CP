#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll N = 2e5 + 1;
ll n;
ll t[2 * N][6];
ll values[6];

void sum(ll sum[], ll f[], ll s[]) {
    for (int i = 0; i < 6; i++) {
        sum[i] = f[i] + s[i];
    }
}

void build() {
    for (ll i = i + n - 1; i > 0; i--) {
        sum(t[i], t[i * 2], t[i * 2 + 1]);
    }
}

void modify(ll p, ll index) {
    p += n;
    for (int i = 0; i < 6; i++) {
        t[p][i] = i == index;
    }

    while (p > 1) {
        sum(t[p / 2], t[p], t[p ^ 1]);
        p /= 2;
    }
}

ll query(ll l, ll r) {
    ll gems[6] = {0};
    l += n;
    r += n;

    while (l < r) {
        if (l % 2 == 1) {
            for(int i = 0; i < 6; i++) {
                gems[i] += t[l][i];
            }
            l++;
        }
        if (r % 2 == 1) {
            r--;
            for(int i = 0; i < 6; i++) {
                gems[i] += t[r][i];
            }
        }
        l /= 2;
        r /= 2;
    }
    ll ans = 0;
    for (int i = 0; i < 6; i++) {
        ans += gems[i] * values[i];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> n >> q;
    for (int i = 0; i < 6; i++) {
        cin >> values[i];
    }
    string line;
    cin >> line;

    for (int c = 0; c < line.length(); c++) {
        t[n + c][line[c] - 49]++;
    }
    build();

    while (q-- > 0) {
        int action;
        cin >> action;
        switch (action) {
            case 1:
                int k, p;
                cin >> k >> p;
                modify(k - 1, p - 1);
                break;

            case 2:
                int b, v;
                cin >> b >> v;
                values[b - 1] = v;
                break;

            case 3:
                int l, r;
                cin >> l >> r;
                cout << query(l - 1, r) << '\n';
                break;
        }
    }

    return 0;
}