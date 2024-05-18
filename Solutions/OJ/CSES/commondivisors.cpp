#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e6 + 1;

int facts[N];
int prime_factor[N]; //stores 

std::vector <int> prime;

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

void find_divs(int i, int p, vector<pair<int,int>> &v) {
    // cout << "i: " << i << " p: " << p << "\n";
    if(i == v.size()) {
        facts[p]++;
        return;
    }
    for(int j = 0; j < v[i].second + 1; j++) {
        find_divs(i + 1, p, v);
        p *= v[i].first;
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    
    sieve(N);
    
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        map<int,int> m;
        while(num != 1) {
            if(m.find(prime_factor[num]) == m.end()) {
                m[prime_factor[num]] = 1;
            } else {
                m[prime_factor[num]]++;
            }
            num /= prime_factor[num];
        }
        vector<pair<int,int>> v(0);
        for(auto x : m) {
            v.push_back(x);
        }
        find_divs(0, 1, v);
    }
    for(int i = N; i >= 1; i--) {
        if(facts[i] >= 2) {
            cout << i << "\n";
            return 0;
        }
    }

    return 0;
}