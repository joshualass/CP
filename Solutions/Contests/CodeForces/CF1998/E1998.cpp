#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//same bad idea, different day

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

void solve() {
    
    int n, x; cin >> n >> x;
    vector<ll> a(n), p(n + 1);


    for(int i = 0; i < n; i++) {
        cin >> a[i];
        p[i+1] = p[i] + a[i];
    }

    vector<int> lefts(n);
    stack<int> s;
    for(int i = n - 1; i >= 0; i--) {

        while(s.size() && a[i] > p[s.top() + 1] - p[i + 1]) {
            lefts[s.top()] = i + 1;
            s.pop();
        }

        s.push(i);

    }

    // cout << "lefts : " << lefts << '\n';

    vector<int> res(n);
    vector<int> clear(n);

    deque<array<int,2>> q; //{left, cnt}

    for(int i = 0; i < n; i++) {

        while(1) {
            int action = 0;

            while(q.size()) {
                array<int,2> t = q.back();
                q.pop_back();
                if(t[0] != 0 && p[i] - p[t[0]] >= a[t[0] - 1]) {
                    action = 1;
                    if(q.size()) {
                        q.back()[1] += t[1];
                    } else {
                        q.push_back({0, t[1]});
                    }
                } else {
                    // cout << "get back to the queue! " << t << '\n';
                    q.push_back(t);
                    break;
                }
            }

            if(q.size() && a[i] > (p[i] - p[q.back()[0]])) {
                // cout << "erasing : " << q.back() << " i : " << i << '\n';
                q.pop_back();
                action = 1;
            }

            if(!action) break;

        }

        q.push_back({lefts[i], 1});

        while(q.size() && (q.front()[0] == 0 || p[i+1] - p[q.front()[0]] >= a[q.front()[0] - 1])) {
            res[i] += q.front()[1];
            q.pop_front();
        }

        if(a[i] > p[i]) clear[i] = 1;

    }

    int cur = 0;

    for(int i = 0; i < n; i++) {
        if(clear[i]) cur = 0;
        cur += res[i];
        // if(i == n - 1) {
            cout << cur << " \n"[i == n - 1];
        // }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}