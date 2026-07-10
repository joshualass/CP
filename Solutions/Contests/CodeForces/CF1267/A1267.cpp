#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,3>> events;

    for(int i = 0; i < n; i++) {
        ll a, b, t; cin >> a >> b >> t;
        events.push_back({a, b, t});
    }

    sort(events.begin(), events.end());

    set<array<ll,3>> s; // {t, a, b}
    ll time = 0, res = 0;

    auto prune = [&]() -> void {
        while(sz(s)) {
            auto [t, a, b] = *s.begin();
            if(time + t > b) {
                s.erase(s.begin());
            } else {
                break;
            }
        }
    };

    array<ll,3> def = {-1,-1,-1};

    int p = 0;
    while(time < 1e18) {
        array<ll,3> best = def;
        prune();

        // cout << "p : " << p << " time : " << time << " res : " << res << " s : " << s << endl;

        if(sz(s)) {
            best = *s.begin();
            assert((*s.begin())[1] <= time); 
            //everything in the set is activated
        }
        while(p < n && (best == def || best != def && events[p][0] < max(best[1], time) + best[0])) {
            auto [a, b, t] = events[p++];
            if(best == def || max(a, time) + t < max(best[1], time) + best[0]) {
                best = {t, a, b};
            }
            s.insert({t, a, b});
        }
        if(best == def) {
            time = 1e18;
            continue;
        }
        // cout << "best : " << best << endl;
        assert(sz(s));
        ll use;
        time = max(time, best[1]);
        if(best == *s.begin()) {
            use = min((best[2] - time) / best[0], p < n ? (events[p][0] - time) / best[0] : LLONG_MAX);
        } else {
            //just one time, dealer
            use = 1;
        }
        res += use;
        time += best[0] * use;
        assert(time <= best[2]);
    }

    cout << res << '\n';

    return 0;
}
