#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

ll binexp(ll base, ll power, ll MOD = 1e9 + 7) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " | ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve(N);
    int n; cin >> n;
    vector<bool> visited(n+1);
    vector<pair<int,int>> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i].first;
        nums[i].second = i + 1;
    }
    sort(nums.begin(),nums.end());
    ll score = 0;
    int left = n;
    while(nums.size()) {
        // cout << "inf? " << nums.back() << "\n";
        if(visited[nums.back().second]) {nums.pop_back(); continue;}
        int next_num = nums.back().first;
        int cnt = 0;
        while(nums.size() && nums.back().first == next_num) {
            pair<int,int> next = nums.back(); nums.pop_back();
            // cout << "curr idx: " << next.second << "\n";

            map<int,int> cnts;
            int num = next.second;
            while(num != 1) {
                cnts[prime_factor[num]]++;
                num /= prime_factor[num];
            }
            // cnts[1]++;
            set<int> s;
            // s.insert(1);
            find_divs(cnts.begin(),1,cnts,s);
            // cout << s << "\n";
            for(int x : s) {
                // cout << "x: " << x << "\n";
                if(visited[x]) continue;
                int curr = x;
                while(curr <= next.second) {
                    if(!visited[curr]) {
                        // cout << "next: " << next << " found: " << curr << "\n";
                        visited[curr] = true;
                        cnt ++;
                        left--;
                    }
                    curr += next.second;
                }
            }
            if(!visited[1]) {
                // cout << "next: " << next << " found: " << 1 << "\n";
                visited[1] = true;
                cnt ++;
                left--;
            }
        }
        // score = (score + (binexp(2,cnt,MOD) - 1) * next_num) % MOD;
        // cout << "num ways to make: " << next_num << " is " << (binexp(2,cnt,MOD) - 1) % MOD * binexp(2,left,MOD) << "\n";
        // cout << "cnt: " << cnt << " left: " << left << "\n";
        score = (score + next_num * (binexp(2,cnt,MOD) - 1) % MOD * binexp(2,left,MOD)) % MOD;
    }
    cout << score << "\n";
    return 0;
}