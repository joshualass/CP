#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e5 + 1;

std::vector <int> prime;
int prime_factor[N];

void sieve (int n) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
            prime.push_back (i);
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve(N);
    
    int n, k; cin >> n >> k;
    ll cnt = 0;

    map<map<int,int>, int> m;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        map<int,int> add;
        while(prime_factor[num] != -1 || num != 1) {
            int factor = prime_factor[num];
            if(factor == -1) {
                factor = num;
            }
            num /= factor;
            // cout << "factor: " << factor << "\n";
            if(add.find(factor) == add.end()) {
                // add[factor] = 1;
                add.insert({factor,1});
            } else {
                add[factor]++;
            }
        }
        //get rid of unnecessary factors
        // cout << "make it here - 0: " << i << " map size: " << add.size() << "\n";
        vector<int> rem(0);
        for(auto &x : add) { //when you iterate through a map, you can't remove or add elements :))
            // cout << "x: " << x << "\n";
            x.second = x.second % k;
            if(x.second == 0) {
                // add.erase(x.first);
                rem.push_back(x.first);
            }
        }
        for(auto x : rem) {
            add.erase(x);
        }
        // cout << "make it here - 1: " << i << "\n";
        if(m.find(add) != m.end()) {
            cnt += m[add];
        };
        for(auto &x : add) {
            x.second = k - x.second;
        }
        // cout << "make it here - 3: " << i << "\n";
        if(m.find(add) == m.end()) {
            m[add] = 1;
        } else {
            m[add]++;
        }
    }
    cout << cnt << endl;
    return 0;
}