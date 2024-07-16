#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    map<string, array<int,2>> game;
    map<array<int,2>, string> goals;
    string quaffle = "dmot";

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            string s; cin >> s;
            if(s[1] == 'G') {
                goals[{i,j}] = s;
            } else {
                if(s != "..") {
                    game[s] = {i,j};
                }
            }
        }
    }

    int red = 0, blue = 0;

    int q; cin >> q;
    for(int t = 0; t < q; t++) {
        string who; cin >> who;
        char action; cin >> action;
        if(action == 'D') {
            game[who][0]++;
        } else if(action == 'U') {
            game[who][0]--;
        } else if(action == 'R') {
            game[who][1]++;
        } else if(action == 'L') {
            game[who][1]--;
        } else if(action == 'C') {
            string ball; cin >> ball;
            if(ball == ".Q") {
                quaffle = who;
            } 
            if(ball == ".S") {
                if(who[0] == 'R') {
                    red += 10;
                    cout << t << " " << "RED CATCH GOLDEN SNITCH\n";
                    break;
                }
                if(who[0] == 'B') {
                    blue += 10;
                    cout << t << " " << "BLUE CATCH GOLDEN SNITCH\n";
                    break;
                }
            }
        } else if(action == 'T') {
            assert(game.count(quaffle));
            array<int,2> coords = game[quaffle];
            // cout << "quaffle : " << quaffle << " coords : " << coords[0] << ", " << coords[1] << '\n';
            // cout << "game/ : " << game << '\n';
            for(auto [v, u] : goals) {
                if(u == "RG" && v == coords) {
                    cout << t << " " << "BLUE GOAL\n";
                    blue++;
                }
                if(u == "BG" && v == coords) {
                    cout << t << " " << "RED GOAL\n";
                    red++;
                }
            }
            quaffle = "dmot";
        }


        if(game.count(".B")) {
            array<int,2> coords = game[".B"];
            for(auto it = game.begin(); it != game.end();) {
                array<int,2> playercoords = (*it).second;
                string name = (*it).first;
                if((name[0] == 'B' || name[0] == 'R') && name[1] >= '0' && name[1] <= '9' && coords == playercoords) {
                    cout << t << " " << name << " ELIMINATED\n";
                    it = game.erase(it);
                } else {
                    it++;
                }
            }
        }

    }

    cout << "FINAL SCORE: " << red << " " << blue << '\n';

    return 0;
}