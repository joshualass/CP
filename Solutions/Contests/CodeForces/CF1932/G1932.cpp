#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
need to focus on fixing wrong answers.
fermat's little theorem of modular inverses only works for prime mod. 
*/

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
    ll inv = modInverse(b, MOD);
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

//supposed to solve Ax + b === Cx + d % mod
ll find_step(ll A, ll B, ll C, ll D, ll mod) {
//get equation in the form of Ex === F % mod
    A %= mod, B %= mod, C %= mod, D %= mod;
    ll E = (A-C+mod) % mod;
    ll F = (D-B+mod) % mod;
    ll g = gcd(E,gcd(F,mod));
    E /= g, F /= g, mod /= g;

    if(gcd(E,mod) != 1) { //inverse doesn't exist and we did gcd so no solution
        return -1;
    }    
    if(mod == 1 || F == 0) return 0;
    // ll inv = binexp(E,mod-2,mod);
    ll inv = modInverse(E,mod);
    // cout << "e : " << E << " f : " << F << " mod : " << mod << " inv : " << inv << '\n';
    return F * inv % mod;
}

void solve() {
    ll n, m, h; cin >> n >> m >> h;
    vector<ll> l(n);
    vector<ll> s(n);
    for(ll &x : l) cin >> x;
    for(ll &x : s) cin >> x;

    vector<vector<ll>> adj(n);
    for(ll i = 0; i < m; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> visited(n,-1);
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    pq.push({0,0});

    while(pq.size()) {
        pair<ll,ll> p = pq.top();
        pq.pop();
        if(visited[p.second] != -1) continue;
        // cout << "i : " << p.second << " steps : " << p.first << '\n';
        visited[p.second] = p.first;
        for(ll i : adj[p.second]) {
            ll start_step = p.first % h;
            ll start_from = l[p.second] + start_step * s[p.second];
            ll start_to = l[i] + start_step * s[i];
            ll steps = find_step(s[p.second], start_from, s[i], start_to, h);
            // cout << s[p.second] << "x + " << start_from << " === " << s[i] << "x + " << start_to << " % " << h << " | x = " << steps << '\n';
            // cout << "a : " << s[p.second] << " b : " << start_from << " c : " << s[i] << " d : " << start_to << " mod : " << h << " ans : " << steps << '\n';
            if(steps != -1) {
                pq.push({p.first + steps + 1,i});
            }
        }
    }

    cout << visited[n-1] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}