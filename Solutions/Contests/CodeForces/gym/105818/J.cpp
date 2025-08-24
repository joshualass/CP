#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, qx, qy, qz; cin >> n >> qx >> qy >> qz;
    vector<pair<char, array<ll,3>>> ops;

    auto draw = [&](ll type, ll c1, ll c2, ll w) -> void {
        char c = (type == 0 ? 'X' : type == 1 ? 'Y' : 'Z');
        ops.push_back({c, {c1, c2, w}});
    };

    auto draw_parallelogram = [&](ll t, array<ll,2> lower, array<ll,2> higher, ll w) -> void {
        // cout << "t : " << t << " lower : " << lower << " higher : " << higher << " w : " << w << '\n';
        draw(t, higher[0], higher[1], w);
        if(lower[0]) {
            draw(t, lower[0] - 1, higher[1], -w);
        }
        if(lower[1]) {
            draw(t, higher[0], lower[1] - 1, -w);
        }
        if(lower[0] && lower[1]) {
            draw(t, lower[0] - 1, lower[1] - 1, w);
        }
    };

    ll w = 1;
    while(1) {
        // cout << "qx : " << qx << " qy : " << qy << " qz : " << qz << '\n';
        if(qx + qy + qz <= n) {
            // cout << "case0\n";
            ll len = n - (qx + qy + qz);
            if(len == 0) {
                draw_parallelogram(0, {qy, qz}, {qy, qz}, w);
                break;
            }
            ll add = len / 2;
            // cout << "len : " << len << " add : " << add << '\n';
            draw_parallelogram(0, {qy, qz}, {qy + add, qz + add}, w);
            draw_parallelogram(1, {qz, qx}, {qz + add, qx + add}, w);
            draw_parallelogram(2, {qx, qy}, {qx + add, qy + add}, w);
            if(len == 1) break;
            qx += add;
            qy += add;
            qz += add;
        } else {
            // cout << "case1\n";
            ll len = (qx + qy + qz) - n;
            ll add = - (len / 2);
            // cout << "len : " << len << " add : " << add << '\n';
            draw_parallelogram(0, {qy + add, qz + add}, {qy, qz}, w);
            draw_parallelogram(1, {qz + add, qx + add}, {qz, qx}, w);
            draw_parallelogram(2, {qx + add, qy + add}, {qx, qy}, w);
            if(len == 1) break;
            qx += add;
            qy += add;
            qz += add;
        }
        w *= -2;
    }

    cout << ops.size() << '\n';
    for(auto [type, coords] : ops) {
        cout << type << " " << coords[0] << " " << coords[1] << " " << coords[2] << '\n';
    }

    return 0;
}
