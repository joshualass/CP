#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

class FindingKids {
public:
    long long getSum(int n, int q, int A, int B, int C) {
        long long M = 1e9 + 7;
        vector<long long> rights, lefts;
        map<int,int> m;
        for(long long i = 0; i < n; i++) {
            A = (1LL * A * B + C) % M;
            long long p = A % (M - n + i + 1);
            if(m.count(p)) p = M - n + i;
            m[p] = i;
            if(p & 1) {
                lefts.push_back(p);
            } else {
                rights.push_back(p);
            }
        }

        vector<int> order(n);
        int p = 0;
        for(auto [pos, id] : m) {
            order[id] = p++;
        }

        sort(lefts.begin(), lefts.end());
        sort(rights.begin(), rights.end());
        long long res = 0;
        for(long long i = 0; i < q; i++) {
            A = (1LL * A * B + C) % M;
            long long kid = A % n;
            A = (1LL * A * B + C) % M;
            long long time = A;

            kid = order[kid];
            long long l = -M, r = M * 2;
            while(l != r) {
                long long m;
                if((l + r) & 1) {
                    m = (l + r - 1) / 2;
                } else {
                    m = (l + r) / 2;
                }
                long long lpos = m + time, rpos = m - time;
                long long ll = -1, rl = lefts.size() ? lefts.size() - 1 : -1;
                long long lr = -1, rr = rights.size() ? rights.size() - 1 : -1;
                while(ll != rl) {
                    long long m = (ll + rl + 1) / 2;
                    if(lefts[m] <= lpos) {
                        ll = m;
                    } else {
                        rl = m - 1;
                    }
                }
                while(lr != rr) {
                    long long m = (lr + rr + 1) / 2;
                    if(rights[m] <= rpos) {
                        lr = m;
                    } else {
                        rr = m - 1;
                    }
                }

                long long cntleq = ll + 1 + lr + 1;

                if(cntleq >= kid + 1) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }

            res += abs(l);
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
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg3;
  cin >> arg3;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg4;
  cin >> arg4;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = FindingKids();
  long long ret = c.getSum(arg0, arg1, arg2, arg3, arg4);
  cout << ret;
}