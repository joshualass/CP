#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//regular 
ll gcd ( ll a, ll b ) {
    while ( b ) {
        a = a % b;
        swap ( a, b );
    }
    return a;
}

//extended 
ll ext_gcd ( ll A, ll B, ll *X, ll *Y ){
    ll x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}

pair<ll, ll> chinese_remainder_theorem( vector<ll> A, vector<ll> M ) {
    if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
 
    ll n = A.size();
 
    ll a1 = A[0];
    ll m1 = M[0];
    /** Initially x = a_0 (mod m_0)*/
 
    /** Merge the solution with remaining equations */
    for ( ll i = 1; i < n; i++ ) {
        ll a2 = A[i];
        ll m2 = M[i];
 
        ll g = __gcd(m1, m2);
        if ( a1 % g != a2 % g ) return {-1,-1}; /** No solution exists*/
 
        /** Merge the two equations*/
        ll p, q;
        ext_gcd(m1/g, m2/g, &p, &q);
 
        ll mod = m1 / g * m2; /** LCM of m1 and m2*/
 
        /** We need to be careful about overflow, but I did not bother about overflow here to keep the code simple.*/
        ll x = (a1*(m2/g)*q + a2*(m1/g)*p) % mod;
 
        /** Merged equation*/
        a1 = x;
        if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return {a1, m1};
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<ll> volumes(0);
    vector<ll> V(3);
    vector<ll> v(3);
    ll a,b,c,d,e,f,g; cin >> a >> b >> v[0] >> v[1] >> v[2] >> f >> g;
    for(int i = 1; i * 2 < a; i++) {
        volumes.push_back(i * (a - i * 2) * (b - i * 2));
    }
    sort(volumes.begin(),volumes.end());
    for(int i = 0; i < 3; i++) {
        V[i] = volumes[volumes.size() - 1 - i];
    }
    // cout << chinese_remainder_theorem(v, V) << "\n";
    pair<ll,ll> ans = chinese_remainder_theorem(v,V);
    cout << ans.first + (f - ans.first + ans.second - 1) / ans.second * ans.second<< "\n";
    return 0;
}