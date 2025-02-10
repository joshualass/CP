#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int BOARD_SIZE = 8;

vector<pair<int, int>> king_moves = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
vector<pair<int, int>> knight_moves = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
vector<pair<int, int>> rook_moves, bishop_moves, queen_moves, pawn_moves;

void init_moves() {
    for(int i = 1; i < BOARD_SIZE; i++) {
        rook_moves.push_back({i, 0});
        rook_moves.push_back({-i, 0});
        rook_moves.push_back({0, i});
        rook_moves.push_back({0, -i});
        
        bishop_moves.push_back({i, i});
        bishop_moves.push_back({-i, -i});
        bishop_moves.push_back({i, -i});
        bishop_moves.push_back({-i, i});
    }
    queen_moves.insert(queen_moves.end(), rook_moves.begin(), rook_moves.end());
    queen_moves.insert(queen_moves.end(), bishop_moves.begin(), bishop_moves.end());
    pawn_moves = {{1, 1}, {1, -1}};
}

bool is_valid(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// Generate all hybrid pieces by merging two sets of moves
vector<vector<pair<int, int>>> generate_hybrid_pieces() {
    vector<vector<pair<int, int>>> hybrid_pieces;
    vector<vector<pair<int, int>>> base_pieces = {king_moves, knight_moves, rook_moves, bishop_moves, queen_moves, pawn_moves};
    
    for (size_t i = 0; i < base_pieces.size(); i++) {
        for (size_t j = i + 1; j < base_pieces.size(); j++) {
            vector<pair<int, int>> hybrid = base_pieces[i];
            hybrid.insert(hybrid.end(), base_pieces[j].begin(), base_pieces[j].end());
            hybrid_pieces.push_back(hybrid);
        }
    }
    return hybrid_pieces;
}

bool is_king_in_check(int kx, int ky, int px, int py, vector<pair<int, int>>& moves) {
    for (auto [dx, dy] : moves) {
        int x = px + dx, y = py + dy;
        if(x == kx && y == ky) return 1;
    }
    return false;
}

bool has_escape(int kx, int ky, int px, int py, vector<pair<int, int>>& moves) {
    for (auto [dx, dy] : king_moves) {
        int nx = kx + dx, ny = ky + dy;
        if (is_valid(nx, ny) && (!is_king_in_check(nx, ny, px, py, moves) || nx == px && ny == py)) {
            return true;
        }
    }
    return false;
}

int count_checkmates() {
    int count = 0;
    vector<vector<pair<int, int>>> hybrid_pieces = generate_hybrid_pieces();

    for(auto hpiece : hybrid_pieces) {
        cout << hpiece << '\n';
    }
    
    for (auto& moves : hybrid_pieces) {
        set<pair<int, int>> seen;
        for (int kx = 0; kx < BOARD_SIZE; kx++) {
            for (int ky = 0; ky < BOARD_SIZE; ky++) {
                for (int px = 0; px < BOARD_SIZE; px++) {
                    for (int py = 0; py < BOARD_SIZE; py++) {
                        if (kx == px && ky == py) continue; // Same position
                        if (is_king_in_check(kx, ky, px, py, moves) && !has_escape(kx, ky, px, py, moves)) {
                            seen.insert({kx * BOARD_SIZE + ky, px * BOARD_SIZE + py});
                        }
                    }
                }
            }
        }
        count += seen.size();
    }
    return count;
}

int main() {
    init_moves();
    cout << "Total distinct checkmate positions: " << count_checkmates() << endl;
    return 0;
}
