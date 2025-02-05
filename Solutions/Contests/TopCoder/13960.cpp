#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;



// SOLUTION_BEGIN
class LuckyXor {
public:
    int construct(int a) {
        auto is_lucky = [](int x) -> bool {
            while(x) {
                if(x % 10 == 4 || x % 10 == 7) {
                    x /= 10;
                } else {
                    return 0;
                }
            }
            return 1;
        };
        for(int b = a + 1; b <= 100; b++) {
            if(is_lucky(a^b)) return b;
        }
        return -1;
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = LuckyXor();
  int ret = c.construct(arg0);
  cout << ret;
}