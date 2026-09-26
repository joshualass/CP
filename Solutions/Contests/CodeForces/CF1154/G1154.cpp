#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int N = 1e7 + 1;

int lo[N][2];
int a[1000000];

//need to build sieve, typically with N
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

void add_lo(int x, int i) {
    if(i + 1 == lo[x][0] || i + 1 == lo[x][1]) return;
    if(lo[x][0] == 0) {
        lo[x][0] = i + 1;
    } else if(a[i] <= a[lo[x][0] - 1]) {
        lo[x][1] = lo[x][0];
        lo[x][0] = i + 1;
    } else if(lo[x][1] == 0 || a[i] <= a[lo[x][1] - 1]) {
        lo[x][1] = i + 1;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    sieve();

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        add_lo(a[i], i);
    }

    ll res = LLONG_MAX;
    int ban, ana; 
    for(int i = N - 1; i >= 1; i--) {
        for(int x : prime) {
            if(i * x < N) {
                for(int j = 0; j < 2; j++) {
                    if(lo[i * x][j]) add_lo(i, lo[i * x][j] - 1);
                }
            } else {
                break;
            }
        }
        int l = lo[i][0], r = lo[i][1];
        if(l && r) {
            l--; r--;
            // if(i < 100) { 
            //     cout << "i : " << i << " l : " << l << " r : " << r << endl;
            // }
            if(1LL * a[l] * a[r] / i < res) {
                res = 1LL * a[l] * a[r] / i;
                ban = l + 1, ana = r + 1;
            }
        }
    }

    if(ban > ana) swap(ban, ana);

    cout << ban << " " << ana << '\n';

    return 0;
}
