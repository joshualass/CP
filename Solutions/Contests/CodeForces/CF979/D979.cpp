#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
same strategy, but avoid constant factor from using an unordered map and use more memory. 
Also, implement a faster Trie
*/

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const int N = 1e5 + 1;

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

struct Trie {
    const int depth = 31;
    struct Node {
        array<int,2> a;
        int cnt;
        int min;
        Node() {
            a = {-1,-1};
            cnt = 0;
            min = INT_MAX;
        }
    };
    vector<Node> nodes;

    Trie () {
        nodes.push_back(Node());
    }

    void insert(int num) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] == -1) {
                nodes[curr].a[bit] = nodes.size();
                nodes.push_back(Node());
            }
            curr = nodes[curr].a[bit];
            nodes[curr].cnt++;
            nodes[curr].min = min(nodes[curr].min, num);
        }
    }

    int query(int x, int k, int s) {
        int res = 0;
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = (((x >> i) & 1) ^ 1);
            if(nodes[curr].a[bit] != -1 && nodes[nodes[curr].a[bit]].cnt > 0 && nodes[nodes[curr].a[bit]].min <= s - x) {
                res += (1 << i);
                curr = nodes[curr].a[bit];
            } else if(nodes[curr].a[bit ^ 1] != -1 && nodes[nodes[curr].a[bit ^ 1]].cnt > 0 && nodes[nodes[curr].a[bit ^ 1]].min <= s - x) {
                curr = nodes[curr].a[bit ^ 1];
            } else {

                return -1;
            }
        }
        return res;
    }

    bool find(int num) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] != -1) {
                curr = nodes[curr].a[bit];
            } else {
                return 0;
            }
        }
        return 1;
    }

    bool erase(int num) {
        if(find(num)) {
            int curr = 0;
            for(int i = depth - 1; i >= 0; i--) {
                curr = nodes[curr].a[((num >> i) & 1)];
                nodes[curr].cnt--;
            }
            return 1;
        } else {
            return 0;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    vector<Trie> roots(N);
    vector<bool> vis(N);
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int u; cin >> u;
            if(vis[u] == 0) {
                vis[u] = 1;
                vector<int> divs;
                find_divisors(u,divs);
                for(int x : divs) {
                    roots[x].insert(u);
                }
            }
        } else {
            int x, k, s; cin >> x >> k >> s;
            int res = -1;
            if(x % k == 0) {
                res = roots[k].query(x,k,s);
            }
            if(res == -1) {
                cout << res << '\n';
            } else {
                cout << (res ^ x) << '\n';
            }
        }
    }

    cerr << "ok\n";
    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

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

// void find_divs(int idx, int p, vector<pair<int,int>> &facts, vector<int> &nums) {
//     if(idx == facts.size()) {
//         nums.push_back(p);
//         return;
//     }
//     for(int j = 0; j < facts[idx].second + 1; j++) {
//         find_divs(idx + 1, p, facts, nums);
//         p *= facts[idx].first;
//     }
// }

// //O(sqrt(n)), approx. cuberoot(n) factors. 
// void find_divisors(int num, vector<int> &nums) {
//     // map<int,int> factors;
//     vector<pair<int,int>> factors;
//     // cout << "num: " << num << " ";
//     for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
//         bool first = 1;
//         while(num % prime[i] == 0) {
//             if(first) {
//                 factors.push_back({prime[i],1});
//                 first = 0;
//             } else {
//                 factors.back().second++;
//             }
//             num /= prime[i];
//         }
//     }
//     if(num != 1) {
//         factors.push_back({num,1});
//     }
//     // cout << factors << "\n";
//     find_divs(0, 1, factors, nums);
// }

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// struct chash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
// template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
// template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

// const int depth = 31;

// struct Trie {
//     int cnt;
//     Trie* arr[2];
//     Trie() {
//         cnt = 0;
//         arr[0] = nullptr;
//         arr[1] = nullptr;
//     }
//     pb_map<int,int> m;
// };

// void insert(int num, vector<int> &divs, Trie* root) {
//     Trie* curr = root;
//     for(int d = depth - 1; d >= 0; d--) {
//         int bit = (num >> d) & 1;
//         if(curr->arr[bit] == nullptr) {
//             curr->arr[bit] = new Trie();
//         }
//         curr = curr->arr[bit];
//         curr->cnt++;
//         // for(int x : divs) {
//         //     if(curr->m.find(x) == curr->m.end()) {
//         //         curr->m[x] = num;
//         //     } else {
//         //         curr->m[x] = min(num,curr->m[x]);
//         //     }
//         // }
//     }
// }

// int query(int x, int k, int s, Trie* root) { //queries the maximum xor value (what else are you going to use a binary trie for lol)
//     Trie* curr = root;
//     int ans = 0;
//     for(int d = depth - 1; d >= 0; d--) {
//         int bit = (x >> d) & 1;
//         if(curr->arr[bit ^ 1] && curr->arr[bit ^ 1]->m.find(k) != curr->arr[bit ^ 1]->m.end() && curr->arr[bit ^ 1]->m[k] <= s - x) {
//             curr = curr->arr[bit^1];
//             ans += 1 << d;
//         } else if(curr->arr[bit] && curr->arr[bit]->m.find(k) != curr->arr[bit]->m.end() && curr->arr[bit]->m[k] <= s - x)  {
//             curr = curr->arr[bit];
//         } else {
//             return -1;
//         }
//     }
//     return ans;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     freopen("D.in","r",stdin);
//     // freopen(".out","w",stdout);

//     clock_t tStart = clock();

//     sieve();
//     int q; cin >> q;
//     Trie* root = new Trie();
//     for(int i = 0; i < q; i++) {
//         int t; cin >> t;
//         if(t == 1) {
//             int u; cin >> u;
//             vector<int> divs;
//             find_divisors(u,divs);
//             insert(u,divs,root);
//         } else {
//             int x, k, s; cin >> x >> k >> s;
//             int res = -1;
//             if(x % k == 0) {
//                 res = query(x, k, s, root);
//             }
//             if(res != -1) {
//                 cout << (res ^ x) << '\n';
//             } else {
//                 cout << res << '\n';
//             }
//         }
//     }

//     printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

//     return 0;
// }