//was trying to solve https://www.codechef.com/problems/KSIZEGCD
//but instead of a subarray of length i, it can be any i elements
//does this by finding the divisors of all the n numbers in log n time
//after finding these divisors, finds the highest divisor with at least frequency i
//this solution is able to be modified so that it can solve the problem by keep tracking of the current divisors
//solution would TLE using this approach :skull:
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e5 + 1;

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

void find_divs(map<int,int>::iterator i, int p, map<int,int> &cnts, unordered_map<int,int> &facts) {
    if(i == cnts.end()) {
        if(facts.find(p) == facts.end()) {
            facts[p] = 1;
        } else {
            facts[p]++;
        }
        return;
    }
    
    for(int j = 0; j < (*i).second + 1; j++) {
        find_divs(++i, p, cnts, facts);
        --i;
        p *= (*i).first;
    }
    
}

void solve() { 
    int n; cin >> n;
    
    unordered_map<int,int> facts;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        map<int,int> cnts;
        for(int j = 0; j < prime.size(); j++) {
            while(num % prime[j] == 0) {
                if(cnts.find(prime[j]) == cnts.end()) {
                    cnts[prime[j]] = 1;
                } else {
                    cnts[prime[j]]++;
                }
                num /= prime[j];
            }
        }
        if(num != 1) {
            cnts[num] = 1;
        }
        find_divs(cnts.begin(), 1, cnts, facts);
    }
    vector<pair<int,int>> v(0);
    for(auto x : facts) {
        v.push_back(x);
    }
    sort(v.begin(), v.end(), [](pair<int,int> &left, pair<int,int> &right) {
        if(left.second == right.second) {
            return left.first > right.first;
        } else {
            return left.second < right.second;
        }
    });
    
    // for(auto x : v) {
    //     cout << x.first << " " << x.second << "\n";
    // }
    int idx = 0;
    for(int i = 1; i <= n; i++) {
        while(v[idx].second < i) {
            idx++;
        }
        cout << v[idx].first << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    
    sieve(N);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
