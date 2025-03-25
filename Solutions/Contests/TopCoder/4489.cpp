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

        auto isconnected = [](vector<array<int,2>> poly, array<int,2> offset, array<int,2> dims) -> bool {
            vector<vector<int>> board(dims[0], vector<int>(dims[1]));
            for(array<int,2> b : poly) {
                board[b[0]][b[1]] = 1;
            }
            int sw = -1, sh = -1;
            for(int i = 0; i < dims[0]; i++) {
                for(int j = 0; j < dims[1]; j++) {
                    if(board[i][j] == 0) {
                        sw = i;
                        sh = j;
                    }
                }
            }
            if(sw == -1 && sh == -1) return 1; //board is completely filled by poly

            vector<int> dx = {-1,1,0,0}, dy = {0,0,-1,1};

            int sz = 0;
            queue<array<int,2>> q;
            q.push({sw, sh});
            while(q.size()) {
                auto [w, h] = q.front();
                q.pop();
                if(board[w][h]) continue;
                board[w][h] = 1;
                sz++;
                for(int i = 0; i < 4; i++) {
                    int nw = w + dx[i], nh = h + dy[i];
                    if(nw < 0 || nh < 0 || nw >= dims[0] || nh >= dims[1]) continue;
                    q.push({nw, nh});
                }
            }
            return poly.size() + sz == dims[0] * dims[1];
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

                int usable = isconnected(poly, {8,8}, {20,20});
                if(!usable) continue; //polyomino disonnects no matter the position

                int bx_w = min(10, width);
                int bx_h = min(10, height);
                int shift_w = bx_w - w - 1;
                int shift_h = bx_h - h - 1;

                int ok_corner_bl = isconnected(poly, {0,0}, {bx_w, bx_h});
                int ok_corner_br = isconnected(poly, {shift_w, 0}, {bx_w, bx_h});
                int ok_corner_ul = isconnected(poly, {0, shift_h}, {bx_w, bx_h});
                int ok_corner_ur = isconnected(poly, {shift_w, shift_h}, {bx_w, bx_h});

                


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