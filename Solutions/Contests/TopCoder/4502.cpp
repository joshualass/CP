#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class CardCosts {
public:
    long long mincost(int n, int k) {
        ll res = 0;
        priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
        vector<ll> m;
        vector<int> a(n);
        auto add = [&](int idx) -> void {
            pq.push({m[idx] * (2 * a[idx] + 1), idx});
            a[idx]++;
        };
        for(int i = 0; i < n; i++) {
            if(i) {
                if(1e18 / k < m.back()) break;
                m.push_back(m.back()*k);
            } else {
                m.push_back(1);
            }
            add(i);
        }
        while(n--) {
            auto [cost, idx] = pq.top();
            pq.pop();
            res += cost;
            add(idx);
        }
        return res;
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg1;
  cin >> arg1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = CardCosts();
  long long ret = c.mincost(arg0, arg1);
  cout << ret;
}