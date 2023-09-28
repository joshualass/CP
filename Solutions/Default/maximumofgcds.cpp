// https://www.codechef.com/problems/KSIZEGCD
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

void find_divs(unordered_map<int,int>::iterator i, int p, unordered_map<int,int> &cnts, unordered_set<int> &found) {
    if(i == cnts.end()) {
        found.insert(p);
        return;
    }
    unordered_map<int,int>::iterator next = i;
    next++;
    for(int j = 0; j < (*i).second + 1; j++) {
        find_divs(next, p, cnts, found);
        p *= (*i).first;
    }
    
}

void solve() { 
    int n; cin >> n;
    unordered_map<int,int> cons; //stores the divisor, as well as how many times it's occurred
    vector<int> ans(n+1);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        unordered_map<int,int> cnts;
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
        unordered_set<int> found;
        find_divs(cnts.begin(), 1, cnts, found);
        vector<int> removes(0);
        for(int x : found) {
            if(cons.find(x) == cons.end()) {
                cons[x] = 1;
            } else {
                cons[x]++;
            }
            ans[cons[x]] = max(ans[cons[x]],x);
        }
        for(pair<int,int> x : cons) {
            if(found.find(x.first) == found.end()) {
                removes.push_back(x.first);
            }
        }
        for(int x : removes) cons.erase(x);
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
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
