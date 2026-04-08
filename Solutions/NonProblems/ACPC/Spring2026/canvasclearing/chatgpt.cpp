#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static const ll LIM = 1000000000LL;

struct Box {
    ll minx, maxx, miny, maxy;
};

struct Event {
    ll x, y1, y2;   // update [y1, y2)
    int delta;
    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

struct SegTree {
    int n;
    vector<int> mx, lazy;

    SegTree(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = max(1, n_);
        mx.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void add(int ql, int qr, int val) {
        if (ql > qr) return;
        add(1, 0, n - 1, ql, qr, val);
    }

    void add(int node, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            mx[node] += val;
            lazy[node] += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) add(node << 1, l, mid, ql, qr, val);
        if (qr > mid)  add(node << 1 | 1, mid + 1, r, ql, qr, val);
        mx[node] = lazy[node] + max(mx[node << 1], mx[node << 1 | 1]);
    }

    int getMax() const {
        return mx[1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    const ll INF = (1LL << 60);

    vector<ll> minx(N + 1, INF), maxx(N + 1, -INF);
    vector<ll> miny(N + 1, INF), maxy(N + 1, -INF);
    vector<char> seen(N + 1, false);

    for (int i = 0; i < N; ++i) {
        ll x, y;
        int t;
        cin >> x >> y >> t;

        seen[t] = true;
        minx[t] = min(minx[t], x);
        maxx[t] = max(maxx[t], x);
        miny[t] = min(miny[t], y);
        maxy[t] = max(maxy[t], y);
    }

    vector<Box> boxes;
    boxes.reserve(N);

    for (int t = 1; t <= N; ++t) {
        if (seen[t]) {
            boxes.push_back({minx[t], maxx[t], miny[t], maxy[t]});
        }
    }

    int M = (int)boxes.size();
    if (M <= K) {
        cout << 0 << '\n';
        return 0;
    }

    int need = M - K;

    auto can = [&](ll L) -> bool {
        ll maxStart = LIM - L + 1;   // lower-left corner must be in [1, maxStart]

        vector<Event> events;
        vector<ll> ys;
        events.reserve(2 * M);
        ys.reserve(2 * M);

        int eligible = 0;

        for (const auto& b : boxes) {
            // This type's bounding box must fit inside the L x L square.
            if (b.maxx - b.minx + 1 > L) continue;
            if (b.maxy - b.miny + 1 > L) continue;

            ll x1 = max(1LL, b.maxx - L + 1);
            ll x2 = min(b.minx, maxStart);
            ll y1 = max(1LL, b.maxy - L + 1);
            ll y2 = min(b.miny, maxStart);

            if (x1 > x2 || y1 > y2) continue;

            ++eligible;

            // Rectangle of valid lower-left positions:
            // [x1, x2] x [y1, y2] on integer grid points.
            // Convert to half-open intervals for sweep/compression:
            // [x1, x2+1) x [y1, y2+1)
            events.push_back({x1,     y1, y2 + 1, +1});
            events.push_back({x2 + 1, y1, y2 + 1, -1});

            ys.push_back(y1);
            ys.push_back(y2 + 1);
        }

        if (eligible < need) return false;
        if (events.empty()) return false;

        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        sort(events.begin(), events.end());

        // Segment tree on elementary y-intervals [ys[i], ys[i+1])
        SegTree st((int)ys.size() - 1);

        int i = 0;
        while (i < (int)events.size()) {
            ll curX = events[i].x;

            while (i < (int)events.size() && events[i].x == curX) {
                int l = (int)(lower_bound(ys.begin(), ys.end(), events[i].y1) - ys.begin());
                int r = (int)(lower_bound(ys.begin(), ys.end(), events[i].y2) - ys.begin()) - 1;

                if (l <= r) st.add(l, r, events[i].delta);
                ++i;
            }

            if (st.getMax() >= need) return true;
        }

        return false;
    };

    ll lo = 1, hi = LIM;
    while (lo < hi) {
        ll mid = (lo + hi) >> 1;
        if (can(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
    return 0;
}