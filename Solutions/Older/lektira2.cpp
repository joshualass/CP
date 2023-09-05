#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<string> words;

string rev(string l) {
    string ans = "";
    for(int i = l.size() - 1; i >= 0; i--) {
        ans += l[i];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    cin >> line;
    int n = line.size();
    for(int i = 1; i < n; i++) {
        for(int t = i + 1; t < n; t++) {
            words.insert(rev(line.substr(0,i)) + rev(line.substr(i, t - i)) + rev(line.substr(t)));
//            cout << "first: " << rev(line.substr(0,i)) << " second: " << rev(line.substr(i, t - i)) << " third: " << line.substr(t) << '\n'; 
        }
    }

    cout << *(words.begin());

    return 0;
}