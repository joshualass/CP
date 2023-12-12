#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n) {
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

void solve() {
    int p; cin >> p;
    vector<int> ans(0);
    for(int i = 0; i < prime.size() && prime[i] * prime[i] <= p; i++) {
        while(p % prime[i] == 0) {
            ans.push_back(prime[i]);
            p /= prime[i];
        }
    }
    if(p != 1) {
        ans.push_back(p);
    }
    int sum = accumulate(ans.begin(),ans.end(),0);
    if(sum > 41) {
        cout << "-1";
    } else {
        int ones = 41 - sum;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(auto x : ans) pq.push(x);
        while(pq.size() >= 2) {
            int first = pq.top(); pq.pop();
            int second = pq.top(); pq.pop();
            // cout << "first: " << first << " second: " << second << "\n";
            if(first * second - (first + second) <= ones) {
                ones -= first * second - (first + second);
                pq.push(first * second);
                // cout << "better\n";
            } else {
                pq.push(first); pq.push(second); break;
            }
        }
        while(pq.size()) {
            cout << pq.top() << " ";
            pq.pop();
        }
        for(int i = 0; i < ones; i++) {
            cout << "1 ";
        }
        // for(int i = 0; i < ones; i++) {
        //     ans.push_back(1);
        // }
        // cout << ans.size() << " ";
        // for(auto &x: ans) cout << x << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("B2.in","r",stdin);
    freopen("B2.txt","w",stdout);

    sieve(1e5);

    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}