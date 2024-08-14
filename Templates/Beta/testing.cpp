#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int n;

struct compare_1 {
    bool operator()(const string &lhs, const string &rhs) const {
        if(lhs.size() != rhs.size()) {
            return lhs.size() < rhs.size();
        } else {
            return lhs < rhs;
        }
    }
};

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D, compare_1> m) {
    // for(auto &x: m) os << x.first << " " << x.second << " | ";
    for(auto &x : m) os << "string : " << x.first << string(n - x.first.size() + 2, ' ') << " winnable ? " << x.second.first << " win by : " << x.second.second << '\n';
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) {
        if(x == string(x.rbegin(), x.rend())) {
            os << x << "\n";
        }
    }
    return os;
}

map<string, pair<bool,string>, compare_1> dp;

string extractidx(string s, int idx) {
    s.erase(s.begin() + idx, s.begin() + idx + 1);
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == s[i-1]) {
            s.erase(s.begin() + i - 1, s.begin() + i);
        }
    }
    return s;
}

void recur(string s) {
    string winner = "";
    bool found = 0;
    for(int i = 0; i < s.size(); i++) {
        string extracted = extractidx(s,i);
        if(dp.count(extracted) && dp[extracted].first == 0) {
            winner = extracted;
            found = 1;
        }
    }

    dp[s] = {found, winner};

    if(s.size() < n) {
        char p = (s.empty() ? 'd' : s.back());
        for(int i = 0; i < 3; i++) {
            if(p != 'a' + i) {
                s.push_back('a' + i);
                recur(s);
                s.pop_back();
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    
    recur("a");

    // cout << "dp\n" << dp << '\n';
    vector<string> winnings, losings;
    for(auto x : dp) {
        if(x.second.first) {
            winnings.push_back(x.first);
        } else {
            losings.push_back(x.first);
        }
    }

    sort(winnings.begin(), winnings.end(), [](const string &lhs, const string &rhs) {
        if(lhs.size() == rhs.size()) {
            return lhs < rhs;
        } else {
            return lhs.size() < rhs.size();
        }
    });

    sort(losings.begin(), losings.end(), [](const string &lhs, const string &rhs) {
        if(lhs.size() == rhs.size()) {
            return lhs < rhs;
        } else {
            return lhs.size() < rhs.size();
        }
    });

    cout << "losings\n" << losings;
    cout << "winnings\n" << winnings;

    return 0;
}