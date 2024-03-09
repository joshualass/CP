#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int move; cin >> n >> move;
    move++;
    set<int> in;
    for(int i = 0; i < n; i++) {
        t[i+n] = 1;
        in.insert(i);
    }
    build();

    int idx = n;
    for(int i = n; i >= 1; i--) {
        int left = (move - 1) % i + 1;
        int q = query(idx,n);
        int prev = -1;
        if(q < left) {
            left -= q;
            prev = idx;
            idx = 0;
        } else {
            prev = n;
        }
        // cout << "i: " << i << " idx: " << idx << " prev: " << prev << " left: " << left;
        int l = idx, r = prev;
        while(l < r) {
            int m = (l + r) / 2;
            q = query(idx,m);
            if(q > left) {
                r = m;
            } else if (q == left) {
                r = l = m;   
            }else {
                if(r - l == 1) l = r;
                else l = m;
            }
        }
        l--;
        // cout << " l: " << l;
        if(i == 1) l = 0;
        int remove = *--in.upper_bound(l);
        // cout << " remove: " << remove << " ";
        in.erase(remove);
        modify(remove,0);
        idx = remove;
        cout << idx + 1 << " ";
    }

    return 0;
}