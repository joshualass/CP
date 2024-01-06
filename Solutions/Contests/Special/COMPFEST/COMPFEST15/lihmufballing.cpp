#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll calc_tri(ll start, ll diff, ll cnt) {
    return start * cnt + cnt * (cnt - 1) / 2 * diff;
}

ll solve(int n, int k) {
    if(k == 1) return 0;
    vector<bool> visited(k);
    int pan_idx = 0;
    int cycle = k - 1;
    ll score = 0;

    while(visited[cycle] == 0) {
        visited[cycle] = 1;
        //find first time where they don't intersect
        if(cycle <= pan_idx) {
            int behind = pan_idx - cycle;
            int diff = k - 1;
            int extra_moves = behind / diff + 1;
            // cout << "pan : " << pan_idx << " cycle : " << cycle << " extra moves : " << extra_moves << '\n';
            if(cycle + extra_moves * k >= n) { //0 score from this cycle
                int moves_until_next_cycle = (n - cycle + (k - 1)) / k;
                pan_idx += moves_until_next_cycle;
                cycle += moves_until_next_cycle * k;
                cycle %= n;
                continue;
            }
            pan_idx += extra_moves;
            cycle += extra_moves * k;
        }
        //on a spot where they grab the balls
        int moves_until_next_cycle = (n - cycle + (k - 1)) / k;
        // cout << "k : " << k << " cycle : " << cycle << "moves u n c : " << moves_until_next_cycle << '\n';
        score += calc_tri(cycle + 1, k, moves_until_next_cycle);
        pan_idx += moves_until_next_cycle;
        cycle += moves_until_next_cycle * k;
        cycle %= n;
    }
    return score;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, K; cin >> n >> K;
    pair<ll,ll> ans = {-1,-1};
    for(int k = 1; k <= K; k++) {
        // cout << "k : " << k << '\n';
        ll try1 = solve(n,k);
        // cout << "try1 : " << try1 << '\n';
        if(try1 > ans.first) {
            ans = {try1, k};
        }
    }
    cout << ans.second << '\n';
    return 0;
}