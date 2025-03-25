#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

class PolyominoCut {
public:
    int count(int k, int width, int height) {
        
        set<vector<array<int,2>>> polys;

        auto dfs = [&](auto self, vector<array<int,2>> a) -> void {
            sort(a.begin(), a.end());
            if(polys.count(a)) return;
            polys.insert(a);
            if(a.size() == k) return;

            vector<int> dx = {0,0,-1,1}, dy = {-1,1,0,0};

            for(int i = 0; i < a.size(); i++) {
                for(int j = 0; j < 4; j++) {
                    array<int,2> nx = {a[i][0] + dx[j], a[i][1] + dy[j]};
                    int in_poly = 0;
                    for(int l = 0; l < a.size(); l++) {
                        if(nx == a[l]) in_poly = 1;
                    }
                    if(!in_poly) {
                        vector<array<int,2>> next_poly = a;
                        next_poly.push_back(nx);
                        int mx = min(nx[0], 0), my = min(nx[1], 0);
                        for(int l = 0; l < next_poly.size(); l++) {
                            next_poly[l][0] -= mx;
                            next_poly[l][1] -= my;
                        }
                        // cout << "next poly : " << next_poly << '\n';
                        self(self, next_poly);
                    }
                }
            }

        };

        dfs(dfs, {{0,0}});

        // cout << "poly cnt : " << polys.size() << '\n';

        int res = 0;

        auto isGapH = [](set<array<int,2>> a, int h) -> int {
            int c = 0, t = 0;
            for(int i = 0; i < 8; i++) {
                if(a.count({i, h}) != t) {
                    t ^= 1;
                    c++;
                }
            }
            return c >= 3;
        };

        auto isGapW = [](set<array<int,2>> a, int w) -> int {
            int c = 0, t = 0;
            for(int i = 0; i < 8; i++) {
                if(a.count({w, i}) != t) {
                    t ^= 1;
                    c++;
                }
            }
            return c >= 3;
        };

        for(vector<array<int,2>> poly : polys) {
            if(poly.size() == k) {
                cout << "poly : " << poly << '\n';
                int w = 0, h = 0;
                for(int i = 0; i < k; i++) {
                    w = max(w, poly[i][0]);
                    h = max(h, poly[i][1]);
                }

                cout << "w : " << w << " h : " << h << '\n';

                if(w > width) continue;
                if(h > height) continue;

                set<array<int,2>> s(poly.begin(), poly.end());
                assert(s.size() == k);

                //check if this polyomino disconnects everywhere
                int circle_in = 0;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        if(s.count({i + 0, j + 1}) && s.count({i + 1, j + 0}) && s.count({i + 1, j + 2}) && s.count({i + 2, j + 1}) && s.count({i + 1, j + 1}) == 0) {
                            circle_in = 1;
                        }
                    }
                }

                if(circle_in) continue;
                
                int dis_bottom = isGapH(s, 0);
                int dis_top = isGapH(s, h);
                int dis_left = isGapW(s, 0);
                int dis_right = isGapW(s, w);

                int bad_bl = s.count({0,0}) == 0;
                int bad_br = s.count({w, 0}) == 0;
                int bad_ul = s.count({0, h}) == 0;  
                int bad_ur = s.count({w, h}) == 0;

                int add = (width - w) * (height - h);

                if(w == width && h == height) {
                    if(dis_bottom || dis_top || dis_left || dis_right || bad_bl || bad_br || bad_ul || bad_ur) {
                        add = 0;
                    }
                } else if(w == width) {
                    if(dis_left || dis_right) {
                        add -= max(0, h);
                    }
                    if(dis_left || dis_right || bad_bl || bad_br || dis_bottom) {
                        add--;
                    }
                    if(dis_left || dis_right || bad_ul || bad_ur || dis_top) {
                        add--;
                    }
                } else if(h == height) {
                    if(dis_top || dis_bottom) {
                        add -= max(0, w);
                    }
                    if(dis_top || dis_bottom || dis_left || bad_bl || bad_ul) {
                        add--;
                    }
                    if(dis_top || dis_bottom || dis_right || bad_br || bad_ur) {
                        add--;
                    }
                } else {
                    if(dis_bottom) {
                        add -= max(0, width - 1);
                    }
                    if(dis_top) {
                        add -= max(0, width - 1);
                    }
                    if(dis_left) {
                        add -= max(0, height - 1);
                    }
                    if(dis_right) {
                        add -= max(0, height - 1);
                    }
                    if(bad_bl || dis_bottom || dis_left) {
                        add--;
                    }
                    if(bad_br || dis_bottom || dis_right) {
                        add--;
                    }
                    if(bad_ul || dis_left || dis_top) {
                        add--;
                    }
                    if(bad_ur || dis_right || dis_top) {
                        add--;
                    }
                }

                cout << "add : " << add << '\n';


                res += add;

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
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = PolyominoCut();
  int ret = c.count(arg0, arg1, arg2);
  cout << ret;
}