#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
using namespace std;

class DominoesLines {
public:
    vector<string> constructLines(vector<string> tiles) {

        vector<array<int,2>> t;
        for(string s : tiles) {
            t.push_back({s[0] - '0', s[2] - '0'});
        }

        auto cnt_min_rows = [&](vector<array<int,2>> a, int p) -> int {
            vector<int> cnts(7);
            vector<vector<int>> adj(7);
            for(auto [l, r] : a) {
                cnts[l]++;
                cnts[r]++;
                adj[l].push_back(r);
                adj[r].push_back(l);
            }
            int res = 0;
            vector<int> vis(7);
            for(int i = 0; i < 7; i++) {
                queue<int> q;
                q.push(i);
                int opc = 0; //odd parity count
                int sum_cnt = 0; //sum of all counts
                int vis_p = 0;
                while(q.size()) {
                    int t = q.front();
                    q.pop();
                    if(vis[t]) continue;
                    vis[t] = 1;
                    sum_cnt += cnts[t];
                    if(t == p) vis_p = 1;
                    if(cnts[t] & 1) opc++;
                    for(int to : adj[t]) q.push(to);
                }
                if(sum_cnt == 0) continue;

                if(vis_p) {
                    int min_par = opc / 2 - (cnts[p] & 1);
                    res += min_par;
                } else {
                    res += max(1, opc / 2);
                }
            }
            return res;
        };

        int min_row = cnt_min_rows(t, -1);

        auto tile_less = [](array<int,2> lhs, array<int,2> rhs) {
            if(lhs[0] == rhs[0]) return lhs[1] < rhs[1];
            return lhs[0] < rhs[0];
        };

        vector<vector<array<int,2>>> res;
        while(t.size()) {
            int best_idx = -1;
            array<int,2> best_tile = {7,7};
            for(int i = -1; i < (int) t.size(); i++) {
                if(i == -1) {
                    if(res.size() + cnt_min_rows(t, -1) == min_row) {
                        res.push_back({});
                    } 
                } else {
                    for(int tt = 0; tt < 2; tt++) {
                        if(res.back().empty() || res.back().back()[1] == t[i][0]) {
                            array<int,2> c = t[i];
                            t.erase(t.begin() + i);
                            int add_rows = cnt_min_rows(t, c[1]);
                            int score = res.size() + add_rows - ((int) res.empty());
                            if(score == min_row) {
                                if(tile_less(c, best_tile)) {
                                    best_tile = c;
                                    best_idx = i;
                                }
                            }
                            t.insert(t.begin() + i, c);
                        }   
                        swap(t[i][0], t[i][1]);
                    }
                }
            }

            res.back().push_back(best_tile);
            t.erase(t.begin() + best_idx);
        }

        vector<string> output;
        for(auto rows : res) {
            string s = "";
            for(int i = 0; i < rows.size(); i++) {
                if(i) {
                    s.append("-");
                }
                s.push_back('0' + rows[i][0]);
                s.push_back(':');
                s.push_back('0' + rows[i][1]);
            }
            output.push_back(s);
        }
        return output;
    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> arg0(n0);
  for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
  auto c = DominoesLines();
  vector<string> ret = c.constructLines(arg0);
  for (auto& item : ret) { cout << item << "\n"; }
}