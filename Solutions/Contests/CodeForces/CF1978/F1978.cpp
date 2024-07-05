#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const int N = 2e6 - 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;
vector <int> divs[N];

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

void find_divs(int idx, int p, vector<pair<int,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
void find_divisors(int num, vector<int> &nums) {
    // map<int,int> factors;
    vector<pair<int,int>> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        bool first = 1;
        while(num % prime[i] == 0) {
            if(first) {
                // factors.push_back({prime[i],1});
                nums.push_back({prime[i]});
                first = 0;
            }
            num /= prime[i];
        }
    }
    if(num != 1) {
        // factors.push_back({num,1});
        nums.push_back(num);
    }
    // cout << factors << "\n";
}

int dsu[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

//x always goes to y. 
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    dsu[x] = y;
    sizes[y] += sizes[x];
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(2 * n - 1);
    for(int i = n - 1; i < 2 * n - 1; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n - 1; i++) {
        a[i] = a[i + n];

    }
    n = n * 2 - 1;
    // cout << "n : " << n << '\n';
    // cout << "a : " << a << '\n';

    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }

    unordered_map<int,int> m; 
    ll res = 0;
    ll add = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] != 1) {
            for(int div : divs[a[i]]) {
                if(div == 1) continue;
                if(m.find(div) != m.end() && m[div] + k >= i) {
                    if(find(m[div]) != find(i)) {
                        res++;
                        merge(m[div],i);
                    }
                }
                m[div] = i;
            }
        } else {
            // cout << "i : " << i << " adding : " << min(i, n - i - 1) << '\n';
            add += min(i, n - i - 1);
        }
    }
    // cout << "n : " << n << " add : " << add << " res : " << res << '\n';
    cout << n + add - res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve(1e6 + 1);
    for(int i = 1; i < N; i++) {
        find_divisors(i,divs[i]);
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}