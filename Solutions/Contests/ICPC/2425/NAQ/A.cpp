#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int MAXN = 2e5;
const int mgreed = 301;

ll used[MAXN], type[MAXN], a[MAXN], ma[MAXN], scores[MAXN];
ll dp[2][mgreed][31];
bool use[MAXN + 1][mgreed][31];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//if we add this number, what is the impact on the overall array
priority_queue<array<ll,2>> buildadds(int n) {
    priority_queue<array<ll,2>> pq;

    ll cm = 1;
    for(int i = n - 1; i >= 0; i--) {
        cm *= max(1LL, used[i] * type[i] * a[i]);
        if(!used[i] && type[i] == 0) {
            pq.push({a[i] * cm, i});
        }
    }

    return pq;
}

//current mults after. 
void multafter(int n) {
    ll cm = 1;
    for(int i = n - 1; i >= 0; i--) {
        if(used[i] && type[i]) {
            cm *= a[i];
        }
        ma[i] = cm;
    }
}

//get score at each index
void getscores(int n) {
    ll sc = 0;
    for(int i = 0; i < n; i++) {
        if(used[i]) {
            if(type[i]) {
                sc *= a[i];
            } else {
                sc += a[i];
            }
        }
        scores[i] = sc;
    }
}

//current value gained by each mult
vector<array<ll,2>> buildmults(int n) {
    vector<array<ll,2>> res;
    ll sc = 0;
    for(int i = 0; i < n; i++) {
        if(used[i] == 0 && type[i]) {
            res.push_back({scores[i] * (a[i] - 1) * ma[i], i});
        }
    }
    sort(res.begin(), res.end());
    return res;
}

//add element to used. 
void addelement(int n, ll &score, int toadd, priority_queue<array<ll,2>> &pq, vector<array<ll,2>> &mults) {
    used[toadd] = 1;
    // cout << "I got added : " << toadd << '\n';
    if(type[toadd]) {
        pq = buildadds(n);
        multafter(n);
        getscores(n);
        buildmults(n);
        score = scores[n-1];
    } else {
        score += a[toadd] * ma[toadd];
        for(array<ll,2>& mult : mults) {
            if(mult[1] > toadd) {
                mult[0] += a[toadd] * ma[toadd] * (a[mult[1]] - 1);
            }
        }
        sort(mults.begin(), mults.end());
    }
}

void addbestelement(int n, ll &score, priority_queue<array<ll,2>> &pq, vector<array<ll,2>> &mults, int &ml) {

    int whoadd = -1;
    if(pq.empty() && (mults.empty() || ml == 0)) {
        return;
    } else if(pq.empty()) {
        whoadd = 1;
    } else if((mults.empty() || ml == 0)) {
        whoadd = 0;
    } else {
        if(pq.top()[0] > mults.back()[0]) {
            whoadd = 0;
        } else {
            whoadd = 1;
        }
    }

    if(whoadd == 0) {
        addelement(n, score, pq.top()[1], pq, mults);
        pq.pop();
    } else {
        addelement(n, score, mults.back()[1], pq, mults);
        ml--;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<ll> type(n), a(n);

    for(int i = 0; i < n; i++) {
        char t; cin >> t;
        if(t == 'm') {
            type[i] = 1;
        }
        cin >> a[i];
    }

    int maxtake = min(mgreed - 1,n);
    int maxmulttake = min({n,k,31});
    memset(dp, 0LL, sizeof(dp));
    memset(use, 0, sizeof(use));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= maxtake; j++) {
            for(int k = 0; k <= maxmulttake; k++) {
                dp[i & 1][j][k] = dp[(i&1)^1][j][k];
                if(type[i-1]) {
                    if(k && dp[(i&1)^1][j-1][k-1] * a[i-1] > dp[i&1][j][k]) {
                        dp[i&1][j][k] = dp[(i&1)^1][j-1][k-1] * a[i-1];
                        use[i][j][k] = 1;
                    }
                } else {
                    if(dp[(i&1)^1][j-1][k] + a[i-1] > dp[i&1][j][k]) {
                        dp[i&1][j][k] = dp[(i&1)^1][j-1][k] + a[i-1];
                        use[i][j][k] = 1;
                    }
                }
            }
        }
    }

    // for(auto x : dp) {
    //     for(auto y : x) {
    //         cout << y << '\n';
    //     }
    // }

    int bestmaxmult = 0;
    for(int i = 0; i <= maxmulttake; i++) {
        if(dp[n&1][maxtake][i] > dp[n&1][maxtake][bestmaxmult]) {
            bestmaxmult = i;
        }
    }

    int currtake = maxtake, currmm = bestmaxmult;
    vector<int> used(n);

    for(int i = n; i > 0; i--) {
        if(use[i][currtake][currmm]) {
            used[i-1] = 1;
            currtake--;
            currmm -= type[i-1];
        }
    }

    vector<int> res;
    ll best = 0;
    for(int i = 1; i <= maxtake; i++) {
        for(int j = 0; j <= maxmulttake; j++) {
            best = max(best, dp[n&1][i][j]);
        }
        res.push_back(best);
    }

    priority_queue<array<ll,2>> pq = buildadds(n);
    multafter(n);
    getscores(n);
    vector<array<ll,2>> mults = buildmults(n);
    ll score = scores[n-1];
    int ml = k - bestmaxmult;

    while(res.size() != n) {
        addbestelement(n, score, pq, mults, ml);
        res.push_back(score);
    }

    for(ll x : res) {
        cout << x << '\n';
    }

    return 0;
}