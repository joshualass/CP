#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

void calc_p(int cur, int _p, vector<vector<int>>& c, vector<int>& p) {
    p[cur] = _p;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == _p){
            continue;
        }
        calc_p(next, cur, c, p);
    }
}

ll get_end(int cur, vector<int>& p, vector<ll>& val, vector<bool>& is_set, ll prime) {
    ll end = 1;
    while(!is_set[cur]) {
        end *= prime;
        cur = p[cur];
    }
    end *= val[cur];
    return end;
}

void set_vals(int cur, vector<int>& p, vector<ll>& val, vector<bool>& is_set, ll prime) {
    vector<int> ids(0);
    while(!is_set[cur]) {
        ids.push_back(cur);
        cur = p[cur];
    }
    reverse(ids.begin(), ids.end());
    for(int i = 0; i < ids.size(); i++){
        int next = ids[i];
        is_set[next] = true;
        val[next] = val[p[next]] * prime;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vector<int> p(n);
    calc_p(0, -1, c, p);
    vector<ll> val(n, 0);
    val[0] = 1;
    vector<bool> is_set(n, false);
    is_set[0] = true;
    sieve();
    for(int i = 0; i < prime.size(); i++){
        ll n_prime = prime[i];
        ll max_end = 0;
        ll id = -1;
        for(int j = 0; j < n; j++){
            if(!is_set[j]) {
                ll n_end = get_end(j, p, val, is_set, n_prime);
                if(n_end > max_end) {
                    max_end = n_end;
                    id = j;
                }
            }
        }
        if(id == -1){
            break;
        }
        set_vals(id, p, val, is_set, n_prime);
    }
    for(int i = 0; i < n; i++){
        cout << val[i] << " \n"[i == n - 1];
    }

    return 0;
}