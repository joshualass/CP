#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

class RookAttacks {
public:
    vector<long long> classify(int D, vector<int> R0, vector<int> C0, vector<int> T0, int seed, int steps) {

        map<int,map<int,int>> xy, yx;
        set<int> xs, ys;

        int rook_cnt = 0;

        auto add_rook = [&](int x, int y, int t) -> void {
            xy[x][y] = t;
            yx[y][x] = t;
            xs.insert(x);
            ys.insert(y);
            rook_cnt++;
        };

        for(int i = 0; i < R0.size(); i++) {
            add_rook(R0[i], C0[i], T0[i]);
        }

        ll state = seed;
        for(int i = 0; i < steps; i++) {
            state = (state * 1103515245 + 12345) & ((1LL << 31) - 1);
            int x = state % D;
            state = (state * 1103515245 + 12345) & ((1LL << 31) - 1);
            int y = state % D;
            state = (state * 1103515245 + 12345) & ((1LL << 31) - 1);
            int t = state / (1 << 30);
            if(xy[x].count(y) == 0) {
                add_rook(x,y,t);
            }
        }

        vector res(5, vector<ll>(5));

        res[0][0] = 1LL * D * D - rook_cnt;

        for(auto [x, m] : xy) {
            array<int,2> p = {-1,-1};
            for(auto [y, color] : m) {
                int add = y - (p[0] + 1);
                array<int,2> type = {0,0};
                if(p[1] != -1) {
                    type[p[1]]++;
                }
                type[color]++;
                res[type[0]][type[1]] += add;
                res[0][0] -= add;
                p = {y, color};
            }
            int last = D;
            int add = D - (p[0] + 1);
            array<int,2> type = {0,0};
            type[p[1]]++;
            res[type[0]][type[1]] += add;
            res[0][0] -= add;
        }

        for(auto [y, m] : yx) {
            array<int,2> p = {-1,-1};
            for(auto [x, color] : m) {
                int add = x - (p[0] + 1);
                array<int,2> type = {0,0};
                if(p[1] != -1) {
                    type[p[1]]++;
                }
                type[color]++;
                res[type[0]][type[1]] += add;
                res[0][0] -= add;
                p = {x, color};
            }
            int last = D;
            int add = D - (p[0] + 1);
            array<int,2> type = {0,0};
            type[p[1]]++;
            res[type[0]][type[1]] += add;
            res[0][0] -= add;
        }   

        map<int,int> cx, cy;
        int cp = 0;
        for(int x : xs) {
            cx[x] = cp++;
        }

        cp = 0;
        for(int y : ys) {
            cy[y] = cp++;
        }

        vector<map<int,int>> cxy(cx.size()), cyx(cy.size());

        for(auto [x, m] : xy) {
            for(auto [y, t] : m) {
                cxy[cx[x]][cy[y]] = t;
                cyx[cy[y]][cx[x]] = t;
            }
        }

        vector trees(3, vector(3, Tree<int>(cx.size())));

        auto toggle_before = [&](int x, int y, int val) -> void {
            array<int,2> type = {0,0};
            map<int,int>::iterator it = cxy[x].find(y);
            type[it->second]++;
            if(it != cxy[x].begin()) {
                it--;
                type[it->second]++;
            }
            trees[type[0]][type[1]].update(x, val);
        };

        auto toggle_after = [&](int x, int y, int val) -> void {
            array<int,2> type = {0,0};
            map<int,int>::iterator it = cxy[x].find(y);
            type[it->second]++;
            it++;
            if(it != cxy[x].end()) {
                type[it->second]++;
            }
            trees[type[0]][type[1]].update(x, val);
        };

        //initialize cols for each x
        for(int i = 0; i < cxy.size(); i++) {
            int y = cxy[i].begin()->first;
            toggle_before(i, y, 1);
        }

        for(int y = 0; y < cyx.size(); y++) {
            //add new cols
            if(y) {
                for(auto [x, t] : cyx[y - 1]) {
                    toggle_after(x, y - 1, 1);
                }
            }
            //clear the blocked columns
            for(auto [x, t] : cyx[y]) {
                toggle_before(x, y, 0);
            }

            array<int,2> p = {-1,-1};
            for(auto [x, t] : cyx[y]) {
                int add = x - 1 - p[0];
                array<int,2> type = {0,0};
                type[t]++;
                if(p[1] != -1) {
                    type[p[1]]++;
                }
                for(int c0 = 0; c0 < 3; c0++) {
                    for(int c1 = 0; c1 < 3; c1++) {
                        array<int,2> next_type = {type[0] + c0, type[1] + c1};
                        array<int,2> prev_type = {c0, c1};
                        int cnt = trees[c0][c1].query(p[0] + 1, x);
                        res[next_type[0]][next_type[1]] += cnt;
                        res[prev_type[0]][prev_type[1]] -= cnt;
                        res[type[0]][type[1]] -= cnt;
                        res[0][0] += cnt;
                    }
                }
                p = {x, t};
            }
            array<int,2> type = {0,0};
            type[p[1]]++;
            int x = D;
            for(int c0 = 0; c0 < 3; c0++) {
                for(int c1 = 0; c1 < 3; c1++) {
                    array<int,2> next_type = {type[0] + c0, type[1] + c1};
                    array<int,2> prev_type = {c0, c1};
                    int cnt = trees[c0][c1].query(p[0] + 1, x);
                    res[next_type[0]][next_type[1]] += cnt;
                    res[prev_type[0]][prev_type[1]] -= cnt;
                    res[type[0]][type[1]] -= cnt;
                    res[0][0] += cnt;
                }
            }
        }

        vector<ll> res2;
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                res2.push_back(res[i][j]);
            }
        }
        return res2;
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n1; cin >> n1;
  vector<int> arg1(n1);
  for (int i=0;i<n1;++i) { cin >> arg1[i]; }
  int n2; cin >> n2;
  vector<int> arg2(n2);
  for (int i=0;i<n2;++i) { cin >> arg2[i]; }
  int n3; cin >> n3;
  vector<int> arg3(n3);
  for (int i=0;i<n3;++i) { cin >> arg3[i]; }
  int arg4;
  cin >> arg4;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg5;
  cin >> arg5;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = RookAttacks();
  vector<long long> ret = c.classify(arg0, arg1, arg2, arg3, arg4, arg5);
  for (auto& item : ret) { cout << item << "\n"; }
}