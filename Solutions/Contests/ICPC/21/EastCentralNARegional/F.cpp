#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const ld PI = acos(-1);
struct vec2 {
    ld x, y;
    vec2() {}
    vec2(ld _x, ld _y) {
        x = _x, y = _y;
    }
};

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

ld dist_sq(vec2 a, vec2 b) {
    ld dx = a.x - b.x;
    ld dy = a.y - b.y;
    return dx * dx + dy * dy;
}

ld dist(vec2 a, vec2 b) {
    return sqrt(dist_sq(a, b));
}

vec2 mul(vec2 a, ld s) {
    return {a.x * s, a.y * s};
}

ld cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ld tri_area(vec2 t1, vec2 t2, vec2 t3) {
    vec2 d1 = sub(t2, t1);
    vec2 d2 = sub(t3, t1);
    return cross(d1, d2) / 2.0;
}

ld find_intt(ld dist, ld r0, ld r1, ld s0, ld s1) {
    ld low = 0;
    ld high = 1e18;
    ld a0 = r0 * r0 * PI;
    ld a1 = r1 * r1 * PI;
    ld eps = 1e-10;
    while(high - low > eps){
        ld mid = low + (high - low) / 2;
        ld nr0 = sqrt((a0 + s0 * PI * mid) / PI);
        ld nr1 = sqrt((a1 + s1 * PI * mid) / PI);
        if(nr0 + nr1 >= dist) {
            high = mid;
        }
        else {
            low = mid;
        }
    }
    return high;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<ld>> a(n, vector<ld>(4));
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
    }
    ld time = 0;
    while(a.size() != 1){
        //pairwise find closest pair
        ld mint = 1e18;
        int u, v;
        for(int i = 0; i < a.size(); i++){
            for(int j = i + 1; j < a.size(); j++){
                vec2 c0 = {a[i][0], a[i][1]};
                vec2 c1 = {a[j][0], a[j][1]};
                ld r0 = a[i][2];
                ld r1 = a[j][2];
                ld s0 = a[i][3];
                ld s1 = a[j][3];
                ld t = (dist(c0, c1) - (r0 + r1)) / (s0 + s1);
                // ld t = find_intt(dist(c0, c1), r0, r1, s0, s1);
                if(t < mint){
                    mint = t;
                    u = i;
                    v = j;
                }
            }
        }
        // cout << "MINT : " << mint << "\n";
        time += mint;
        for(int i = 0; i < a.size(); i++){
            a[i][2] += a[i][3] * mint;
        }
        vector<int> merge = {u, v};
        while(merge.size() > 1){
            sort(merge.begin(), merge.end());
            reverse(merge.begin(), merge.end());
            vec2 cnew = {0, 0};
            ld asum = 0;
            ld snew = 0;
            for(int i = 0; i < merge.size(); i++){
                int ind = merge[i];
                cnew = add(cnew, {a[ind][0], a[ind][1]});
                snew = max(snew, a[ind][3]);
                asum += a[ind][2] * a[ind][2] * PI;
                a.erase(a.begin() + ind);
            }
            // cout << "ASUM : " << asum << "\n";
            cnew = mul(cnew, 1.0 / merge.size());
            ld rnew = sqrt(asum / PI);
            merge = {};
            a.push_back({cnew.x, cnew.y, rnew, snew});
            //see what circles are intersecting the new one
            merge.push_back(a.size() - 1);
            for(int i = 0; i < (int) a.size() - 1; i++){
                vec2 c0 = {a[i][0], a[i][1]};
                ld r0 = a[i][2];
                if(dist(cnew, c0) < r0 + rnew) {
                    merge.push_back(i);
                }
            }
        }
    }
    cout << fixed << setprecision(10) << a[0][0] << " " << a[0][1] << "\n";
    cout << fixed << setprecision(10) << a[0][2] << "\n";

    return 0;
}