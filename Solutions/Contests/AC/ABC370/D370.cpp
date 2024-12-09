// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int h, w, q; cin >> h >> w >> q;

//     vector<set<int>> rows(h);
//     vector<set<int>> cols(w);

//     for(int i = 0; i < h; i++) {
//         for(int j = 0; j < w; j++) {
//             rows[i].insert(j);
//             cols[j].insert(i);
//         }
//     }

//     int rc = 0;

//     auto rem = [&](int r, int c) -> void {
//         rows[r].erase(c);
//         rc++;
//         cols[c].erase(r);
//     };

//     for(int i = 0; i < q; i++) {
//         int r, c; cin >> r >> c;
//         r--; c--;
//         if(rows[r].count(c)) {
//             rem(r,c);
//         } else {
//             if(rows[r].lower_bound(c) != rows[r].end()) {
//                 rem(r, *rows[r].lower_bound(c));
//             }

//             if(rows[r].lower_bound(c) != rows[r].begin()) {
//                 rem(r, *--rows[r].lower_bound(c));
//             }

//             if(cols[c].lower_bound(r) != cols[c].end()) {
//                 rem(*cols[c].lower_bound(r), c);
//             }

//             if(cols[c].lower_bound(r) != cols[c].begin()) {
//                 rem(*--cols[c].lower_bound(r), c);
//             }
//         }
//     }

//     cout << h * w - rc << '\n';

//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
typedef int64_t LL;
// typedef vector<int> vi;
// typedef pair<LL,LL> pii;
// #define mp make_pair
// #define pb push_back
// #define f first
// #define s second


//var 

int main(){
    // #ifndef ONLINE_JUDGE
    //     //for getting input from input.txt
    //     freopen("input.txt", "r", stdin);
    //     //for writing output to output.txt
    //     freopen("output.txt", "w", stdout);
    // #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, q;
    cin >> h >> w >> q;
    vector<set<int>> row(h);
    vector<set<int>> col(w);
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            row[i].insert(j);
            col[j].insert(i);
        }
    }
    for(int ctr= 0; ctr < q; ctr++){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if(row[x].count(y)){
            row[x].erase(y);
            col[y].erase(x);
        } 
        else{
            // auto curr_row = lower_bound(row[x].begin(), row[x].end(), y);
            // auto curr_col = lower_bound(col[y].begin(), col[y].end(), x);

            auto curr_row = row[x].lower_bound(y);
            auto curr_col = col[y].lower_bound(x);

            auto pre_row = row[x].end();
            auto pre_col = col[y].end();


            if(curr_row != row[x].begin()){
                pre_row = prev(curr_row);
            }
            if(curr_col != col[y].begin()){
                pre_col = prev(curr_col);
            }
            int val = 0;
            if(curr_row != row[x].end()){
                val = *curr_row;
                row[x].erase(curr_row);
                col[val].erase(x);
            }
            if(pre_row != row[x].end()){
                val = *pre_row;
                row[x].erase(pre_row);
                col[val].erase(x);
            }
            if(curr_col != col[y].end()){
                val = *curr_col;
                col[y].erase(curr_col);
                row[val].erase(y);
            }
            if(pre_col != col[y].end()){
                val = *pre_col;
                col[y].erase(pre_col);
                row[val].erase(y);
            }
        }
    }
    int ans = 0;
    for(int i=0; i<h; i++){
        ans += row[i].size();
    }
    cout << ans << "\n";
    // cout << "\n";
    
    cout.flush();
    return 0;
}