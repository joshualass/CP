#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
class TheSoccerDivOne {
public:

    class Compare {
        public:
            bool operator() (const array<int,2>& lhs, const array<int,2>& rhs) {
                return lhs[0] < rhs[0]; 
            }
    };


    int find(vector<int> points) {
        int a = points[0] + 12;
        points.erase(points.begin());
        sort(points.rbegin(), points.rend());
        int n = points.size();

        for(int i = 0; i <= n; i++) {
            if(i < n && points[i] > a) continue;
            for(int draws = 0; draws <= (n - i) * 4; draws++) {
                int loss_bal = (i + 1) * -4;
                priority_queue<array<int,2>, vector<array<int,2>>, Compare> pq;

                int draws_left = draws;
                vector<array<int,2>> tryfirst;

                for(int j = i; j < n; j++) {
                    
                    pq.push({points[j],0});
                }
                
                int ok = 1;
                vector<array<int,2>> left;

                while(draws_left) {

                    draws_left--;

                    array<int,2> f = {-1,-1}, s = {-1,-1};
                    while(pq.size()) {
                        if(pq.top()[0] == a) {
                            left.push_back(pq.top());
                            pq.pop();
                        } else {
                            f = pq.top();
                            pq.pop();
                            break;
                        }
                    }

                    while(pq.size()) {
                        if(pq.top()[0] == a) {
                            left.push_back(pq.top());
                            pq.pop();
                        } else {
                            s = pq.top();
                            pq.pop();
                            break;
                        }  
                    }

                    if(s[0] == -1) {
                        ok = 0;
                        break;
                    }

                    f[0]++;
                    f[1]++;
                    s[0]++;
                    s[1]++;

                    if(f[1] < 4) pq.push(f);
                    if(s[1] < 4) pq.push(s);

                }

                while(pq.size()) {
                    left.push_back(pq.top());
                    pq.pop();
                }

                for(auto [score, games] : left) {
                    int games_left = 4 - games;
                    int win = min(games_left, (a - score) / 3);
                    int loss = games_left - win;
                    loss_bal -= win;
                    loss_bal += loss;
                }

                if(ok && loss_bal <= 0) return i + 1;
            }

            int loss_need = (i + 1) * -4;
            int draw_need = 0;
            int max_draw = 0;
            for(int j = i; j < n; j++) {
                if(points[j] > a) {
                    loss_need = 1e9;
                }
                if(points[j] >= a - 4) {
                    int draws = (a - points[j]);
                    draw_need += draws;
                    max_draw = max(draws,max_draw);
                    loss_need += 4 - draws;
                } else {
                    int ln = min(4, (a - points[j] - 4) / 2);
                    int draws = 4 - ln;
                    draw_need += draws;
                    max_draw = max(max_draw, draws);
                    loss_need -= ln;
                }
            }
            if(loss_need <= 0 && (draw_need - loss_need + 1) / 2 >= max_draw) return i + 1;

        }
    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  vector<int> arg0(n0);
  for (int i=0;i<n0;++i) { cin >> arg0[i]; }
  auto c = TheSoccerDivOne();
  int ret = c.find(arg0);
  cout << ret;
}