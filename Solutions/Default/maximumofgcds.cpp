// https://www.codechef.com/problems/KSIZEGCD
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// const int N = 1e5 + 1;

// int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
// vector <int> prime;

// void sieve (int n) {
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

// void find_divs(unordered_map<int,int>::iterator i, int p, unordered_map<int,int> &cnts, unordered_set<int> &found) {
//     if(i == cnts.end()) {
//         found.insert(p);
//         return;
//     }
//     unordered_map<int,int>::iterator next = i;
//     next++;
//     for(int j = 0; j < (*i).second + 1; j++) {
//         find_divs(next, p, cnts, found);
//         p *= (*i).first;
//     }
    
// }

// void solve() { 
//     int n; cin >> n;
//     unordered_map<int,int> cons; //stores the divisor, as well as how many times it's occurred
//     vector<int> ans(n+1);
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         unordered_map<int,int> cnts;
//         for(int j = 0; j < prime.size(); j++) {
//             while(num % prime[j] == 0) {
//                 if(cnts.find(prime[j]) == cnts.end()) {
//                     cnts[prime[j]] = 1;
//                 } else {
//                     cnts[prime[j]]++;
//                 }
//                 num /= prime[j];
//             }
//         }
//         if(num != 1) {
//             cnts[num] = 1;
//         }
//         unordered_set<int> found;
//         find_divs(cnts.begin(), 1, cnts, found);
//         vector<int> removes(0);
//         for(int x : found) {
//             if(cons.find(x) == cons.end()) {
//                 cons[x] = 1;
//             } else {
//                 cons[x]++;
//             }
//             ans[cons[x]] = max(ans[cons[x]],x);
//         }
//         for(pair<int,int> x : cons) {
//             if(found.find(x.first) == found.end()) {
//                 removes.push_back(x.first);
//             }
//         }
//         for(int x : removes) cons.erase(x);
//     }
//     for(int i = 1; i <= n; i++) {
//         cout << ans[i] << " ";
//     }
//     cout << "\n";
// }

// int main() {
//     ios_base::sync_with_stdio(false);cin.tie(NULL);
    
//     sieve(N);
//     int casi; cin >> casi;
//     while(casi-->0) solve();
//     return 0;
// }

//try again using stack approach :)
//stacks are good at finding answers for maximum value of length of all subarrays problem
//stacks do not work here. runtime has higher upperbound than expected could still work though
//goon L
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template <typename T, typename D>
// std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
//     os << '(' << p.first << ", " << p.second << ") ";
//     return os;
// }

// template <typename T>
// void printS(stack<T> x) {
//     cout << "stack: ";
//     while(x.size()) {
//         cout << x.top() << ' ';
//         x.pop();
//     }
//     cout << "\n";
// }

// void solve() {
//     int n; cin >> n;
//     vector<int> maxes(n);
//     stack<pair<int,int>> s;
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         //first let's update all nums so that they are divisible by the current num
//         int g = num;
//         int idx = -1;
//         while(s.size() && gcd(s.top().first, g) != s.top().first) {
//             maxes[i - 1 - s.top().second] = max(maxes[i - 1 - s.top().second], s.top().first); //update maxes 
//             idx = s.top().second;
//             g = gcd(s.top().first, g);
//             s.pop();
//         }
//         if(idx != -1) {
//             s.push({g, idx});
//         }
//         if(s.empty() || s.top().first != num) {
//             s.push({num,i});
//         }
//         cout << "after i : " << i << " s : ";
//         printS(s);
//     }
//     while(s.size()) {
//         maxes[n - 1 - s.top().second] = max(maxes[n - 1 - s.top().second], s.top().first);
//         s.pop();
//     }
//     for(int i = n - 2; i >= 0; i--) {
//         maxes[i] = max(maxes[i], maxes[i+1]);
//     }
//     for(int i = 0; i < n; i++) {
//         cout << maxes[i] << " \n"[i == n - 1];
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

//trial 3 :)
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> maxes(n);
    vector<pair<int,int>> gcds;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        vector<pair<int,int>> upds;
        gcds.push_back({num,i});
        for(int j = gcds.size() - 1; j >= 0; j--) {
            if(upds.empty()) {
                upds.push_back({gcd(gcds[j].first,num),gcds[j].second});
            } else if(gcd(gcds[j].first, num) != upds.back().first) {
                upds.push_back({gcd(gcds[j].first,num),gcds[j].second});
            } else {
                upds.back().second = gcds[j].second;
            }
        }
        reverse(upds.begin(), upds.end());
        swap(gcds, upds);
        for(pair<int,int> &p : gcds) {
            int idx = p.second;
            maxes[i - idx] = max(maxes[i - idx], p.first);
        }
    }
    for(int i = n - 2; i >= 0; i--) {
        maxes[i] = max(maxes[i], maxes[i+1]);
    }
    for(int i = 0; i < n; i++) {
        cout << maxes[i] << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}