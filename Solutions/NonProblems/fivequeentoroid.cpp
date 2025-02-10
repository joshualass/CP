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

const int N = 5; // 5x5 board
const int Q = 4; // 4 queens

// Function to check if a queen attacks another under toroidal rules
bool isAttacking(int r1, int c1, int r2, int c2) {
    return (r1 == r2 || c1 == c2 || (r1 - c1) % N == (r2 - c2) % N || (r1 + c1) % N == (r2 + c2) % N);
}

// Recursive function to place queens
int placeQueens(int placed, vector<pair<int, int>>& positions, int startRow) {
    if (placed == Q) {
        vector<string> board(5,string(5,'.'));
        for(auto pos : positions) board[pos.first][pos.second] = 'Q';
        for(auto row : board) cout << row << '\n';
        cout << '\n';
        return 1; // Found a valid arrangement

    }

    int count = 0;
    for (int r = startRow; r < N; r++) {
        for (int c = 0; c < N; c++) {
            bool valid = true;
            for (auto& [qr, qc] : positions) {
                if (isAttacking(qr, qc, r, c)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                positions.push_back({r, c});
                count += placeQueens(placed + 1, positions, r);
                positions.pop_back();
            }
        }
    }
    return count;
}

int main() {
    vector<pair<int, int>> positions;
    int solutions = placeQueens(0, positions, 0);
    cout << "Number of ways to place 4 non-attacking queens: " << solutions << endl;
    return 0;
}
