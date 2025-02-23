#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Piece {
    string name;
    int square_cover;
    int cost;
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Piece> pieces = {
        {"King",9,0},
        {"Pawn",3,1},
        {"Queen",28,9},
        {"Bishop",14,3},
        {"Knight",9,3},
        {"Rook",15,5}
    };

    int need = 64 - 9;

    auto dfs = [&] (auto self, vector<Piece> inuse, int covered, int cost_left, int idx) -> void {
        if(idx == pieces.size()) {
            if(covered >= 64) {
                cout << "combo covers "
            }
        }
        for(int i = 0; cost_left + i * pieces)



    };

    return 0;
}