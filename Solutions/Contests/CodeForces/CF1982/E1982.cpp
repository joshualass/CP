#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1000000007;

/*
nice problem where we analyze cycles that bits are on and off. 

indexing
depth - what bit we are on
k - from problem
overhead - how many bits of higher order are set for the entire range

storing
cnt - how many subarrays are possible within this segment
l - maximum size subarray including left endpoint where all elements <= k
r - same thing as left, but right side
all - if the entire range is <= k
*/

struct node {
    ll cnt, l, r;
    bool all;
    node() {
        cnt = 0, l = 0, r = 0, all = 0;
    }
};

node pc[64][64][64];

void solve() {
    ll n, k; cin >> n >> k;
    node curr;

    int overcnt = 0;

    for(ll depth = 60; depth >= 0; depth--) {
        if(n >= 1LL << depth) {
            node* next = &pc[depth][k][overcnt];
            curr.cnt = (curr.cnt + next->cnt + curr.r * next->l) % MOD;
            ll nextl = (curr.all ? curr.l + next->l : curr.l) % MOD;
            ll nextr = (next->all ? curr.r + next->r : next->r) % MOD;
            curr.l = nextl;
            curr.r = nextr;
            curr.all = curr.all && next->all;
            n -= 1LL << depth;
            overcnt++;
        }
    }

    cout << curr.cnt << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(ll depth = 0; depth < 63; depth++) {
        for(ll k = 0; k < 63; k++) {
            for(ll overhead = 0; overhead < 63; overhead++) {
                if(k >= overhead) {
                    if(depth == 0) {
                        pc[depth][k][overhead].cnt = 1;
                        pc[depth][k][overhead].l = 1;
                        pc[depth][k][overhead].r = 1;
                        pc[depth][k][overhead].all = 1;
                    } else {
                        //the left half to the segment has one less overhead
                        //we care about depth - 1, k should not change, overhead on left segment and overhead + 1 on the right segment
                        node* left = &pc[depth - 1][k][overhead];
                        node* right = &pc[depth - 1][k][overhead + 1];

                        pc[depth][k][overhead].cnt = (left->cnt + right->cnt + left->r * right->l) % MOD;
                        pc[depth][k][overhead].l = (left->all ? left->l + right->l : left->l) % MOD;
                        pc[depth][k][overhead].r = (right->all ? left->r + right->r : right->r) % MOD;
                        pc[depth][k][overhead].all = left->all && right->all;
                    }
                }
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}