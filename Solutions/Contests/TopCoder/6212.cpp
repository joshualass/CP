#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class BishopOnTheBoard {
public:
    int countReachableCells(int xSize, int ySize, int x, int y, int k) {

        int res = 1LL * xSize * ySize / 2;
        if((xSize & 1) && (ySize & 1) && ((x + y) % 2 == 0)) res++;

        auto rotate = [&]() -> void {
            int next_xSize = ySize; 
            int next_ySize = xSize;
            int next_x = ySize - 1 - y;
            int next_y = x;
            xSize = next_xSize;
            ySize = next_ySize;
            x = next_x;
            y = next_y;
        };

        auto go_down_left = [&](array<ll,2> a) -> array<ll,2> {
            int move = a[0];
            return {0, a[1] - move};
        };

        auto go_down_right = [&](array<ll,2> a) -> array<ll,2> {
            int move = xSize - a[0] - 1;
            return {xSize - 1, a[1] - move};
        };

        for(int rotation = 0; rotation < 4; rotation++) {

            array<ll,2> a = {x,y}, b = {x,y};
            for(int i = 0; i < k; i++) {
                if(i & 1) {
                    a = go_down_left(a);
                    b = go_down_right(b);
                } else {
                    a = go_down_right(a);
                    b = go_down_left(b);
                }
            }

            for(int i = 0; i < xSize; i++) {
                ll miny = min(a[1] + i, b[1] + (xSize - 1 - i));
                res -= max(0LL, miny / 2);
            }

            rotate();
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
  auto c = BishopOnTheBoard();
  int ret = c.countReachableCells(arg0, arg1, arg2, arg3, arg4);
  cout << ret;
}