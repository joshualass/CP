#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//luckily found edge case - 49
//what happens when numbers are palindromes .. ?

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const ll N = 1e6 + 1;

ll prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <ll> prime;

void sieve (ll n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (ll i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (ll j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

void find_divs(ll idx, ll p, vector<pair<ll,ll>> &facts, vector<ll> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(ll j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
void find_divisors(ll num, vector<ll> &nums) {
    // map<ll,ll> factors;
    vector<pair<ll,ll>> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        bool first = 1;
        while(num % prime[i] == 0) {
            if(first) {
                factors.push_back({prime[i],1});
                first = 0;
            } else {
                factors.back().second++;
            }
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors.push_back({num,1});
    }
    // cout << factors << "\n";
    find_divs(0, 1, factors, nums);
}

map<ll,ll> dp0;
map<ll,ll> dp1;

ll reversenum(ll num) {
    string s = to_string(num);
    reverse(s.begin(), s.end());
    return stoll(s);
}

bool ispal(ll num) {
    return num == reversenum(num);
}

bool haszero(ll num) {
    string s = to_string(num);
    return count(s.begin(), s.end(), '0');
}

void dfs(ll n) {

    // cout << "n : " << n << '\n';

    if(dp0.count(n)) return;

    vector<ll> divs;
    find_divisors(n,divs);

    set<ll> s(divs.begin(), divs.end());

    for(ll div : s) {
        if(!haszero(div) && div > 1) {
            if(ispal(div)) {
                if(div == n) {
                    dp1[n] = div;
                } else {
                    dfs(n / div);
                    if(dp0[n / div] != -1) {
                        dp1[n] = div;
                    }
                }
            }
            ll rev = reversenum(div);
            if(s.count(rev) && s.count(div * rev)) {
                if(div * rev == n) {
                    dp0[n] = div;
                } else {
                    dfs(n / (div * rev));
                    if(dp0[n / (div * rev)] != -1) {
                        dp0[n] = div;
                    }
                }
            }
        }
    }

    if(dp0.count(n) == 0) {
        dp0[n] = -1;
    }

    if(dp1.count(n) == 0) {
        dp1[n] = -1;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    ll n; cin >> n;

    dp0[1] = 1;
    dp1[1] = 1;

    dfs(n);

    // cout << "dfs0 : " << dp0 << '\n';
    // cout << "dfs1 : " << dp1 << '\n';

    if(dp1[n] != -1) {

        string mid = to_string(dp1[n]);
        n /= dp1[n];
        string post = "";

        while(n != 1) {
            post.push_back('*');
            post.append(to_string(dp0[n]));
            n /= dp0[n] * reversenum(dp0[n]);
        }

        string rev = post;
        reverse(rev.begin(), rev.end());

        cout << rev << mid << post << '\n';

    } else if(dp0[n] != -1) {

        string post = "";
        while(n != 1) {
            post.push_back('*');
            post.append(to_string(dp0[n]));
            n /= dp0[n] * reversenum(dp0[n]);
        }

        string rev = post;
        reverse(rev.begin(), rev.end());

        cout << rev << post.substr(1) << '\n';

        
    } else {
        cout << "-1\n";
    }

    return 0;
}