#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Tree {
    typedef ll T; //update the data type, currently int
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    Tree tree(n);
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        tree.update(i,num);
    }
    for(int i = 0; i < q; i++) {
        int a, b, c; cin >> a >> b >> c;
        if(a & 1) {
            tree.update(--b,c);
        } else {
            cout << tree.query(--b,c) << "\n";
        }
    }

    return 0;
}

/*
//older template
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5;
int n;
ll t[N * 2];

void build() {
    for(int i = n - 1; i > 0; i--) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

void modify(int p, ll value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = t[p] + t[p ^ 1];
        p /= 2;
    }
}

ll query(int l, int r) {
    ll ans = 0; 
    l += n;
    r += n;
    while(l < r) {
        if (l % 2 == 1) {
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
    int q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> t[i + n];
    }
    build();
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll k, u; cin >> k >> u;
            modify(--k,u);
        } else {
            int a, b; cin >> a >> b;
            cout << query(--a,b) << '\n';
        }


    }

    return 0;
} */