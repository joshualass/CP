#include <bits/stdc++.h>

using namespace std;

template<typename Type>
void print_grid(const vector<vector<Type>>& grid) {
    cout << "[";
    for (const auto& row : grid) {
        cout << "[";
        for (const auto& i : row) {
            cout << i << ", ";
        }
        cout << "]," << endl;
    }
    cout << "]" << endl;
}

// diagonal different parity check
bool check_diagonal(const vector<vector<long long>>& grid, const int& i, const int& j) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    // can only have diagonal elements if 2x2 or bigger
    if (rows > 1 && cols > 1) {
        long long val = grid[i][j];
        long long rem = val % 2;

        long long bottom_right = (i < rows - 1 && j < cols - 1 && grid[i + 1][j + 1] != 0) ? grid[i + 1][j + 1] % 2 : -1;
        long long bottom_left = (i < rows - 1 && j > 0 && grid[i + 1][j - 1] != 0) ? grid[i + 1][j - 1] % 2 : -1;
        long long top_right = (i > 0 && j < cols - 1 && grid[i - 1][j + 1] != 0) ? grid[i - 1][j + 1] % 2 : -1;
        long long top_left = (i > 0 && j > 0 && grid[i - 1][j - 1] != 0) ? grid[i - 1][j - 1] % 2 : -1;

        if (val == 0) {
            return true;
        }

        // top left corner
        if (i == 0 && j == 0) {
            if (bottom_right == rem) {
                return false;
            }
        }
        // top right corner
        else if (i == 0 && j == cols - 1) {
            if (bottom_left == rem) {
                return false;
            }
        }
        // bottom left corner
        else if (i == rows - 1 && j == 0) {
            if (top_right == rem) {
                return false;
            }
        }
        // bottom right corner
        else if (i == rows - 1 && j == cols - 1) {
            if (top_left == rem) {
                return false;
            }
        }
        // top row but not corner
        else if (i == 0) {
            if (bottom_left == rem || bottom_right == rem) {
                return false;
            }
        }
        // bottom row but not corner
        else if (i == rows - 1) {
            if (top_left == rem || top_right == rem) {
                return false;
            }
        }
        // left column but not corner
        else if (j == 0) {
            if (top_right == rem || bottom_right == rem) {
                return false;
            }
        }
        // right column but not corner
        else if (j == cols - 1) {
            if (top_left == rem || bottom_left == rem) {
                return false;
            }
        }
        // has all 4 diagonals
        else {
            if (top_left == rem || top_right == rem || bottom_left == rem || bottom_right == rem) {
                return false;
            }
        }
    }
    return true;
}

bool check_increasing(const vector<vector<long long>>& grid, const int& i, const int& j) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    long long val = grid[i][j];

    if (val == 0) {
        return true;
    }

    return (j == 0 || val > grid[i][j - 1] || grid[i][j - 1] == 0) && (j == cols - 1 || val < grid[i][j + 1] || grid[i][j + 1] == 0) && (i == 0 || val > grid[i - 1][j] || grid[i - 1][j] == 0) && (i == rows - 1 || val < grid[i + 1][j] || grid[i + 1][j] == 0);
}

// used to make sure grid is valid
bool check(const vector<vector<long long>>& grid) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(check_diagonal(grid, i, j) && check_increasing(grid, i, j))) {
                return false;
            }
        }
    }
    return true;
}

long long get_lowest(const vector<vector<long long>>& grid, const vector<vector<bool>>& parity, int i, int j) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();
    long long left = j == 0 ? 0 : grid[i][j - 1];
    long long top = i == 0 ? 0 : grid[i - 1][j];

    long long lower_bound = 0;

    if (left == 0 && top == 0) {
        lower_bound = 0;
    }
    else if (left == 0) {
        lower_bound = top;
    }
    else if (top == 0) {
        lower_bound = left;
    }
    else {
        lower_bound = max(left, top);
    }

    lower_bound++;

    if ((lower_bound % 2 == 0) != parity[i][j] && rows != 1 && cols != 1) {
        lower_bound++;
    }

    return lower_bound;
}

long long get_highest(const vector<vector<long long>>& grid, const vector<vector<bool>>& parity, int i, int j) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();
    long long right = j == cols - 1 ? 0 : grid[i][j + 1];
    long long down = i == rows - 1 ? 0 : grid[i + 1][j];

    long long upper_bound = 0;

    if (right == 0 && down == 0) {
        upper_bound = numeric_limits<long long>::max();
    }
    else if (right == 0) {
        upper_bound = down;
    }
    else if (down == 0) {
        upper_bound = right;
    }
    else {
        upper_bound = min(right, down);
    }

    upper_bound--;

    if ((upper_bound % 2 == 0) != parity[i][j] && rows != 1 && cols != 1) {
        upper_bound--;
    }

    return upper_bound;
}

long long sum_grid(const vector<vector<long long>>& grid) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();
    long long total = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            total += grid[i][j];
        }
    }

    return total;
}

pair<bool, bool> get_parity(const vector<vector<long long>>& grid, vector<vector<bool>>& parity_row, vector<vector<bool>>& parity_col) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    int i_arg = -1;
    int j_arg = -1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 0) {
                i_arg = i;
                j_arg = j;
                parity_col[i][j] = grid[i][j] % 2 == 0;
                parity_row[i][j] = grid[i][j] % 2 == 0;
            }
        }
    }

    // every value in grid is a 0
    if (i_arg == -1) {
        // top left value will be a 1, so 1st column is odd, 2nd column is even, etc.
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                parity_row[i][j] = j % 2 == 1;
                parity_col[i][j] = j % 2 == 1;
            }
        }
    }
    else {
        bool use_col = true;
        bool use_row = true;

        // alternate parities of columns
        bool is_even_og = grid[i_arg][j_arg] % 2 == 0;

        for (int j = 0; j < cols; j++) {
            bool is_even = (abs(j - j_arg) % 2 == 0) ? is_even_og : !is_even_og;

            for (int i = 0; i < rows; i++) {
                if (grid[i][j] == 0) {
                    parity_col[i][j] = is_even;
                }
                else {
                    if ((grid[i][j] % 2 == 0) == is_even) {
                        parity_col[i][j] = is_even;
                    }
                    // grid is not possible to solve
                    else {
                        use_col = false;
                        goto exit_col;
                    }
                }
            }
        }

        exit_col:

        // try rows
        for (int i = 0; i < rows; i++) {
            bool is_even = (abs(i - i_arg) % 2 == 0) ? is_even_og : !is_even_og;

            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    parity_row[i][j] = is_even;
                }
                else {
                    if ((grid[i][j] % 2 == 0) == is_even) {
                        parity_row[i][j] = is_even;
                    }
                    // grid is not possible to solve
                    else {
                        use_row = false;
                        goto exit_row;
                    }
                }
            }
        }

        exit_row:

        return {use_row, use_col};
    }
    return {true, true};
}

long long algorithm(vector<vector<long long>>& grid, const vector<vector<bool>>& parity) {
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    // for n x 1 and 1 x n, only need to check increasing condition since there are no diagonals
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 0) {
                long long lower_bound = get_lowest(grid, parity, i, j);
                // long long upper_bound = get_highest(grid, parity, i, j);
                //
                // if (upper_bound < lower_bound) {
                //     return -1;
                // }

                grid[i][j] = lower_bound;
            }
        }
    }

    if (check(grid)) {
        return sum_grid(grid);
    }

    // print_grid(grid);

    return -1;
}

bool is_all_zeros(const vector<vector<long long>>& grid) {
    for (const vector<long long>& row : grid) {
        for (const long long& num : row) {
            if (num != 0) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    // ifstream cin("input.txt"); // UNCOMMENT WHEN SUBMITTING
    // ofstream cout("output.txt"); // UNCOMMENT WHEN SUBMITTING

    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long rows, cols;
    cin >> rows >> cols;

    vector grid(rows, vector(cols, static_cast<long long>(0)));

    vector parity_row(rows, vector(cols, false));
    vector parity_col(rows, vector(cols, false));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            long long num;
            cin >> num;

            grid[i][j] = num;
        }
    }

    if (is_all_zeros(grid)) {
        long long pos1 = cols * rows * (rows + (2 * cols) - 1) / 2;
        long long pos2 = cols * rows * (cols + (2 * rows) - 1) / 2;

        cout << min(pos1, pos2) << endl;
        return 0;
    }

    pair<bool, bool> pair_status = get_parity(grid, parity_row, parity_col);
    bool row_status = pair_status.first;
    bool col_status = pair_status.second;

    // if (!((row_status || col_status) && check(grid))) {
    //     cout << -1 << endl;
    //     return 0;
    // }

    auto grid2 = grid;

    // try both parities
    long long pos1 = -1;
    long long pos2 = -1;
    if (row_status) {
        pos1 = algorithm(grid, parity_row);
    }

    if (col_status) {
        pos2 = algorithm(grid2, parity_col);
    }

    if (pos1 == -1) {
        cout << pos2 << endl;
    }
    else if (pos2 == -1) {
        cout << pos1 << endl;
    }
    else {
        cout << min(pos1, pos2) << endl;
        // print_grid(grid);
    }

    return 0;
}