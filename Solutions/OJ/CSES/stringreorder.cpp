#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;

    auto isok = [&](int last, vector<int> nx) -> int {
        int total = accumulate(nx.begin(), nx.end(), 0);
        int ok = 1;
        for(int i = 0; i < 26; i++) {
            int slots = (total + 1 - (i == last)) / 2;
            if(nx[i] > slots) ok = 0;
        }
        return ok;
    };

    vector<int> a(26);
    for(char c : s) a[c - 'A']++;

    string res;
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < 26; j++) {
            if(a[j] && (res.empty() || res.back() - 'A' != j)) {
                a[j]--;
                if(isok(j, a)) {
                    res.push_back(j + 'A');
                    break;
                }
                a[j]++;
            }
        }
    }

    cout << (res.size() == s.size() ? res : "-1") << '\n';

    return 0;
}
