#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// https://open.kattis.com/problems/money

// template<typename T>
template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll recur (int plo, int phi, int clo, int chi, vector<pair<ll,ll>> &p, vector<pair<ll,ll>> &c) {

    if(plo == phi) return 0;
    
    int m = plo + (phi - plo) / 2;

    int best_idx = -1;
    ll best_score = 0;
    int last_to_left = -1;

    for(int i = clo; i < chi; i++) {
        if(c[i].second < p[m].second) {
            last_to_left = i;
        }
        
        ll score = (c[i].first - p[m].first) * (c[i].second - p[m].second);
        if(score > 0 && (c[i].second - p[m].second) < 0) {
            score = 0;
        }
        if(score > best_score) {
            best_score = score;
            best_idx = i;
        }
    }

    if(best_idx == -1) {
        best_idx = last_to_left;
    }

    return max({recur(plo, m, clo, best_idx + 1, p, c), best_score, recur(m + 1, phi, best_idx, chi, p, c)});

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int producers, consumers; cin >> producers >> consumers;

    vector<pair<ll,ll>> p(producers);
    vector<pair<ll,ll>> c(consumers);

    for(int i = 0; i < producers; i++) {
        cin >> p[i].first >> p[i].second;
    }

    
    for(int i = 0; i < consumers; i++) {
        cin >> c[i].first >> c[i].second;
    }

    sort(p.begin(), p.end(), [] (const pair<ll,ll> &lhs, const pair<ll,ll> &rhs) {
        if(lhs.second == rhs.second) {
            return lhs.first < rhs.first;
        } else {
            return lhs.second < rhs.second;
        }
    });

    
    sort(c.begin(), c.end(), [] (const pair<ll,ll> &lhs, const pair<ll,ll> &rhs) {
        if(lhs.second == rhs.second) {
            return lhs.first < rhs.first;
        } else {
            return lhs.second < rhs.second;
        }
    });

    vector<pair<ll,ll>> p_p;
    vector<pair<ll,ll>> p_c;


    ll min_production = LLONG_MAX;

    for(int i = 0; i < producers; i++) {
        if(p[i].first < min_production) {
            p_p.push_back(p[i]);
            min_production = p[i].first;
        }
    }

    ll max_consume = LLONG_MIN;

    for(int i = consumers - 1; i >= 0; i--) {
        if(c[i].first > max_consume) {
            p_c.push_back(c[i]);
            max_consume = c[i].first;
        }
    }

    reverse(p_c.begin(), p_c.end());
    // cout << "pruned producers: " << p_p << '\n';

    int plo = 0;
    int phi = p_p.size();

    int clo = 0;
    int chi = p_c.size();

    ll best = recur(plo, phi, clo, chi, p_p, p_c);

    cout << best << '\n';

    return 0;
}