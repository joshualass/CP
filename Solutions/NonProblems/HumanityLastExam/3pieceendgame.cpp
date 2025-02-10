#include <iostream>
#include <vector>
using namespace std;

const int BOARD_SIZE = 8;
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Checks if a position is within the board
bool is_valid(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// Checks if a move is valid for a king
bool is_king_move_valid(int kx, int ky, int nx, int ny, int px, int py, int wkx, int wky) {
    if (!is_valid(nx, ny)) return false; // Out of bounds
    if ((nx == wkx && ny == wky) || (nx == px && ny == py)) return false; // Cannot land on own pieces
    for (int i = 0; i < 8; i++) {
        if (nx + dx[i] == wkx && ny + dy[i] == wky) return false; // Cannot move next to opponent king
    }
    return true;
}

// Checks if a move is valid for a pawn (ignoring captures)
bool is_pawn_move_valid(int px, int py, int nx, int ny, int wkx, int wky, int bkx, int bky) {
    if (!is_valid(nx, ny)) return false;
    if (nx != px - 1 || ny != py) return false; // Pawns move one step up
    if (nx == wkx && ny == wky) return false; // Cannot land on white king
    if (nx == bkx && ny == bky) return false; // Cannot land on black king
    return true;
}

// Checks if black can legally capture the pawn
bool can_black_capture_pawn(int px, int py, int bkx, int bky, int wkx, int wky) {
    // Black king must be adjacent to the pawn
    if (abs(bkx - px) <= 1 && abs(bky - py) <= 1) {
        //white pawn unprotected
        if(abs(wkx-px) <= 1 && abs(wky-py) <= 1) {
            return false;
        }
        return true;
    }
    return false;
}

// Checks if black is stalemated
bool is_black_stalemate(int bkx, int bky, int px, int py, int wkx, int wky) {
    for (int i = 0; i < 8; i++) {
        int nx = bkx + dx[i], ny = bky + dy[i];
        if (is_king_move_valid(bkx, bky, nx, ny, px, py, wkx, wky)) return false;
    }
    return true;
}

// Checks if white is stalemated
bool is_white_stalemate(int px, int py, int wkx, int wky, int bkx, int bky) {
    // Check if the white pawn can move
    if (is_pawn_move_valid(px, py, px - 1, py, wkx, wky, bkx, bky)) return false;

    // Check if the white king has a legal move
    for (int i = 0; i < 8; i++) {
        int nx = wkx + dx[i], ny = wky + dy[i];
        if (is_king_move_valid(wkx, wky, nx, ny, px, py, bkx, bky)) return false;
    }
    return true;
}

int main() {
    int stalemate_count = 0;

    // Iterate over all possible positions of white king, black king, and white pawn
    for (int wkx = 0; wkx < BOARD_SIZE; wkx++) {
        for (int wky = 0; wky < BOARD_SIZE; wky++) {
            for (int bkx = 0; bkx < BOARD_SIZE; bkx++) {
                for (int bky = 0; bky < BOARD_SIZE; bky++) {
                    if (abs(wkx - bkx) <= 1 && abs(wky - bky) <= 1) continue; // Kings must not be adjacent

                    for (int px = 1; px < BOARD_SIZE - 1; px++) { // Pawn cannot be on the 1st row or last row
                        for (int py = 0; py < BOARD_SIZE; py++) {
                            if ((px == wkx && py == wky) || (px == bkx && py == bky)) continue; // Pawn cannot be on the same square as a king

                            // Determine if Black can capture the pawn
                            bool black_can_take_pawn = can_black_capture_pawn(px, py, bkx, bky, wkx, wky);
                            
                            // If Black can capture the pawn, remove it and check stalemate for White
                            if(!black_can_take_pawn) {
                                // Check for stalemate conditions
                                if (is_black_stalemate(bkx, bky, px, py, wkx, wky) || is_white_stalemate(px, py, wkx, wky, bkx, bky)) {
                                    stalemate_count++;
                                }       
                            } else {
                                if (is_white_stalemate(bkx,bky, wkx, wky, bkx, bky)) {
                                    stalemate_count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Total stalemate positions: " << stalemate_count << endl;
    return 0;
}
