#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<string> words;

void recur(vector<char> chars, vector<char> left) {
    if(left.size() == 0) {
        string ans = "";
        for(int i = 0; i < chars.size(); i++) {
            ans += chars[i];
        }
        words.insert(ans);
        return;
    }
    for(int i = 0; i < left.size(); i++) {
        chars.push_back(left[i]);
        char rem = left[i];
        left.erase(left.begin() + i);
        recur(chars, left);
        left.insert(left.begin() + i, rem);
        chars.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string word; cin >> word;
    vector<char> pass (word.size());
    for(int i = 0; i < word.size(); i++) {
        pass[i] = word[i];
    }
    recur({}, pass);
    cout << words.size() << '\n';
    for(string x : words) {
        cout << x << '\n';
    }
    return 0;
}