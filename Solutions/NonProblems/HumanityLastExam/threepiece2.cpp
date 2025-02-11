#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 8;

int pdr[2]{1,1}, pdc[2]{-1,1};
int kdr[8]{1,1,1,0,-1,-1,-1,0}, kdc[8]{-1,0,1,1,1,0,-1,-1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int res = 0;

    for(int wkr = 0; wkr < N; wkr++) {
        for(int wkc = 0; wkc < N; wkc++) {
            for(int bkr = 0; bkr < N; bkr++) {
                for(int bkc = 0; bkc < N; bkc++) {
                    if(abs(wkr-bkr) <= 1 && abs(wkc-bkc) <= 1) continue; //no touching kings
                    for(int pr = 1; pr < N - 1; pr++) { //white pawn cannot be on first or last row
                        for(int pc = 0; pc < N; pc++) {
                            set<array<int,2>> s = {{wkr,wkc},{bkr,bkc},{pr,pc}};
                            if(s.size() != 3) continue;

                            set<array<int,2>> black_bad; //squares black king cannot reach
                            set<array<int,2>> white_bad; //squares white king cannot reach
                            for(int i = 0; i < 2; i++) {
                                black_bad.insert({pr+pdr[i],pc+pdc[i]});
                            }

                            for(int i = 0; i < 8; i++) {
                                black_bad.insert({wkr+kdr[i],wkc+kdc[i]}); //black can't visit near king
                                white_bad.insert({bkr+kdr[i],bkc+kdc[i]}); //white can't visit near king
                            }

                            white_bad.insert({pr,pc}); //white king cannot visit own pawn

                            int black_check = black_bad.count({bkr,bkc});

                            int black_has_move = 0;
                            for(int i = 0; i < 8; i++) {
                                int bknr = bkr + kdr[i], bknc = bkc + kdc[i];
                                if(bknr >= 0 && bknr < N && bknc >= 0 && bknc < N && black_bad.count({bknr,bknc}) == 0) {
                                    black_has_move = 1;
                                }
                            }

                            int white_has_move = 0;
                            if(s.count({pr+1,pc}) == 0) white_has_move = 1; //push pawn

                            for(int i = 0; i < 8; i++) {
                                int wknr = wkr + kdr[i], wknc = wkc + kdc[i];
                                if(wknr >= 0 && wknr < N && wknc >= 0 && wknc < N && white_bad.count({wknr,wknc}) == 0) {
                                    white_has_move = 1;
                                }
                            }

                            if(!black_check && !black_has_move || !white_has_move) {
                                vector<string> board(8,string(8,'.'));
                                board[wkr][wkc] = 'W';
                                board[bkr][bkc] = 'B';
                                board[pr][pc] = 'p';
                                reverse(board.begin(),board.end());
                                for(auto row : board) cout << row << '\n';
                                res++;
                                cout << '\n';
                            }

                        }
                    }
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}