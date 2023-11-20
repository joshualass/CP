#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T>
void printS(stack<T> x) {
    cout << "stack: ";
    while(x.size()) {
        cout << x.top() << ' ';
        x.pop();
    }
    cout << "\n";
}
// int cnt = 0;
void calc_ans(int i, vector<vector<int>> &stacks, vector<int> &ans, vector<bool> &visiting, stack<int> &s) {
    // cnt++;
    // cout << "i: " << i << '\n';
    // printS(s);
    if(visiting[i]) { //cycle found
        // cout << "cycle found --- ";
        while(s.top() != i) {
            // cout << s.top() << " ";
            visiting[s.top()] = 0;
            s.pop();
        }
        // cout << i << " ";
        s.pop();
        visiting[i] = 0;
        // cout << '\n';
    }

    if(stacks[i].empty() && ans[i] == -1) {
        ans[i] = i;
    }

    if(ans[i] != -1) { //we are done here
        // cout << "ans found --- ans[i] : " << ans[i] << '\n';
        // s.push(i);
        while(s.size()) {
            int top = s.top();
            visiting[top] = false;
            // cout << "top : " << s.top() << " ";
            // cout << "setting answer of index : " << top << " to value : " << ans[i] << '\n';
            ans[top] = ans[i];
            s.pop();
        }
        return;
    }
    //¡VAMOS!
    s.push(i);
    visiting[i] = true;
    int next = stacks[i].back();
    // cout << "VAMOS : " << i << " next : " << next << '\n';
    stacks[i].pop_back();
    calc_ans(next, stacks, ans, visiting, s);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<vector<int>> stacks(n);

    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        for(int j = 0; j < k; j++) {
            int idx; cin >> idx;
            idx--;
            stacks[i].push_back(idx);
        }
    }

    vector<int> ans(n,-1);
    vector<bool> visiting(n);

    stack<int> s;

    for(int i = 0; i < n; i++) {
        calc_ans(i, stacks, ans, visiting, s);
    }

    for(auto x : ans) cout << ++x << " ";
    cout << endl;

    // cout << cnt << '\n';

    return 0;
}