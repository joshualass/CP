#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int SIZE = 2e5;

int ans[SIZE];

int post(int index, vector<vector<int>>& adj, vector<int>& parents) {
    if(index != 0 && adj[index].size() == 1) {
        ans[index] = 0;
        return 1;
    }
    int sum = 0;
    for(int i = 0; i < adj[index].size(); i++) {
        if(adj[index][i] != parents[index]) {
            sum += post(adj[index][i], adj, parents);
        }
    }
    ans[index] = sum;
    return sum + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<vector<int>> adj(n);
    vector<int> parents(n);

    for(int i = 1; i < n; i++) {
        int num; cin >> num;
        num--;
        adj[i].push_back(num);
        adj[num].push_back(i);
        parents[i] = num;
    }
    post(0, adj, parents);
    for(int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
