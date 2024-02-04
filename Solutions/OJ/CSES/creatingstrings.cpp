#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<string> s;
string word;
void tostr(vector<int> &v) {
    string ans = "";
    for(int i = 0; i < v.size(); i++) {
        ans += word[v[i]];
    }
    s.insert(ans);
}

void recur(vector<int> &v, vector<int> left) {
    if(left.empty()) {
        tostr(v);
        return;
    }
    
    
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> word;
    vector<int> v(word.size());
    vector<int> left;
    for(int i = 0; i < word.size(); i++) {
        left[i] = i;
    }
    recur(v,left);

    return 0;
}
