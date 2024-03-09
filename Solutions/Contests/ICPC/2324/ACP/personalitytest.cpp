#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
because the problem statement asks for lowest b, and then highest a. it kind of leads to using an iterative approach
iterating over all the strings in the order they appear and seeing if there is a match at any point and then finishing up
at each index and type of letter m (3000) * 26. we store all the previous strings that have this letter
then when we are iterating over the next current string, we add to a counter all the common occurrences of the previous string
because k i slow, this will not time limit exceed and we get complexity of O(m * 26 + m * n + n * n * k) because the counts of the common
occurrences can't exceed k
*/

vector<int> mat[3000][26];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // vector<vector<vector<int>>> mat(3000,vector<vector<int>>(26));
    
    int n, m, k; cin >> n >> m >> k;
    
    for(int i = 0; i < n; i++) {
        vector<int> counts(n);
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] != '.') {
                for(int x : mat[j][s[j] - 'A']) {
                    counts[x]++;
                }
                mat[j][s[j] - 'A'].push_back(i);
            }
        }
        for(int j = n - 1; j >= 0; j--) {
            if(counts[j] >= k) {
                cout << j + 1 << " " << i + 1 << '\n';
                return 0;
            }
        }
    }
    cout << "-1\n";
    return 0;
}