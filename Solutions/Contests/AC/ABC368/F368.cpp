#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();

    vector<int> grundys(100001);

    for(int i = 1; i <= 100000; i++) {

        vector<int> div;
        find_divisors(i,div);

        sort(div.begin(), div.end(), [&](const int &lhs, const int &rhs) {
            return grundys[lhs] < grundys[rhs];
        });

        int mex = 0;
        for(int x : div) {
            if(x != i && grundys[x] == mex) {
                mex++;
            }
        }
        grundys[i] = mex;
    }

    int n; cin >> n;
    int g = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        g ^= grundys[num];
    }

    cout << (g == 0 ? "Bruno" : "Anna") << '\n';


    return 0;
}