#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class PeriodicTiling {
public:
    int minBlock(vector<string> part) {
        int r = part.size(), c = part[0].size();
        int sr = -1, sc = -1;
        for(int i = 1; i <= r; i++) {
            int ok = 1;
            for(int j = 0; j < r; j++) {
                for(int k = 0; k < c; k++) {
                    if(part[j][k] != part[(i+j)%r][k]) {
                        ok = 0;
                    }
                }
            }
            if(ok) {
                sr = i;
                break;
            }
        }

        for(int i = 1; i <= c; i++) {
            int ok = 1;
            for(int j = 0; j < r; j++) {
                for(int k = 0; k < c; k++) {
                    if(part[j][k] != part[j][(k+i)%c]) {
                        ok = 0;
                    }
                }
            }
            if(ok) {
                sc = i;
                break;
            }
        }
        // cout << "sr : " << sr << " sc : " << sc << '\n';

        int mul = 10;
        for(int i = 0; i < r * mul; i++) {
            for(int j = 0; j < mul; j++) {
                cout << part[i%r];
            }
            cout << '\n';
        }

        return sr * sc / gcd(sr,sc);
    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> arg0(n0);
  for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
  auto c = PeriodicTiling();
  int ret = c.minBlock(arg0);
  cout << ret;
}