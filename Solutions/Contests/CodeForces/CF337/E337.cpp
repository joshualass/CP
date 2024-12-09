// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <map>
// #include <set>

// using namespace std;

// bool is_prime(long long n) {
//     if (n <= 1) return false;
//     for (long long i = 2; i * i <= n; ++i) {
//         if (n % i == 0) return false;
//     }
//     return true;
// }

// int solve(int idx, map<long long, int>& counts, int nodes, vector<long long>& a) {
//     if (idx == a.size()) {
//         return nodes;
//     }

//     int min_nodes = 1e9;

//     if (is_prime(a[idx])) {
//         if (counts.find(a[idx]) == counts.end() || counts[a[idx]] == 0) {
//            nodes++;
//         }
//         map<long long, int> next_counts = counts;
//         if (next_counts.find(a[idx]) != next_counts.end()) {
//             next_counts[a[idx]]--;
//              if (next_counts[a[idx]] == 0) {
//                 next_counts.erase(a[idx]);
//              }
//         }
        
//         min_nodes = min(min_nodes, solve(idx + 1, next_counts, nodes, a));
//          if(counts.find(a[idx]) == counts.end() || counts[a[idx]] == 0) nodes--;

//     } else {
//          for (auto it = counts.begin(); it != counts.end(); ++it) {
//             if (it->second > 0 && it->first % a[idx] == 0) {
//                 map<long long, int> next_counts = counts;
//                 next_counts[it->first]--;
//                 if (next_counts[it->first] == 0) {
//                     next_counts.erase(it->first);
//                 }

//                 long long next_val = it->first / a[idx];
//                 if (next_counts.find(next_val) == next_counts.end()) {
//                     nodes++;
//                 }
//                 next_counts[next_val]++;

//                 if (next_counts.find(a[idx]) != next_counts.end() && next_counts[a[idx]] > 0) {
//                     next_counts[a[idx]]--;
//                     if (next_counts[a[idx]] == 0) {
//                         next_counts.erase(a[idx]);
//                     }
//                 }
//                 min_nodes = min(min_nodes, solve(idx + 1, next_counts, nodes, a));
//                 nodes--; 
//             }
//         }

//         map<long long, int> next_counts = counts;
//         if (next_counts.find(a[idx]) != next_counts.end() && next_counts[a[idx]] > 0) {
//             next_counts[a[idx]]--;
//             if (next_counts[a[idx]] == 0) {
//                 next_counts.erase(a[idx]);
//             }
//         } else {
//             nodes++;
//         }
//         min_nodes = min(min_nodes, solve(idx + 1, next_counts, nodes, a));
        
//     }


//     return min_nodes;
// }

// int main() {
//     int n;
//     cin >> n;
//     vector<long long> a(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> a[i];
//     }
//     sort(a.rbegin(), a.rend());

//     map<long long, int> counts;
//     for (long long x : a) {
//         counts[x]++;
//     }

//     cout << solve(0, counts, 0, a) << endl;

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template <typename T, typename D>
// std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
//     os << '(' << p.first << ", " << p.second << ") ";
//     return os;
// }

// template<typename T, typename D>
// std::ostream& operator<<(std::ostream& os, map<T,D> m) {
//     for(auto &x: m) os << x.first << " " << x.second << " | ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// /*
// *************************************
// need to build sieve --> sieve() 
// *************************************
// */
// const int N = 1e6 + 1;

// int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
// vector <int> prime;

// void sieve (int n = N) {
// 	std::fill (prime_factor, prime_factor + n, -1);
// 	for (int i = 2; i < n; ++i) {
// 		if (prime_factor[i] == -1) {
// 		    prime.push_back(i);
//             prime_factor[i] = i;
//         }
// 		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
// 			prime_factor[i * prime[j]] = prime[j];
// 			if (i % prime[j] == 0) break;
// 		}
// 	}
// }

// void find_divs(int idx, int p, vector<pair<ll,int>> &facts, vector<int> &nums) {
//     if(idx == facts.size()) {
//         nums.push_back(p);
//         return;
//     }
//     for(int j = 0; j < facts[idx].second + 1; j++) {
//         find_divs(idx + 1, p, facts, nums);
//         p *= facts[idx].first;
//     }
// }

// void prime_factorize(ll num, vector<pair<ll,int>> &prime_factors) {
//     for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
//         if(num % prime[i] == 0) {
//             prime_factors.push_back({prime[i],0});
//             while(num % prime[i] == 0) {
//                 prime_factors.back().second++;
//                 num /= prime[i];
//             }
//         }
//         while(num < N && num != 1) {
//             int t = prime_factor[num];
//             prime_factors.push_back({t, 0});
//             while(num % t == 0) {
//                 prime_factors.back().second++;
//                 num /= t;
//             }
//         }
//     }
//     if(num != 1) {
//         prime_factors.push_back({num,1});
//     }
// }

// //O(sqrt(n)), approx. cuberoot(n) factors. 
// void find_divisors(int num, vector<int> &nums) {
//     vector<pair<ll,int>> prime_factors;
//     prime_factorize(num, prime_factors);
//     find_divs(0, 1, prime_factors, nums);
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     sieve();
//     int n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;
//     sort(a.rbegin(), a.rend());
//     vector<map<ll,int>> prime_factors(n);
//     vector<int> primo(n);

//     for(int i = 0; i < n; i++) {
//         vector<pair<ll,int>> pf;
//         prime_factorize(a[i], pf);
//         map<ll,int> m(pf.begin(), pf.end());
//         prime_factors[i] = m;
//         primo[i] = pf == vector<pair<ll,int>>{{a[i],1}};
//     }

//     // cout << "primo : " << primo << '\n';

//     int res = N;

//     auto dfs = [&](auto self, vector<map<ll,int>> &in_tree, vector<int> parents, int i, int cnt, int roots) -> void {
//         // cout << "i : " << i << " parents : " << parents << " cnt : " << cnt << '\n';
//         if(i == n) {
//             res = min(res, cnt);
//             return;
//         }
//         int pfs = 1 - primo[i] + (roots == 1);
//         // cout << "i : " << i << " tree size : " << in_tree.size() << " pfs : " << pfs << '\n';
//         in_tree.push_back(prime_factors[i]);
//         for(auto [pf, f] : prime_factors[i]) pfs += f;
//         parents.push_back(-1);
//         self(self, in_tree, parents, i + 1, cnt + pfs, roots + 1);
//         in_tree.pop_back();
//         parents.pop_back();
//         for(int j = 0; j < in_tree.size(); j++) {
//             map<ll,int> t = in_tree[j];
//             int ok = 1;
//             for(auto [pf, f] : prime_factors[i]) {
//                 t[pf] -= f;
//                 if(t[pf] < 0) {
//                     ok = 0;
//                 }
//             }
//             if(ok) {
//                 swap(in_tree[j], t);
//                 in_tree.push_back(prime_factors[i]);
//                 parents.push_back(j);
//                 self(self, in_tree, parents, i + 1, cnt + 1 - primo[i], roots);
//                 in_tree.pop_back();
//                 parents.pop_back();
//                 swap(in_tree[j], t);
//             }
//         }
//     };

//     vector<map<ll,int>> in_tree;
//     vector<int> parents;
//     dfs(dfs, in_tree, parents, 0, 0, 0);

//     cout << res << '\n';

//     return 0;
// }