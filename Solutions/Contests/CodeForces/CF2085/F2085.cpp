#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
there is an idea that leads to a clean idea, but that is too hard to discern. 

At first, I was thinking of some sort of walk where we iterate over the elements and we slowly walk them over. 
I couldn't come up with a good algorithm to do this. 

Instead, we should think about the median in the array. that all the elements try to approach. 
We need to choose k / 2 elements to the left of this median and k / 2 elements to the right of this median. 
to solve this naively, we can initially set all elements to be to the right and then sor tthe differences that we obtain 
from moving each element to the left as compared to keeping it at the right. We choose the minimum k / 2 differences. 
need to sort things to get this to work/find and sum the smallest k / 2 elements. 

This solves the easy version of the problem. To solve the hard version, we can observe that not much changes as we shift the 
median over. we can keep a running sum of the smallest k/2 elements with the ds struct. OOP overkill, but this works. 

*/

const ll inf = 1e12;

struct ds {
    int n, k; 
    array<set<array<ll,2>>, 2> a;
    vector<ll> b, c;
    ll s;

    ds(int n, int k) {
        this->n = n;
        this->k = k;
        this->s = 0;
        b.resize(n);
        c.resize(n);

        for(int i = 0; i < k; i++) {
            a[0].insert({inf, i});
            b[i] = 0;
            c[i] = inf;
            s += inf;
        }

        for(int i = k; i < n; i++) {
            a[1].insert({inf, i});
            b[i] = 1;
            c[i] = inf;
        }

    }

    void add(int i, ll v, int p) {
        a[p].insert({v, i});
        if(p == 0) s += v;
    }

    void rem(int i, ll v, int p) {
        assert(a[p].count({v, i}));
        a[p].erase({v, i});
        if(p == 0) s -= v;
    }

    void upd(int i, ll v) {
        assert(i >= 0 && i < n);
        rem(i, c[i], b[i]);
        c[i] = v;
        add(i, c[i], b[i]);
        if((*--a[0].end())[0] > (*a[1].begin())[0]) {
            assert(a[0].size() && a[1].size());
            int l = (*--a[0].end())[1];
            int r = (*a[1].begin())[1];
            rem(l, c[l], b[l]);
            b[l] = 1;
            add(l, c[l], b[l]);

            rem(r, c[r], b[r]);
            b[r] = 0;
            add(r, c[r], b[r]);
        }
    }

};

void solve() {

    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<set<int>> b(k);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        b[x].insert(i);
    }

    ll sum_r = 0;
    ds d(k, k / 2);

    for(int i = 0; i < k; i++) {
        ll l = inf;
        assert(b[i].size());
        ll r = *b[i].begin();
        d.upd(i, l - r);
        sum_r += r;
    }

    ll res = inf;

    for(int i = 1; i < n; i++) {
        int p = a[i-1]; //prev value
        ll l = i - 1; //index to the left
        ll r = (b[p].lower_bound(i) == b[p].end() ? inf : *b[p].lower_bound(i)); //index to the right

        // cout << "i : " << i << " l : " << l << " r : " << r << '\n';

        //all k rights become closer, except the one we skip, which is already at 0
        sum_r -= k - 1;
        //add the next r. 
        sum_r += r - i;

        //update the pq value
        ll r_cost = r - i;
        ll l_cost = 0;
        d.upd(p, l_cost - r_cost - i * 2);

        ll cost = sum_r + d.s + 1LL * k / 2 * i * 2;

        // cout << "i : " << i << " sum_r : " << sum_r << " d.s : " << d.s << " cost : " << cost << '\n';

        res = min(res, cost);

    }

    auto tri = [&](ll t) -> ll {
        return t * (t - 1) / 2;
    };

    cout << res - tri((k + 1) / 2) - tri(k / 2) << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}