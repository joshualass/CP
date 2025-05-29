#include <bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
typedef long double ld;

const ld pi = acos(-1);
const ld epsilon = 1e-9;

int calc_quad(pll a) {
    ll x = a.first, y = a.second;
    if(y == 0) {
        if(x > 0) return 0;
        else return 4;
    }
    if(x == 0){
        if(y > 0) return 2;
        else return 6;
    }
    if(x > 0 && y > 0) return 1;
    if(x < 0 && y > 0) return 3;
    if(x < 0 && y < 0) return 5;
    if(x > 0 && y < 0) return 7;
    assert(false);
    return -1;
}

pll rot_q1(pll& a){
    ll x = a.first, y = a.second;
    int q = calc_quad(a);
    assert(q >= 1 && q % 2 == 1);
    while(q != 1) {
        ll nx = y, ny = -x;
        x = nx, y = ny;
        q -= 2;
    }
    return {x, y};
}

struct lg {
    pll s, q1;
    int quad, ind;
    lg() {}
    lg(pll a, int _ind) {
        ind = _ind;
        quad = calc_quad(a);
        ll x = a.first, y = a.second;
        ll g = gcd(x, y);
        x /= g, y /= g;
        s = {x, y};
        if(quad % 2) q1 = rot_q1(s);
    }
};


const int N = 1e6 + 100;
bool v[N];
lg ev[N * 2];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int s = 0;
        for(int i = 0; i < n; i++) v[i] = false;
        for(int i = 0; i < n; i++){
            ll x, y;
            cin >> x >> y;
            if(calc_quad({x, y}) >= 4) s ++, v[i] = true;
            ev[i * 2 + 0] = lg({x, y}, (i + 1));
            ev[i * 2 + 1] = lg({-x, -y}, -(i + 1));
        } 
        // cout << "START S : " << s << "\n";
        sort(begin(ev), begin(ev) + (n * 2), [](const auto &a, const auto &b) -> bool {
            if(a.quad != b.quad) return a.quad < b.quad;
            if(a.quad % 2 == 0) return a.ind < b.ind;
            return a.q1.second * b.q1.first < b.q1.second * a.q1.first;
        });
        int ans = n;
        for(int i = 0; i < n * 2; i++){
            int cur = abs(ev[i].ind) - 1;
            if(ev[i].ind > 0) {
                if(!v[cur]) s ++;
                v[cur] = true;
            }
            else {
                if(v[cur]) s --;
                v[cur] = false;
            }
            ans = min(ans, s);
        }
        cout << ans << "\n";
    }

    return 0;
} 

// #include <bits/stdc++.h>
// using namespace std;
// typedef long long  ll;
// typedef vector<int> vi;
// typedef pair<int, int> pii;
// typedef vector<ll> vl;
// typedef long double ld;

// const ld pi = acos(-1);
// const ld epsilon = 1e-9;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL), cout.tie(NULL);

//     int t;
//     cin >> t;
//     while(t--){
//         int n;
//         cin >> n;
//         map<pair<ll, ll>, int> acnt;
//         for(int i = 0; i < n; i++){
//             ll x, y;
//             cin >> x >> y;
//             ll g = gcd(x, y);
//             x /= g, y /= g;
//             acnt[{x, y}] += 1;
//         }
//         vi f(acnt.size());
//         int fptr = 1;
//         vector<pair<ld, int>> ev;
//         for(auto i = acnt.begin(); i != acnt.end(); i++){
//             ld x = i->first.first, y = i->first.second;
//             cout << "XY : " << x << " " << y << "\n";
//             ld ang = atan2(y, x);
//             ev.push_back({ang, -fptr});
//             ev.push_back({ang + pi, fptr});
//             f[fptr - 1] = i->second;
//             fptr ++;
//         }
//         for(int i = 0; i < ev.size(); i++){
//             ld ang = ev[i].first;
//             while(ang > 2 * pi) ang -= 2 * pi;
//             while(ang < 0) ang += 2 * pi;
//             ev[i].first = ang;
//             // cout << ev[i].first << " " << ev[i].second << "\n";
//         }
//         sort(ev.begin(), ev.end());
//         int ans = n;
//         vector<bool> v(f.size(), false);
//         int s = 0;
//         for(int i = 0; i < ev.size(); i++){
//             int cur = abs(ev[i].second) - 1;
//             // cout << cur << endl;
//             // cout << "I : " << i << endl;
//             // cout << "EV : " << ev[i].first << " " << ev[i].second << "\n";
//             // cout << "VSZ : " << v.size() << " " << f.size() << endl;
//             if(ev[i].second < 0) {
//                 if(!v[cur]) s += f[cur];
//                 v[cur] = true;
//             }
//             else {
//                 if(v[cur]) s -= f[cur];
//                 v[cur] = false;
//             }
//         }
//         for(int i = 0; i < ev.size(); i++){
//             int cur = abs(ev[i].second) - 1;
//             // cout << cur << endl;
//             // cout << "I : " << i << endl;
//             // cout << "EV : " << ev[i].first << " " << ev[i].second << "\n";
//             if(ev[i].second < 0) {
//                 if(!v[cur]) s += f[cur];
//                 v[cur] = true;
//             }
//             else {
//                 if(v[cur]) s -= f[cur];
//                 v[cur] = false;
//             }
//             ans = min(ans, s);
//         }
//         cout << ans << "\n";
//     }

//     return 0;
// }