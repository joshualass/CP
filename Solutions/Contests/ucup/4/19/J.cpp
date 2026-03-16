#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef pair<ll, ll> pii;
typedef long double ld;

void solve() {
    ll n, k; cin >> n >> k;
    ll pos = 0;
    map<ll,ll> events_poll, events_space;

    events_poll[0]++;
    events_poll[1]--;
    events_space[0] = 0;

    auto cycle_work = [&](ll &a, ll k) -> void {
        ll cycles = a / k;
        events_poll[0] += cycles;
        events_poll[k] -= cycles;

        events_space[0] += cycles;
        events_space[k] -= cycles;
        a %= k;
    };

    for(ll i = 0; i < n; i++) {
        ll a; cin >> a;
        if(i % 2 == 0) {
            if(pos + a >= k) {
                events_poll[pos + 1]++;
                events_poll[k]--;
                events_poll[0]++;
                events_poll[1]--;

                events_space[pos]++;
                events_space[k]--;

                a -= (k - pos);
                pos = 0;
            }

            cycle_work(a, k);

            //a rem
            events_poll[pos + 1]++;
            events_poll[pos + 1 + a]--;

            events_space[pos]++;
            events_space[pos + a]--;

            pos += a;
        } else {
            if(a >= pos) {
                events_poll[0]++;
                events_poll[pos]--;

                events_space[0]++;
                events_space[pos]--;

                a -= pos;
                pos = 0;
            }
            cycle_work(a, k);

            //a rem down
            if(a && pos == 0) pos = k;
            events_poll[pos - a]++;
            events_poll[pos]--;

            events_space[pos - a]++;
            events_space[pos]--;

            pos -= a;
        }
    }

    events_poll.erase(k);
    events_space.erase(k);

    ll lo = LLONG_MAX, hi = LLONG_MIN;
    ll cur = 0;
    // cout << "events poll" << endl;
    for(auto [pos, d] : events_poll) {
        cur += d;
        // cout << "pos : " << pos << " d : " << d << " cur : " << cur << endl;
        lo = min(lo, cur);
        hi = max(hi, cur);
    }
    cur = 0;
    // cout << "events space" << endl;
    for(auto [pos, d] : events_space) {
        cur += d;
        // cout << "pos : " << pos << " d : " << d << " cur : " << cur << endl;
        lo = min(lo, cur);
        hi = max(hi, cur);
    }

    cout << lo << " " << hi << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll casi; cin >> casi;
    while(casi-->0) solve();    

    return 0;
}