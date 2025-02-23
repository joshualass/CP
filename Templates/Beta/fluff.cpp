#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class Posters {
public:
    int maxCover(int width, int height, vector<int> pWidth, vector<int> pHeight) {

        int res = 0;
        int n = pWidth.size();
        int c = 0;

        auto get_area = [&](vector<array<int,2>> a) {
            int area = 0;
            c++;
            for(int i = 1; i < 1 << n; i++) {
                int lox = 100, loy = 100, hix = 0, hiy = 0;
                for(int j = 0; j < n; j++) {
                    if((i >> j) & 1) {
                        lox = min(lox, a[j][0] + pWidth[j]);
                        loy = min(loy, a[j][1] + pHeight[j]);
                        hix = max(hix, a[j][0]);
                        hiy = max(hiy, a[j][1]);
                    }
                }
                if(hix < lox && hiy < loy) {
                    if(__builtin_popcount(i) & 1) {
                        area += (lox - hix) * (loy - hiy);
                    } else {
                        area -= (lox - hix) * (loy - hiy);
                    }
                }
            }
            res = max(res,area);
        };

        array<int,2> b = {-1,-1};

        vector<array<int,2>> a(n,b);
        array<vector<array<int,2>>,4> poss;
        set<pair<vector<array<int,2>>,array<vector<array<int,2>>,4>>> vis;

        auto dfs = [&](auto self, vector<array<int,2>> a, array<vector<array<int,2>>,4> poss) -> void {
            if(vis.count(make_pair(a,poss))) return;
            vis.insert({a,poss});
            if(count(a.begin(),a.end(),b) == 0) {
                get_area(a);
                return;
            }
            for(int i = 0; i < n; i++) {
                if(a[i] == b) {
                    for(int j = 0; j < 4; j++) {
                        for(auto [px, py] : poss[j]) {
                            int tx = px, ty = py;
                            if(j == 2) {
                                ty -= a[i][1];
                            } else if(j == 3) {
                                tx -= a[i][0];
                            }
                            tx += max(0,-tx);
                            ty += max(0,-ty);
                            tx -= max(0,tx+pWidth[i] - width);
                            ty -= max(0,ty+pHeight[i] - height);

                            a[i] = {tx,ty};
                            poss[0].push_back({tx,ty+pHeight[i]});
                            poss[1].push_back({tx+pWidth[i],ty});
                            poss[2].push_back({tx,ty});

                            self(self, a, poss);
                            a[i] = {-1,-1};
                            for(int k = 0; k < 3; k++) poss[k].pop_back();
                        }
                    }
                }
            }
        };
        poss[0].push_back({0,0});
        poss[3].push_back({width,height});
        dfs(dfs, a, poss);
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
  int n2; cin >> n2;
  vector<int> arg2(n2);
  for (int i=0;i<n2;++i) { cin >> arg2[i]; }
  int n3; cin >> n3;
  vector<int> arg3(n3);
  for (int i=0;i<n3;++i) { cin >> arg3[i]; }
  auto c = Posters();
  int ret = c.maxCover(arg0, arg1, arg2, arg3);
  cout << ret;
}