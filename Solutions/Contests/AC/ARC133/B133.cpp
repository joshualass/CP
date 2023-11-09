#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return max(a,b); //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

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

void find_divs(map<int,int>::iterator it, int p, map<int,int> &facts, set<int> &nums) {
    if(it == facts.end()) {
        if(p != 1) {
            nums.insert(p);
        }
        return;
    }
    for(int j = 0; j < (*it).second + 1; j++) {
        find_divs(++it, p, facts, nums);
        --it;
        p *= (*it).first;
    }
}

void find_divisors(int num, set<int> &nums) {
    map<int,int> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        while(num % prime[i] == 0) {
            factors[prime[i]]++;
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors[num]++;
    }
    // cout << factors << "\n";
    find_divs(factors.begin(), 1, factors, nums);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    
    int n; cin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    vector<int> aidxs(n+1);

    for(int i = 0; i < n; i++) {
        aidxs[a[i]] = i;
    }

    Tree<int> tree(n);

    for(int i = 0; i < n; i++) {
        int num = b[i];
        // vector<int> factors;
        // while(num != 1) {
        //     int factor = prime_factor[num];
        //     factors.push_back(aidxs[factor]);
        //     num /= factor;
        // }
        // factors.push_back(aidxs[1]);

        set<int> s;
        find_divisors(num, s);

        vector<int> factors;
        for(auto x : s) {
            factors.push_back(aidxs[x]);
        }
        factors.push_back(aidxs[1]);
        sort(factors.rbegin(),factors.rend());
        // cout << "i: " << i << " b[i]: " << b[i] << '\n';
        for(int factor_idx : factors) {
            // cout << "updating at index: " << factor_idx << " ";
            tree.update(factor_idx, max(tree.query(0,factor_idx) + 1, tree.query(factor_idx,factor_idx+1)));

        }
        // cout << '\n';
    }

    cout << tree.query(0,n) << '\n';

    return 0;
}