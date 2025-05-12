#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

ll inf = 1e18;

struct pt {
    ll x, y;
    pt(ll _x, ll _y) {
        x = _x;
        y = _y;
    }
    pt() {x = 0, y = 0;}
};

ll dist(pt a, pt b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

pt add(pt a, pt b){
    return {a.x + b.x, a.y + b.y};
}

pt sub(pt a, pt b) {
    return {a.x - b.x, a.y - b.y};
}

pt mul(pt a, ll s) {
    return {a.x * s, a.y * s};
}

pt div(pt a, ll s) {
    return {a.x / s, a.y / s};
}

pt find_isect_helper(pt a, ll ra, pt b, ll rb) {
    assert(ra > 0 && rb > 0);
    //see if they're close enough
    if(ra + rb < dist(a, b)) return {inf, inf};
    //see if one contains the other
    if(dist(a, b) + rb < ra) return {inf, inf};
    if(dist(a, b) + ra < rb) return {inf, inf};
    //see if the parity matches
    if((ra + rb) % 2 != dist(a, b) % 2) return {inf, inf};
    //there must exist an intersection 
    //find two adjacent points inside and outside
    vector<pt> apts;
    apts.push_back({a.x + ra, a.y});
    apts.push_back({a.x, a.y + ra});
    apts.push_back({a.x - ra, a.y});
    apts.push_back({a.x, a.y - ra});
    pt pa = {inf, inf}, pb = {inf, inf};
    for(int i = 0; i < 4; i++){
        if(dist(apts[i], b) <= rb && dist(apts[(i + 1) % 4], b) >= rb) {
            pa = apts[i];
            pb = apts[(i + 1) % 4];
            break;
        }
    }
    //couldn't find anything. The other one will.
    if(pa.x == inf) return {inf, inf};
    //we know distance from outside point to b, and we know that if we travel along pb -> pa, we'll eventually get inside
    pt dir = sub(pa, pb);
    assert(abs(dir.x) == abs(dir.y));
    dir.y /= abs(dir.x);
    dir.x /= abs(dir.x);
    assert(abs(dir.x) == 1 && abs(dir.y) == 1);
    ll db = dist(pb, b);
    db -= rb;
    assert(db % 2 == 0);
    pt ans = pb;
    ans = add(ans, mul(dir, db / 2));
    assert(dist(ans, a) == ra && dist(ans, b) == rb);
    return ans;
}

pt find_isect(pt a, ll ra, pt b, ll rb) {
    if(ra == 0 && rb == 0) {
        return (a.x == b.x && a.y == b.y)? a : pt(inf, inf);
    }
    else if(ra == 0) {
        return (dist(a, b) == rb)? a : pt(inf, inf);
    }
    else if(rb == 0){
        return (dist(a, b) == ra)? b : pt(inf, inf);
    }
    pt ia = find_isect_helper(a, ra, b, rb);
    pt ib = find_isect_helper(b, rb, a, ra);
    if(ia.x != inf) return ia;
    return ib;
}

pt find_isect(pt a, ll ra_low, ll ra_high, pt b, ll rb) {
    assert(ra_low % 2 == ra_high % 2);
    //is b outside of a
    if(dist(a, b) > ra_high + rb) return {inf, inf};
    //is b contained by a
    if(dist(a, b) + rb < ra_low) return {inf, inf};
    //is a contained by b
    if(dist(a, b) + ra_high < rb) return {inf, inf};
    //do the parities match
    if((ra_low + rb) % 2 != dist(a, b) % 2) return {inf, inf};
    //they should intersect. Find the closest distance from a to b that matches parity and also inside of [ra_low, ra_high]. 
    //ra >= dist(a, b) - rb
    //dist(a, b) + ra >= rb, ra >= rb - dist(a, b)
    //dist(a, b) + rb >= ra, ra <= dist(a, b) + rb
    ll lb = max(dist(a, b) - rb, rb - dist(a, b));
    ll ub = dist(a, b) + rb;
    lb = max(lb, ra_low), ub = min(ub, ra_high);
    // cout << "LB UB : " << lb << " " << ub << "\n";
    assert(lb <= ub);
    return find_isect(a, lb, b, rb);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    pt end;
    cin >> end.x >> end.y;
    vl d(n);
    d[0] = 0;
    for(int i = 1; i < n; i++) cin >> d[i];
    vl rl(n + 1), rh(n + 1);
    rl[0] = 0, rh[0] = 0;
    for(int i = 1; i <= n; i++){
        rh[i] = rh[i - 1] + d[i - 1];
        rl[i] = abs(rl[i - 1] - d[i - 1]);
        rl[i] = min(rl[i], abs(rh[i - 1] - d[i - 1]));
        if(rl[i - 1] <= d[i - 1] && d[i - 1] <= rh[i - 1]) {
            if(d[i - 1] % 2 == rl[i - 1] % 2) rl[i] = min(rl[i], (ll) 0);
            else rl[i] = min(rl[i], (ll) 1);
        }
    }
    // cout << "RL RH : " << rl[n] << " " << rh[n] << endl;
    //determine if end is visitable
    if(find_isect({0, 0}, rl[n], rh[n], end, 0).x == inf) {
        //not visitable
        cout << "NO\n";
        return 0;
    }
    //always visitable
    cout << "YES\n";
    vector<pt> ans(0);
    ans.push_back(end);
    for(int i = n - 1; i > 0; i--){
        // cout << "FIND ISECT : " << rl[i] << " " << rh[i] << " " << end.x << " " << end.y << " " << d[i] << endl;
        pt isect = find_isect({0, 0}, rl[i], rh[i], end, d[i]);
        ans.push_back(isect);
        end = isect;
    }
    reverse(ans.begin(), ans.end());
    for(int i = 0; i < n - 1; i++) assert(dist(ans[i], ans[i + 1]) == d[i + 1]);
    for(int i = 0; i < n; i++) cout << ans[i].x << " " << ans[i].y << "\n";

    return 0;
}


// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// typedef vector<int> vi;
// typedef vector<ll> vl;
// typedef vector<vi> vvi;
// typedef vector<bool> vb;

// #define rep(i, a, b) for(int i = a; i < (b); i++)
// #define all(x) begin(x), end(x)
// #define sz(x) (int) (x).size()

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL), cout.tie(NULL);

//     int n; cin >> n;

//     ll a, b; cin >> a >> b;
//     vector<array<ll,3>> dists(n - 2);
    
//     array<ll,2> res = {};

//     for(int i = 0; i < n - 1; i++) {
//         ll x; cin >> x;
//         dists[i][0] = i;
//         dists[i][1] = x;
//         res[0] = x;
//     }

//     ll d; cin >> d;
    
//     //not enough distances to reach point (a, b)
//     if(res[0] < a + b - d) {
//         cout << "NO\n";
//         return 0;
//     }

//     //parity is no good
//     if(((res[0] + d) & 1) != ((a + b) & 1)) {
//         cout << "NO\n";
//         return 0;
//     }

//     ll sw = res[0] - (a + b - d);
//     ll nw = 

//     vector<array<ll,2>> dists(n - 1);


//     for(int i = 0; i < n - 1; i++) {
//         cin >> dists[i][0];
//         res[0] += dists[i][0];
//     }

//     //adjust up to x in the direction SW
//     auto go_sw = [&](ll x) -> void {
//         for(auto &d : dists) {
//             ll go = max(x, d[0]);

//             d[0] -= go;
//             d[1] -= go;

//             res[0] -= go;
//             res[1] -= go;

//             x -= go;
//         }
//     };

//     auto go_nw = [&]()



//     return 0;
// }