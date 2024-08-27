#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
it's not too tricky to observe that binary search is helpful to solve this problem.
The question is how to binary search correctly?

We need to solve this question: given a fixed xor value k, for each right endpoint of a subarray, what is the highest index j such that j < i and minimum of subarray is less than k?
We use a Trie to solve this. 
We insert elements into the Trie, and then kind of query all the values that will xor less than k and take the maximum index from them. Takes n loga per search, and binary search runs loga times. 

Quite a lot of mistakes when implementing this both times.
Main issues: integer overflow, forgetting small things in implementation. 

Things missed so far
not assigning nextchild
forgetting res * dp for other problem. 

too many WA --> lower ego. 

*/

//BinaryTrie but implemented in a caseworky manner. TODO is exchange l / r with some array of sizing [N][2]. 

int depth = 31;
int nextchild = 3200000;

int l[3200000];
int r[3200000];
int m[3200000];

void reset() {
    for(int i = 0; i < nextchild; i++) {
        l[i] = -1;
        r[i] = -1;
        m[i] = -1;
    }
    nextchild = 1;
}

void insert(int i, int x) {
    int cur = 0;
    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;
        if(!bit) {           
            if(l[cur] == -1) {
                l[cur] = nextchild++;
            }
            cur = l[cur];
        } else {
            if(r[cur] == -1) {
                r[cur] = nextchild++;
            }
            cur = r[cur];
        }
        m[cur] = i;
    }
}

int query(int x, int k) {

    int res = -1;
    int cur = 0;

    for(int d = depth - 1; d >= 0; d--) {
        int bit = (x >> d) & 1;
        if((k >> d) & 1) { //if bit is set for k, we have the option to check the offbit. Must not go in direction of bit
            if(!bit && l[cur] != -1) {
                res = max(res, m[l[cur]]);
            } 
            if(bit && r[cur] != -1) {
                res = max(res, m[r[cur]]);
            }
        }
        //in either case, go in the direction of x ^ k. 
        if(bit == ((k >> d) & 1)) {
            if(l[cur] != -1) {
                cur = l[cur];
            } else {
                return res;
            }
        } else {
            if(r[cur] != -1) {
                cur = r[cur];
            } else {
                return res;
            }
        }
    }
    return res;
}

void solve() {

    ll n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int lo = 0, hi = 1073741823;

    while(lo != hi) {

        int m = (lo + hi + 1) / 2;
        
        reset();
        ll countunder = 0;
        int currhi = -1;

        for(int i = 0; i < n; i++) {

            currhi = max(currhi, query(a[i], m));
            countunder += currhi + 1;
            insert(i,a[i]);
        }

        if(countunder < k) {
            lo = m;
        } else {
            hi = m - 1;
        }

    }

    cout << lo << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}