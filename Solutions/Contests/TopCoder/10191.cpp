#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
class SettingTents {
public:
    int countSites(int N, int M) {
        int res = 0;
        auto get_corner = [](int x, int y, int xm, int ym) -> array<int,2> {
            return {x-xm, y-ym};
        };
        for(int i = 1; i <= N; i++) {
            for(int j = 0; j <= M; j++) {
                if(((i + j) & 1) == 0) {
                    int xm = (i + j) / 2;
                    int ym = i - xm;
                    int g = gcd(i,j);
                    int tx = xm, ty = ym;   
                    int xd = i / g, yd = -j / g;
                    while(tx > j / 2) {
                        auto [x2,y2] = get_corner(j,i,tx,ty);
                        int mdx = max(j, tx-x2), mdy = max(i, y2-ty);
                        int add = 0;
                        if(mdx <= M && mdy <= N) {
                            add = (M - mdx + 1) * (N - mdy + 1);
                        }
                        res += add;
                        tx -= xd;
                        ty -= yd;
                    }
                    tx = xm + xd;
                    ty = ym + yd;
                    while(1) {
                        auto [x2,y2] = get_corner(j,i,tx,ty);
                        int mdx = max(j, tx-x2), mdy = max(i, y2-ty);
                        int add = 0;
                        if(mdx <= M && mdy <= N) {
                            add = (M - mdx + 1) * (N - mdy + 1);
                        } else {
                            break;
                        }
                        // cout << "l1 - i : " << i << " j : " << j << " tx : " << tx << " ty : " << ty << " add : " << add << '\n';
                        res += add;
                        tx += xd;
                        ty += yd;
                    }
                }
            }
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
  auto c = SettingTents();
  int ret = c.countSites(arg0, arg1);
  cout << ret;
}