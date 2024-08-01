#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
const ll maxsize = 60;

/*
First, observe that we can calculate each of the paths independently. For a given n, we find the number of paths of each length which is bounded by O(log(n)) because of the depth of a binary tree.
We can calculate the number of lengths for all the paths by looking at each node as well as its subtree size. There are logn unique subtree sizes. We calculate the number of paths by seeing how many
nodes in the left and right subtree have depth i. Once the lengths are calculated, we can compute how many times for each of the lengths, each of the maxes from 1 to m will occur in O(m) time. 
*/

//basic programming exercise made difficult. 

ll leftcnts[maxsize + 1];
ll rightcnts[maxsize + 1];

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

ll pc[100001][121];

void solve() {

    clock_t tStart = clock();
    
    ll N, M; cin >> N >> M;

    vector<ll> lengths(maxsize * 2 + 2);

    map<ll,ll> m;
    m[N] = 1;

    while(m.size()) {
        auto [n, mult] = (*m.rbegin());
        m.erase(n);
        ll remain = n - 1;
        ll levelsize = 1;
        ll leftsize = 0, rightsize = 0;

        memset(leftcnts, 0, sizeof(leftcnts));
        memset(rightcnts, 0, sizeof(rightcnts));

        leftcnts[0] = 1, rightcnts[0] = 1;
        for(int depth = 1; depth <= maxsize; depth++) {
            ll leftadd = min(remain, levelsize);
            leftcnts[depth] = (leftcnts[depth] + leftadd) % MOD;
            remain -= leftadd;
            leftsize += leftadd;

            ll rightadd = min(remain, levelsize);
            rightcnts[depth] += (rightcnts[depth] + rightadd) % MOD;
            remain -= rightadd;
            rightsize += rightadd;

            levelsize *= 2;
        }

        mult %= MOD;

        for(int ld = 0; ld <= maxsize; ld++) {
            for(int rd = 0; rd <= maxsize; rd++) {
                lengths[ld + rd + 1] = (lengths[ld + rd + 1] + leftcnts[ld] * rightcnts[rd] % MOD * mult) % MOD;
            }
        }

        if(leftsize) {
            m[leftsize] = (m[leftsize] + mult) % MOD;
        }
        if(rightsize) {
            m[rightsize] = (m[rightsize] + mult) % MOD;
        }

    }

    ll res = 0;
    ll maxlength = min(N, __lg(N) * 2 + 1);
    ll notonpathposs = binexp(M, N - maxlength);

    for(ll length = maxlength; length; length--) {
        if(lengths[length]) {
            for(ll i = 1; i <= M; i++) {
                ll next = pc[i][length];
                ll prev = pc[i-1][length];
                res = (res + (next - prev + MOD) * i % MOD * lengths[length] % MOD * notonpathposs % MOD) % MOD;
            }
        }
        notonpathposs = (notonpathposs * M) % MOD;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 100001; i++) {
        for(int j = 0; j < 121; j++) {
            pc[i][j] = binexp(i,j);
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

/*

1
502453101139881071 500

*/