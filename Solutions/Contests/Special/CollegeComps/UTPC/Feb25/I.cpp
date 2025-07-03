#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll MAXN = 1e5;
const ll SQN = 320;

deque<ll> deques[320];
array<ll,2> sums[320];

void printdq(int idx) {
    for(int i = 0; i < deques[idx].size(); i++) {
        cout << deques[idx][i] << " \n"[i == deques[idx].size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, q; cin >> n >> q;
    for(ll i = 0; i < n; i++) {
        ll x; cin >> x;
        sums[i / SQN][deques[i / SQN].size() & 1] += x;
        deques[i / SQN].push_back(x);
    }

    // printdq(0);

    auto get = [&](ll idx) -> ll {
        return deques[idx / SQN][idx % SQN];
    };

    auto update_block = [&](ll bidx, ll prev) -> ll {
        ll next = deques[bidx].front();
        deques[bidx].pop_front();
        sums[bidx][0] -= next;
        swap(sums[bidx][0], sums[bidx][1]);
        deques[bidx].push_back(prev);
        sums[bidx][1] += prev;
        return next;
    };

    auto update_block_all = [&](ll bidx, ll l, ll r, ll prev) -> ll {
        l %= SQN;
        r = (r - 1) % SQN + 1;
        // cout << "size : " << deques[bidx].size() << " l : " << l << " r : " << r << endl;
        ll next = deques[bidx][l];
        deque<ll> dq;

        sums[bidx] = {0,0};
        for(ll i = 0; i < l; i++) {
            sums[bidx][dq.size() & 1] += deques[bidx].front();
            dq.push_back(deques[bidx].front());
            deques[bidx].pop_front();
        }

        deques[bidx].pop_front();

        for(ll i = l + 1; i < r; i++) {
            sums[bidx][dq.size() & 1] += deques[bidx].front();
            dq.push_back(deques[bidx].front());
            deques[bidx].pop_front();
        }

        sums[bidx][dq.size() & 1] += prev;
        dq.push_back(prev);

        while(deques[bidx].size()) {
            sums[bidx][dq.size() & 1] += deques[bidx].front();
            dq.push_back(deques[bidx].front());
            deques[bidx].pop_front();
        }

        deques[bidx] = dq;
        return next;

    };

    for(ll i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        l--;
        ll prev = get(l);
        for(ll j = SQN - 1; j >= 0; j--) {
            ll bl_lo = j * SQN, bl_hi = (j + 1) * SQN;
            if(l <= bl_lo && r >= bl_hi) {
                prev = update_block(j, prev);
            } else {
                ll lo = max(l, bl_lo), hi = min(r, bl_hi);
                if(lo < hi) {
                    prev = update_block_all(j, lo, hi, prev);
                }
            }
        }

        ll fish = 0, man = 0;
        for(ll i = 0; i < SQN; i++) {
            fish += sums[i][0];
            man += sums[i][1];
        }

        // printdq(0);


        if(fish > man) {
            cout << "FISH\n";
        } else if(man > fish) {
            cout << "MAN\n";
        } else {
            cout << "TIE\n";
        }

    }

    return 0;
}