#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;
class SlashPath {
public:
    vector<string> construct(int steps) {
        
        //impossible to complete in an even number of steps due to parity
        if(steps % 2 == 0 || steps == 1) return {};

        steps--;
        int r = min(49, steps / 2), c = min(50, steps / 2 + 1);
        if(r * 2 % 4 != steps % 4) {
            r--;
            c--;
        }

        vector<string> maze(r,string(c, '.'));

        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(j > i + 1) {
                    if((i + j) & 1) {
                        maze[i][j] = '\\';
                    } else {
                        maze[i][j] = '/';
                    }
                } else if(i > j) {
                    if((i + j) & 1) {
                        maze[i][j] = '/';
                    } else {
                        maze[i][j] = '\\';
                    }
                } else {
                    maze[i][j] = '\\';
                }
            }
        }

        steps -= r * 2;

        for(int i = 1; i < r - 1; i++) {
            for(int x = i, y = i + 1; x > 0 && y < c - 1; x--, y++) {
                if(steps) {
                    maze[x][y] = '/';
                    steps -= 4;
                }
            }
        }

        for(int i = 1; i < r - 1; i++) {
            for(int x = i, y = i; x < r - 1 && y > 0; x++, y--) {
                if(steps) {
                    maze[x][y] = '/';
                    steps -= 4;
                }
            }
        }

        return maze;

    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = SlashPath();
  vector<string> ret = c.construct(arg0);
  for (auto& item : ret) { cout << item << "\n"; }
}