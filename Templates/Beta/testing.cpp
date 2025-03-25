#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s = "garlic";

    vector<int> perm(6);
    iota(perm.begin(), perm.end(), 0);
    set<string> words;
    for(int i = 0; i < 720; i++) {
        string t = "";
        for(int j = 0; j < 5; j++) {
            t.push_back(s[perm[j]]);
        }
        words.insert(t);
        next_permutation(perm.begin(), perm.end());
    }
    for(auto t : words) cout << t << '\n';

    return 0;
}