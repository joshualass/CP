template<typename T>
struct GE {

    int r, c;
    vector<vector<T>> mat;
    vector<T> x;

    GE(vector<vector<T>> mat, vector<T> x) {
        this->mat = mat;
        this->x = x;
        r = mat.size();
        c = mat[0].size();
    }

    //does row operation row /= div
    void divideRow(int row, T div) {
        for(int i = 0; i < c; i++) {
            mat[row][i] /= div;
        }
        x[row] /= div;
    }

    //does row operation r2 = r2 + r1 * s
    void addRow(int r1, T s, int r2) {
        for(int i = 0; i < c; i++) {
            mat[r2][i] = mat[r2][i] + mat[r1][i] * s;
        }
        x[r2] = x[r2] + x[r1] * s;
    }

    void eliminate(bool print) {
        printMat(print);
        //first step of GE
        vector<int> visited_rows(r,-1);
        for(int col = 0; col < c; ++col) {
            for(int row = 0; row < r; ++row) {
                if(mat[row][col] != 0 && visited_rows[row] == -1) {
                    visited_rows[row] = col;
                    if(mat[row][col] != 1) {
                        divideRow(row, mat[row][col]);
                        printMat(print);
                    }
                    bool shouldprint = 0;
                    for(int row2 = 0; row2 < r; row2++) {
                        if(mat[row2][col] != 0 && row2 != row) {
                            shouldprint = 1;
                            addRow(row, -mat[row2][col], row2);
                        }
                    }
                    if(shouldprint) {
                        printMat(print);
                    }
                    break;
                }
            }
        }
        //second step of GE
        for(int col = c - 1; col >= 0; col--) {
            for(int row = 0; row < r; row++) {
                if(visited_rows[row] == col) {
                    bool shouldprint = 0;
                    for(int row2 = 0; row2 < r; row2++) {
                        if(mat[row2][col] != 0 && row2 != row) {
                            shouldprint = 1;
                            addRow(row, -mat[row2][col], row2);
                        }
                    }
                    if(shouldprint) {
                        printMat(print);
                    }
                }
            }
        }
        cout << "resulting matrix\n";
        printMat(1);
    }

    void printMat(bool print) {
        if(print) {
            for(int i = 0; i < r; i++) {
                cout << '[';
                for(int j = 0; j < c; j++) {
                    cout << mat[i][j] << ",|"[j == c - 1];
                }
                cout << x[i] << "]\n";
            }
        }
        cout << '\n';
    }
};