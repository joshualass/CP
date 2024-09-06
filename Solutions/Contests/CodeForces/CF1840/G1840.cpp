#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    /*Research*/
    /*Random 1 will not work
    const int MAXN = 1e6;

    for(int i = 0; i < 100; i++) {
        ll m = 0;
        for(int j = 0; j < 800; j++) {
            ll num = (rng() % MAXN) + 1;
            m = max(m, num);
        }

        cout << "i : " << i << " m " << m << '\n';
    }
    */
    /*Random 2 also bad
    const int MAXN = 1e6;
   
    for(int i = 0; i < 100; i++) {
        
        vector<int> a(MAXN);
        iota(a.begin(), a.end(), 1);
        random_shuffle(a.begin(), a.end());

        int m = 0;
        int p = 0;
        for(int j = 0; j < 800; j++) {
            m = max(m, a[p]);
            p = (p + a[p]) % MAXN;
        }

        cout << "i : " << i << " m : " << m << '\n';
    
    }
    */
   /* Random 3 also bad
    const int MAXN = 1e6;

    for(int i = 0; i < 100; i++) {
        vector<int> a(MAXN);
        iota(a.begin(), a.end(), 1);
        random_shuffle(a.begin(), a.end());

        int m = 0;
        int p = 0;
        for(int j = 0; j < 800; j++) {
            m = max(m, a[p]);
            p = (p + MAXN + m * (rng() & 1 ? 1 : -1)) % MAXN;
        }

        cout << "m : " << m << '\n';

    }
    */
    
    const int MAXN = 1e6;

    for(int i = 0; i < 100; i++) {
        // vector<int> a(MAXN);
        // iota(a.begin(), a.end(), 1);
        // random_shuffle(a.begin(), a.end());
        map<int,ll> m;
        ll p = 0;
        ll add = 1;

        // m[a[0]] = 0;
        m[p % MAXN] = p;

        int found = 0;

        for(int j = 0; j < 900; j++) { //wtf
            // p = p * 2 % MOD;
            p += add;
            add = add * 2 % MOD;
            if(m.count(p % MAXN)) {
                cout << "dist : " << m[p % MAXN] << " to : " << p << '\n';
                found = 1;
            }
            m[p % MAXN] = p;
        }

        // for(int j = 0; j < 5; j++) {
        //     ll usep = rng() % 1'000'000'000;

        //     for(int k = 0; k < 200; k++) {
        //         p = p + usep;
        //         // if(m.count(a[nextp % MAXN])) {
        //         if(m.count(p % MAXN)) {
        //             // cout << "dist : " << m[a[nextp % MAXN]] << " to : " << nextp << '\n';
        //             found = 1;
        //         }
        //         // p = nextp;
        //         // m[a[p % MAXN]] = p;
        //         m[p % MAXN] = p;
        //     }

        // }

        cout << "i : " << i << " found : " << found << '\n';

    }
    




    return 0;
}