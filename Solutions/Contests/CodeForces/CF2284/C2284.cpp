#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//need to build sieve, typically with N
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

int isprime(ll num) {
    vector<pair<ll,int>> prime_factors;
    for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
        if(num % prime[i] == 0) {
            prime_factors.push_back({prime[i],0});
            while(num % prime[i] == 0) {
                prime_factors.back().second++;
                num /= prime[i];
            }
        }
        while(num < N && num != 1) {
            int t = prime_factor[num];
            prime_factors.push_back({t, 0});
            while(num % t == 0) {
                prime_factors.back().second++;
                num /= t;
            }
        }
    }
    if(num != 1) {
        prime_factors.push_back({num,1});
    }
    return sz(prime_factors) == 1 && prime_factors.back().second == 1;
}

// void solve() {
    
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     for(int i = 0; i < n; i++) {
//         int x = a[i];
//         while(prime_factor[x] != x) x++;
//         cout << x << " " ;
//     }
//     cout << '\n';

// }

void solve() {
    int a, b;
    
    // cin >> a >> b;

    a = 436273010, b = 436273290;

    vector<int> ops;

    if(a == b) {

    } else if(gcd(a, b - a) == 1) {
        ops.push_back(b - a);
    } else {
        int f = -1;
        for(int i = b; i >= a; i--) {
            if(gcd(i, b) == 1 && isprime(i)) {
                f = i;
                break;
            }
        }

        if(f == -1) {
            vector<int> par(b - a + 1, -1);
            queue<int> q;
            q.push(0);
            while(!q.empty()) {
                int x = q.front();
                q.pop();
                int cur = x + a;
                for(int i = 1; cur + i <= b; i++) {
                    if(par[x + i] == -1 && gcd(cur, i) == 1) {
                        q.push(x + i);
                        par[x + i] = x;
                    }
                }
            }

            // cout << "a : " << a << " b : " << b << " par : " << par << endl;

            int p = b - a;
            while(p) {
                // cout << "p : " << p << endl;
                ops.push_back(p - par[p]);
                p = par[p];
            }
            reverse(ops.begin(), ops.end());
        } else {
            ops = {f - a, b - f};
        }
    }

    cout << sz(ops) << '\n';
    cout << ops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    clock_t tStart = clock();

    printf("Time taken start : %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    sieve();

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    printf("Time taken end : %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}