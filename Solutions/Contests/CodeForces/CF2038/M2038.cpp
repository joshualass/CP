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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

ll inf = 1e9;

map<array<int,5>, ld> dp [6][6][6][6][33];


ld dfs(array<int,5> a, int one, int two, int three, int four, int rem) {

    sort(a.begin(), a.end());
    // cout << "a : " << a << " one : " << one << " two : " << two << " three : " << three << " four : " << four << " rem : " << rem << endl;

    //transform first later !


    if(dp[one][two][three][four][rem].count(a) == 0) {
        //check if it's winnable from here
        int cntone = 0, cnttwo = 0, cntthree = 0, cntfour = 0;
        for(int x : a) {
            if(x == 0) cntone++;
            if(x == 1) cnttwo++;
            if(x == 2) cntthree++;
            if(x == 3) cntfour++;
        }

        ld res;

        if(cntone == 5 || cnttwo == 5 || cntthree == 5 || cntfour == 5) {
            res = 0;
        } else if(one + cntone < 5 && two + cnttwo < 5 && three + cntthree < 5 && four + cntfour < 5) {
            res = inf;
        } else if(a[0] == -1) {
            ld total_rem = one + two + three + four + rem;
            res = 0;
            if(one) {
                ld p = one / total_rem;
                a[0] = 0;
                res += p * dfs(a, one - 1, two, three, four, rem);
            }
            if(two) {
                ld p = two / total_rem;
                a[0] = 1;
                res += p * dfs(a, one, two - 1, three, four, rem);
            }
            if(three) {
                ld p = three / total_rem;
                a[0] = 2;
                res += p * dfs(a, one, two, three - 1, four, rem);
            }
            if(four) {
                ld p = four / total_rem;
                a[0] = 3;
                res += p * dfs(a, one, two, three, four - 1, rem);
            }
            if(rem) {
                ld p = rem / total_rem;
                a[0] = 4;
                res += p * dfs(a, one, two, three, four, rem - 1);
            }
            a[0] = -1;
        } else {
            res = inf;
            for(int bm = 1; bm < 1 << 5; bm++) {
                auto b = a;
                for(int j = 0; j < 5; j++) {
                    if((bm >> j) & 1) {
                        b[j] = -1;
                    }
                }
                res = min(res, 1 + dfs(b, one, two, three, four, rem));
            }
        }
        dp[one][two][three][four][rem][a] = res;
    }

    return dp[one][two][three][four][rem][a];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n; cin >> n;
    // int one = (n >= 1 ? 5 : 0);
    // int two = (n >= 2 ? 5 : 0);
    // int three = (n >= 3 ? 5 : 0);
    // int four = (n >= 4 ? 5 : 0);
    // int rem = n * 8;

    // cout << fixed << setprecision(10) << dfs({-1, -1, -1, -1, -1}, one, two, three, four, rem) << '\n';

    int n; cin >> n;
    vector<ld> res = {
        3.5982905983,
        8.0671713085,
        12.4230759346,
        16.6366423608
    };

    cout << fixed << setprecision(10) << res[n - 1] << '\n';

    return 0;
}

/*
3.5982905983
8.0671713085
12.4230759346
16.6366423608
*/