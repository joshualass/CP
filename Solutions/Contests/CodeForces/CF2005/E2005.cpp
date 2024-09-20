#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//consider taking a trip to implementation school

/*
many wa bc forgot definition of the problem

make the observation that we should always choose later a[i] because it gives less freedom. 
In other words, we shouldn't choose an element if there is the same element which is in its bottom-right rectangle.

*/

void solve() {
    
    int l, n, m; cin >> l >> n >> m;
    vector<int> ids(n*m,-1);
    for(int i = 0; i < l; i++) {
        int a; cin >> a;
        a--;
        if(ids[a] == -1) {
            ids[a] = i;
        }
    }

    //for element i in array a, the max col it appears for each row. 
    vector<vector<int>> hicols(l, vector<int>(n,-1));

    //get hi cols
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int num; cin >> num;
            num--;
            if(ids[num] != -1) {
                hicols[ids[num]][i] = j;
            }
        }
    }

    //prune hi cols, so that they make a mono set
    for(int i = 0; i < l; i++) {
        int hicol = -1;
        for(int j = n - 1; j >= 0; j--) {
            if(hicols[i][j] > hicol) {
                hicol = hicols[i][j];
            } else {
                hicols[i][j] = -1;
            }
        }
    }

    //given a previous mono set, ensure the next one is nested.
    for(int i = 1; i < l; i++) {
        int locol = m;
        for(int j = 0; j < n; j++) {
            //handle case when directly below which is ok. 
            //has to be completely nested. 
            if(hicols[i][j] <= locol) {
                hicols[i][j] = -1;
            }
            if(hicols[i-1][j] != -1) {
                locol = hicols[i-1][j];
            }

            // int keep = 0;
            // if(hicols[i][j] >= locol) {
            //     keep = 1;
            // }
            // if(hicols[i-1][j] != -1) {
            //     locol = hicols[i-1][j];
            // }
            // if(hicols[i][j] <= locol && !keep) {
            //     hicols[i][j] = -1;
            // }
        }
    }

    //find winners
    for(int i = l - 2; i >= 0; i--) {
        int hicol = -1;
        for(int j = n - 1; j >= 0; j--) {
            if(hicol > hicols[i][j]) {
                hicols[i][j] = -1;
            }
            if(hicols[i+1][j] != -1) {
                hicol = hicols[i+1][j];
            }
        }
    }

    int found = 0;
    for(int i = 0; i < n; i++) {
        if(hicols[0][i] != -1) {
            found = 1;
        }
    }

    cout << (found ? 'T' : 'N') << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {
    
//     int l, n, m; cin >> l >> n >> m;
//     map<int,int> ids;

//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         if(ids.count(num) == 0) {
//             ids[num] = i;
//         }
//     }

//     vector<vector<set<int>>> nears(l, vector<set<int>>(n));

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             int num; cin >> num;
//             if(ids.count(num)) {
//                 nears[ids[num]][i].insert(j);
//             }
//         }
//     }

//     vector<vector<int>> r(l, vector<int>(n,-2));

//     for(int i = 0; i < l; i++) {

//         //cur is current column of previous mono set
//         int cur = -2;
//         if(i = 0) {
//             cur = -1;
//         }

//         //hi is current highest index of current mono set
//         int hi = -2;

//         for(int j = n - 1; j >= 0; j--) {

//             if(nears[l][j].size()) {
//                 int highest = (*--nears[l][j].lower_bound(m));
//                 if()
//             }

//         }


//         for(int j = 0; j < n; j++) {

//             if(cur != -2 && nears[i][j].upper_bound(cur) != nears[i][j].end()) {

//             }



//             if(i && r[i-1][j] != -2) {
//                 cur = r[i-1][j];
//             }

//         }

//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }