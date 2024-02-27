#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int depth = 30;

struct TrieNode {
    int value;
    TrieNode *arr[2];

    TrieNode() {
        this->value = 0;
        this->arr[0] = nullptr;
        this->arr[1] = nullptr;
    }
};

void insertNode(int num, TrieNode* root) {
    TrieNode* curr = root;
    curr->value++;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1;
        if(curr->arr[idx]) {
            curr = curr->arr[idx];
        } else {
            curr->arr[idx] = new TrieNode();
            curr = curr->arr[idx];
        }
        curr->value++;
    }
}

ll query(int num, TrieNode* root) { //queries the maximum xor value 
    TrieNode* curr = root;
    ll ans = 0;
    for(int i = 0; i < depth; i++) {
        int idx = (num >> (depth - i - 1)) & 1; //get the depth - ith bit of num
        if(idx) {
            ans += curr->value;
            if(curr->arr[0] != nullptr) {
                ans += curr->arr[0]->value;
            }
        } else {
            if(curr->arr[1] != nullptr) {
                ans += curr->arr[1]->value;
            }
        }
        curr = curr->arr[idx];
        // if(idx) {
        //     ans += curr->value;
        // }
    }
    ans += curr->value;
    return ans;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
  // Function to compute a/b under modulo m
ll modDivide(ll a, ll b) {
    a = a % MOD;
    int inv = modInverse(b, MOD);
    return (inv * a) % MOD;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

void solve() {
    ll n; cin >> n;
    vector<int> v(n);
    TrieNode* root = new TrieNode();
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        insertNode(num,root);
        v[i] = num;
    }
    ll total = 0;
    for(int i = 0; i < n; i++) {
        total += query(v[i], root);
        total %= MOD;
    }

    ll inv = modInverse(n * n % MOD,MOD);

    cout << total * inv % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}