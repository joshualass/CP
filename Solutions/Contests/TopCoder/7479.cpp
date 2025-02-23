#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

class Alarmed {
public:
    vector<int> dsu, sizes;

    void dsubuild(int n) {
        dsu.clear();
        sizes.clear();
        for(int i = 0; i < n; i++) {
            dsu.push_back(i);
            sizes.push_back(1);
        }
    }

    int find(int x) {
        if(dsu[x] == x) {
            return x;
        }
        dsu[x] = find(dsu[x]);
        return dsu[x];
    }

    void merge(int x, int y) {
        // cout << "merge x : " << x << " y : " << y << '\n';
        x = find(x);
        y = find(y);
        if(x == y) {
            return;
        }
        if(sizes[x] == sizes[y]) {
            dsu[y] = x;
            sizes[x] += sizes[y];
        } else {
            dsu[y] = x;
            sizes[x] += sizes[y];
        }
    }


    double noise(vector<int> x, vector<int> y, vector<int> threshold) {

        int n = x.size();
        
        auto get_dist = [](ld x1, ld y1, ld x2, ld y2) -> ld {
            return sqrtl((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        };

        ld lo = 0, hi = 100000000;
        while(hi - lo > 1e-10) {
            ld m = (hi + lo) / 2;

            dsubuild(n + 2);

            for(int i = 0; i < n; i++) {
                ld r = sqrtl(m / threshold[i]);
                //check if it touches any left segments
                bool fl = 0, fr = 0;
                int ax = x[i], ay = y[i];
                if(ax <= r) fl = 1;
                if(ax > 50) {
                    if(get_dist(ax,ay,50,0) <= r) fl = 1;
                    if(get_dist(ax,ay,50,100) <= r) fl = 1;
                } else {
                    if(ay <= r) fl = 1;
                    if(100 - ay <= r) fl = 1;
                }
                //check right segments
                if(100 - ax <= r) fr = 1;
                if(ax < 50) {
                    if(get_dist(ax,ay,50,0) <= r) fr = 1;
                    if(get_dist(ax,ay,50,100) <= r) fr = 1;
                } else {
                    if(ay <= r) fr = 1;
                    if(100 - ay <= r) fr = 1;
                }

                if(fl) merge(i,n);
                if(fr) merge(i,n+1);

                for(int j = 0; j < n; j++) {
                    ld rj = sqrtl(m / threshold[j]);        
                    if(get_dist(ax,ay,x[j],y[j]) <= r + rj) {
                        merge(i,j);
                    }
                }
            }

            if(find(n) != find(n+1)) {
                lo = m;
            } else {
                hi = m;
            }
        }

        return lo;

    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  vector<int> arg0(n0);
  for (int i=0;i<n0;++i) { cin >> arg0[i]; }
  int n1; cin >> n1;
  vector<int> arg1(n1);
  for (int i=0;i<n1;++i) { cin >> arg1[i]; }
  int n2; cin >> n2;
  vector<int> arg2(n2);
  for (int i=0;i<n2;++i) { cin >> arg2[i]; }
  auto c = Alarmed();
  double ret = c.noise(arg0, arg1, arg2);
  cout << setprecision(numeric_limits<double>::max_digits10) << ret;
}