#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// void solve() {
//     ll n, a, b, x, y, z; cin >> n >> a >> b >> x >> y >> z;
//     vector<pair<ll,ll>> v = {{1,x}};

//     if((y + a - 1) / a <= x) { //should we consider using operation A
//         v.push_back({a,y});
//     }
//     if((z + b - 1) / b <= x) { //should we consider using operation B
//         v.push_back({b,z});
//     }
//     if(v.size() == 1) {
//         // cout << "case 1: ";
//         cout << n * x << "\n";
//     } else if(v.size() == 2) {
//         // cout << "case 2: ";
//         ll bigops = n / v[1].first;
//         cout << bigops * v[1].second + ((n - bigops * v[1].first) * x) << "\n";
//     } else { //consider all 3 operations
//         // cout << "case 3: ";
//         ll total_cost = 0;
//         // cout << "test: " << a * b << " " << gcd(a,b) << "\n";
//         if(a * b <= n && a <= 1e4 && b <= 1e4) { //I made this if statement trigger more often and got more wrong answers. something's not right...
//             pair<ll,ll> use = {-1,-1};
//             if(v[1].second * v[2].first <= v[2].second * v[1].first) {
//                 use = v[1];
//                 ll lcm = a * b / gcd(a,b);
//                 ll mult = lcm / a; mult /= 2;
//                 use.first *= mult;
//                 use.second *= mult;
//             } else {
//                 use = v[2];
//                 ll lcm = a * b / gcd(a,b);
//                 ll mult = lcm / b; mult /= 2;
//                 use.first *= mult;
//                 use.second *= mult;
//             }
//             if(use.first != 0) {
//                 ll ops = n / use.first;
//                 total_cost += ops * use.second;
//                 n -= ops * use.first;
//             }
//         } else {
//             if(v[2].first <= v[1].first) {
//                 swap(v[1],v[2]);
//             }
//         }

//         ll min_cost = LLONG_MAX;
//         for(int i = 0; i * v[1].first <= n; i++) {
//             //use i operations of A, then fill with B then with 1's
//             ll Aops = i;
//             ll cost = Aops * v[1].second;
//             ll remaining = n - Aops * v[1].first;
//             ll Bops = remaining / v[2].first;
//             cost += Bops * v[2].second;
//             remaining -= Bops * v[2].first;
//             cost += remaining* x;
//             min_cost = min(min_cost, cost);
//         }
//         // cout << total_cost << " " << min_cost << "\n";
//         cout << total_cost + min_cost << "\n";
//     }
// }


//copy daniel's clean sol'n. too clean it burns
void solve() {
    ll n, a, b, x, y, z; cin >> n >> a >> b >> x >> y >> z;

    ll best = n * x;
    for(int i = 0; i * a <= n && i <= 1e6; i++) {
        //use operations of a
        ll remainder = n - i * a;
        best = min(best, i * y + (remainder /  b)*z + (remainder % b)*x);
    } 
    for(int i = 0; i * b <= n && i <= 1e6; i++) {
        //use i operations of b
        ll remainder = n - i * b;
        best = min(best, i * z + (remainder / a) * y + (remainder % a) * x);
    }
    cout << best << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}