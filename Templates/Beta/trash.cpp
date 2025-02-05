#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class RandomSelection {
public:
    double expectedMaximum(int n, int T, int seed, int Amod, vector<int> Aprefix) {
        map<ll,ll> m;
        ld prod = 1;
        ll zc = 0;
        for(int i = 0; i < Aprefix.size(); i++) {
            if(Aprefix[i]) {
                m[Aprefix[i]]++;
                prod *= Aprefix[i];
            } else {
                zc++;
            }
        }
        ll state = seed;
        for(int i = Aprefix.size(); i < n; i++) {
            state = (1103515245 * state + 12345) & ((1LL << 31) - 1);
            int num = (T + state) % Amod;
            if(num) {
                m[num]++;
                prod *= num;
            } else {
                zc++;
            }
        }

        ll cnt = n - zc;
        ll L = 0;
        ld ev = 0;
        for(auto [R, x] : m) {
            ld contrib = 1 / prod * cnt / (cnt + 1) * (powl(R,cnt+1)-powl(L,cnt+1));
            ev += contrib;
            cnt -= x;
            prod /= powl(R,x);
            L = R;
        }
        return ev;
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
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg3;
  cin >> arg3;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n4; cin >> n4;
  vector<int> arg4(n4);
  for (int i=0;i<n4;++i) { cin >> arg4[i]; }
  auto c = RandomSelection();
  double ret = c.expectedMaximum(arg0, arg1, arg2, arg3, arg4);
  cout << setprecision(numeric_limits<double>::max_digits10) << ret;
}