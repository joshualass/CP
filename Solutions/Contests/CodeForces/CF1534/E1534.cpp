#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int debug = 0;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve(int n, int k) {

    // cout << "n : " << n << " k : " << k << endl;

    vector<int> v(n);
    int tr = 0;

    auto ask = [&](vector<int> a) -> void {
        assert(sz(a) == k);
        cout << "?";
        for(int x : a) {
            cout << " " << x + 1;
            v[x] ^= 1;
        }
        cout << endl;
        int res; 
        if(debug == 0) {
            cin >> res;
        } else {
            res = rng() % 676767;
        }
        tr ^= res;
    };

    // int ttfang = 0;

    // while(accumulate(v.begin(), v.end(), 0) != n) {
    //     int sum = accumulate(v.begin(), v.end(), 0);
    //     int empty = n - sum;
    //     vector<int> a;
    //     int zero = 0, one = 0;
    //     if(empty % k) {

    //         int f = 0;
    //         for(int i = 0; i <= k; i++) {
    //             int nz = k - i;
    //             int nx_empty = empty + i - nz;
    //             if(nx_empty % k == 0 && i <= sum && nz <= empty) {
    //                 f = 1;
    //                 one = i;
    //                 zero = nz;
    //             }
    //         }

    //         // cout << "f : " << f << endl;

    //         if(f == 0) {
    //             if(ttfang) {
    //                 zero = min(k, empty);
    //                 one = k - zero;
    //             } else {
    //                 one = min(k, sum);
    //                 zero = k - one;
    //             }
    //         }

    //     } else {
    //         zero = k;
    //         one = 0;
    //     }

    //     // cout << "sum : " << sum << " empty : " << empty << endl;
    //     // cout << "z : " << zero << " o : " << one << endl;

    //     assert(one <= sum);
    //     assert(zero <= empty);
    //     assert(one + zero == k);
        
    //     for(int i = 0; i < n; i++) {
    //         if(v[i] == 0 && zero) {
    //             a.push_back(i);
    //             zero--;
    //         }
    //         if(v[i] == 1 && one) {
    //             a.push_back(i);
    //             one--;
    //         }
    //     }

    //     ttfang ^= 1;

    //     ask(a);
    // }

    const array<int,3> def = {-1,-1,-1};

    queue<int> q;
    vector<array<int,3>> p(n + 1, def);

    auto pushq = [&](int x, array<int,3> par) -> void {
        if(p[x] == def) {
            p[x] = par;
            q.push(x);
        }
    };

    pushq(0, {-1, 0, 0});

    while(sz(q)) {
        int x = q.front();
        q.pop();

        int empty = n - x;
        
        for(int o = 0; o <= k; o++) {
            int z = k - o;
            if(o <= x && z <= empty) {
                pushq(x + z - o, {x, z, o});
            }
        }
    }

    if(p[n] == def) {
        cout << "-1\n";
        return;
    }

    vector<array<int,2>> path;
    int cur = n;
    while(cur) {
        path.push_back({p[cur][1], p[cur][2]});
        cur = p[cur][0];
    }

    for(auto [zero, one] : path) {
        int sum = accumulate(v.begin(), v.end(), 0);
        int empty = n - sum;

        assert(one <= sum);
        assert(zero <= empty);
        assert(one + zero == k);

        vector<int> a;
        
        for(int i = 0; i < n; i++) {
            if(v[i] == 0 && zero) {
                a.push_back(i);
                zero--;
            }
            if(v[i] == 1 && one) {
                a.push_back(i);
                one--;
            }
        }

        ask(a);
    }

    cout << "! " << tr << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if(debug == 0) {
        int n, k; cin >> n >> k;
        solve(n, k);
    } else {
        for(int n = 1; n <= 10; n++) {
            for(int k = 1; k <= n; k++) {
                solve(n, k);
            }
        }
    }


    return 0;
}
