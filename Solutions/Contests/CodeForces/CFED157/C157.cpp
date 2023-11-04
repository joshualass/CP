#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int getsum(string str) {
    int sum = 0;
    for(int i = 0; i < str.size(); i++) {
        sum += str[i] - '0';
    }
    return sum;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll dp[12][12][50];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            for(int k = 0; k < 50; k++) {
                dp[i][j][k] = 0;
            }
        }
    }

    int n; cin >> n;

    vector<string> tickets(n);

    for(auto &x : tickets) cin >> x;

    for(int i = 0; i < n; i++) {
        int sum = getsum(tickets[i]);
        for(int j = 0; j < tickets[i].size(); j++) {
            if(sum >= 0) {
                // cout << "Ticket: " << tickets[i] << " adding to: " << tickets[i].size() << " " << j << " " << sum << '\n';
                dp[tickets[i].size()][j][sum]++;
            }
            sum -= (tickets[i][j] - '0') * 2;
        }
    }

    //size, how many to the left of pivot, right - left of pivot score, count

    // cout << "hey";

    ll ans = 0;

    // for(int i = 0; i < n; i++) {
    //     int sum = 0;
    //     int rsum = getsum(tickets[i]);
    //     for(int lsize = 1; lsize <= max(tickets[i].size(), ; lsize++) {
    //         sum += tickets[i][lsize-1] - '0';
    //         rsum -= tickets[i][lsize-1] - '0';
    //         if(lsize >= (tickets[i].size() + 1) / 2) {
    //             int totalsize = lsize * 2;
    //             int idx = tickets[i].size() - lsize;
    //             int score = sum - rsum;
    //             if(score >= 0) {
    //                 ans += dp[totalsize - lsize][idx][score];
    //             }
    //         }
    //     }
    // }

    for(int i = 0; i < n; i++) {
        int scorebefore = 0;
        int scoreafter = getsum(tickets[i]);
        for(int pivot = 1; pivot <= 5; pivot++) {
            if(tickets[i].size() >= pivot) {
                scorebefore += tickets[i][pivot - 1] - '0';
                scoreafter -= tickets[i][pivot - 1] - '0';
            }
            int string_size = pivot * 2 - tickets[i].size();
            int idx = max(0, pivot - (int) tickets[i].size());
            int score = scorebefore - scoreafter;
            if(string_size >= 0 && idx >= 0 && score >= 0) {
                // cout << "curr ticket: " << tickets[i] << " pivot: " << pivot << " stats: " << string_size << " " << idx << " " << score << " adding: " << dp[string_size][idx][score] << '\n';
                ans += dp[string_size][idx][score];
            }
        }
    }

    cout << ans << '\n';

    return 0;
}