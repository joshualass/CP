#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    getline(cin, line);

    stack<int> opens;
    vector<pair<int, int>> v(0);
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '(') {
            opens.push(i);
        } else if (line[i] == ')') {
            v.push_back({opens.top(), i});
            opens.pop();
        }
    }
    vector<string> poss(0);
    poss.push_back("");

    for (int i = 0; i < v.size(); i++) {
        int size = poss.size();
        while (size-- > 0) {
            poss.push_back(poss[0] + "0");
            poss.push_back(poss[0] + "1");
            poss.erase(poss.begin(), poss.begin() + 1);
        }
    }

    set<string> ans;

    for (int i = 0; i < poss.size(); i++) {
        set<int> exclude;
        string hold = poss[i];
        for (int t = 0; t < hold.size(); t++) {
            if (hold[t] == '0') {
                exclude.insert(v[t].first);
                exclude.insert(v[t].second);
            }
        }
        string out = "";
        for (int i = 0; i < line.length(); i++) {
            if (exclude.find(i) == exclude.end()) {
                out.append(line.substr(i, 1));
            }
        }
        if(exclude.empty()) {
            continue;
        }
        ans.insert(out);
    }

    for(string x : ans) {
        cout << x << '\n';
    }
    // cout << ans.size();
    return 0;
}