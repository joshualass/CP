#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool k_pints(int A, int B, int C, int a, int b, int c, int k) {

// #create visited array with all nodes set to unvisited
// visited = [A][B][C]

    vector<vector<vector<bool>>> visited(A+1,vector<vector<bool>>(B+1,vector<bool>(C+1)));

// q = queue()
    queue<vector<int>> q;
    q.push({a,b,c});

    while(!q.empty()) {
        vector<int> val = q.front();
        q.pop();
        int curr_a = val[0];
        int curr_b = val[1];
        int curr_c = val[2];
        // cout << "ca : " << curr_a << " cb : " << curr_b << " cc : " << curr_c << endl;
        if(visited[curr_a][curr_b][curr_c] == 1) continue;

        visited[curr_a][curr_b][curr_c] = 1;

        if(curr_a == k || curr_b == k || curr_c == k) {
            return 1;
        }

        int pourAB = min(curr_a,B-curr_b);
        q.push({
            curr_a - pourAB,
            curr_b + pourAB,
            curr_c
        });

        int pourAC = min(curr_a,C-curr_c);
        q.push({
            curr_a - pourAC,
            curr_b,
            curr_c + pourAC
        });

        int pourBA = min(curr_b,A-curr_a);
            q.push({
            curr_a + pourBA,
            curr_b - pourBA,
            curr_c
        });

        int pourBC = min(curr_b,C-curr_c);
        q.push({
            curr_a,
            curr_b - pourBC,
            curr_c + pourBC
        });

        int pourCA = min(curr_c,A-curr_a);
        q.push({
            curr_a + pourCA,
            curr_b,
            curr_c - pourCA
        });

        int pourCB = min(curr_c,B-curr_b);
        q.push({
            curr_a,
            curr_b + pourCB,
            curr_c - pourCB
        });
    }

    return 0;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << "test0 --- : " << k_pints(10,11,12,1,10,10,1) << endl;
    cout << "test1 --- : " << k_pints(10,11,12,6,7,8,1) << endl;
    cout << "test2 --- : " << k_pints(10,11,12,1,2,3,7) << endl;

    return 0;
}