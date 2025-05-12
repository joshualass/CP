#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
you may think you need some generating function knowledge, but it is not needed
need to be slightly efficient with the programming/use a modint and save memory from dp

how does one count inversions? one does so by working backwards and inserting an element anywhere 
into the permutation. 

we can use the above to compute a dp table to compute inv[i][j] storing the number of permutations of 
length i and having j inversions. Then, given this informationn, we want to try and compute the number 
of inversions from adding an element. 

we should also see that p is lexicographically smaller than q at some point, meaning the pairs are distinct 
on the first index they differ and can be the same for a bit. 

We see that there are i ways to make a difference of 1 and use this pattern to count things. 
we use a prefix prefix to help compute this as well as a running count of the sums of prefix prefix stuff c

it didn't take very long to see how to do the dp, but some aspects of the implementation were rough. 

forgot to use choose and factorial stuff. 

Very smart to right a solve slow method to debug problems ft. andwerp
this helped me debug the fact that i was missing the factorial part. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int ub = 124751;
int inv[ub];
int p[ub], pp[ub];
int choose[501][501], fact[501];;

vector<int> cntslow(int n) {
    auto getinv = [&](vector<int> p) -> int {
        int res = 0;
        for(int i = 0; i < p.size(); i++) {
            for(int j = i + 1; j < p.size(); j++) {
                res += p[i] > p[j];
            }
        }
        return res;
    };
    auto cntsame = [&](vector<int> p, vector<int> q) -> int {
        int res = 0;
        while(p[res] == q[res]) res++;
        return res;
    };
    vector<int> p(n), q(n);
    iota(p.begin(), p.end(), 0);
    vector<int> res(n + 1);
    while(1) {
        iota(q.begin(), q.end(), 0);
        while(1) {
            if(p < q && getinv(p) > getinv(q)) res[cntsame(p,q)]++;
            if(!next_permutation(q.begin(), q.end())) break;
        }
        if(!next_permutation(p.begin(), p.end())) break;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    int res = 0;

    inv[0] = 1;

    auto add_norm = [&](int x) -> int {
        if(x < 0) x += m;
        if(x >= m) x -= m;
        return x;
    };

    for(int i = 0; i <= 500; i++) {
        for(int j = 0; j <= i; j++) {
            if(i) {
                choose[i][j] = add_norm(choose[i-1][j] + (j ? choose[i-1][j-1] : 0));
            } else {
                choose[i][j] = 1;
            }
            // if(i <= 10 && j <= 10) {
            //     cout << choose[i][j] << " ";
            // }
        }
        // cout<< '\n';
    }

    fact[0] = 1;
    for(int i = 1; i <= 500; i++) fact[i] = (1LL * fact[i-1] * i) % m;

    auto get_p = [&](int l, int r) -> int {
        return add_norm(p[r] - (l ? p[l-1] : 0));
    };

    auto get_pp = [&](int l, int r) -> int {
        return add_norm(pp[r] - (l ? pp[l-1] : 0));
    };

    for(int i = 0; i < n; i++) {
        //build p and pp
        int stp = i * (i - 1) / 2;
        // cout << "i : " << i << " res : " << res << '\n';
        // cout << "inv : ";
        // for(int j = 0; j <= stp; j++) {
        //     cout << inv[j] << " \n"[j == stp];
        // }
        for(int j = 0; j < ub; j++) {
            p[j] = add_norm((j ? p[j-1] : 0LL) + inv[j]);
        }
        // cout << "p : ";
        // for(int j = 0; j <= stp; j++) {
        //     cout << p[j] << " \n"[j == stp];
        // }
        for(int j = 0; j < ub; j++) {
            pp[j] = add_norm((j ? pp[j-1] : 0LL) + p[j]);
        }
        // cout << "pp : ";
        // for(int j = 0; j <= stp; j++) {
        //     cout << pp[j] << " \n"[j == stp];
        // }
        int c = 0;
        int mul = 1LL * choose[n][i + 1] * fact[n - i - 1] % m;
        int add = 0;
        for(int j = 0; j <= stp; j++) {
            if(j >= 2) {
                c = (c + 1LL * p[j-2] * i) % m;
            }
            if(j >= 3) {
                c = (c - get_pp(max(0, j - 3 - i + 1), j - 3) + m) % m;
            }
            // cout << "i : " << i << " j : " << j << " c : " << c << '\n';
            add = (add + 1LL * c * inv[j] % m * mul) % m;
        }
        // cout << "i : " << i << " add : " << add << '\n';
        // cout << "mul : " << mul << '\n';
        res = add_norm(res + add);

        for(int j = 0; j < ub; j++) {
            inv[j] = get_p(max(0, j - i), j);
        }
    }

    cout << res << '\n';
    // vector<int> cnts = cntslow(n);

    // cout << "cnts : " << cnts << '\n';

    return 0;
}
