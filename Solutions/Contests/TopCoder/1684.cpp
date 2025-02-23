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
    int res,n,width,height;
    array<int,2> b = {-1,-1};
    vector<array<int,2>> a;
    array<vector<array<int,2>>,4> poss;
    set<vector<array<int,2>>> vis;
    vector<int> pWidth,pHeight;
    array<int,2> base = {-1,-1};

    void dfs(vector<array<int,2>> &a, array<vector<array<int,2>>,4> &poss) {
        if(vis.count(a)) return;
        vis.insert(a);
        if(count(a.begin(),a.end(),b) == 1) {
            vector<vector<int>> p(width + 1,vector<int>(height+1));
            vector<vector<int>> b(width,vector<int>(height));
            for(int i = 0; i < n; i++) {
                if(a[i] != base) {
                    for(int j = 0; j < pWidth[i]; j++) {
                        for(int k = 0; k < pHeight[i]; k++) {
                            b[a[i][0] + j][a[i][1] + k] = 1;
                        }
                    }
                }
            }
            for(int i = 0; i < width; i++) {
                for(int j = 0;j  < height; j++) {
                    p[i+1][j+1] = p[i+1][j] + p[i][j+1] - p[i][j] + b[i][j];
                }
            }
            for(int i = 0; i < n; i++) {
                if(a[i] == base) {
                    for(int j = 0; j + pWidth[i] <= width; j++) {
                        for(int k = 0; k + pHeight[i] <= height; k++) {
                            res = max(res, p[width][height] + pWidth[i] * pHeight[i] - (p[j+pWidth[i]][k+pHeight[i]] - p[j][k+pHeight[i]] - p[j+pWidth[i]][k] + p[j][k]));
                        }
                    }
                }
            }
            return;
        }
        for(int i = 0; i < n; i++) {
            if(a[i] == b) {
                for(int j = 0; j < 2; j++) {
                    for(auto [px, py] : poss[j]) {
                        int tx = px, ty = py;
                        tx += max(0,-tx);
                        ty += max(0,-ty);
                        tx -= max(0,tx+pWidth[i] - width);
                        ty -= max(0,ty+pHeight[i] - height);

                        // cout << "tx : " << tx << " a[i][0] : " << a[i][0] << " width : " << width << '\n';

                        assert(tx >= 0 && tx + pWidth[i] <= width);
                        assert(ty >= 0 && ty + pHeight[i] <= height);

                        a[i] = {tx,ty};
                        if(ty+pHeight[i] < height) poss[0].push_back({tx,ty+pHeight[i]});
                        if(tx+pWidth[i] < width) poss[1].push_back({tx+pWidth[i],ty});

                        dfs(a,poss);

                        a[i] = {-1,-1};
                        if(ty+pHeight[i] < height) poss[0].pop_back();
                        if(tx+pWidth[i] < width) poss[1].pop_back();
                    }
                }
            }
        }
    }

    int maxCover(int width, int height, vector<int> pWidth, vector<int> pHeight) {

        res = 0;
        n = pWidth.size();
        this->width = width;
        this->height = height;
        this->pWidth = pWidth;
        this->pHeight = pHeight;

        a.assign(n,b);

        poss[0].push_back({0,0});
        poss[0].push_back({width,height});
        dfs(a, poss);

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