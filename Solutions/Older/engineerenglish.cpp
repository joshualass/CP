#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unordered_set<string> words;

    while(!cin.eof()) {
        string line;
        getline(cin,line);
        stringstream ss(line);
        while(!ss.eof()) {
            string word; ss >> word;
            string lowercase = "";
            for(int i = 0; i < word.size(); i++) {
                if(word[i] < 'a') {
                    lowercase += word[i] - 'A' + 'a';
                } else {
                    lowercase += word[i];
                }
            }
            if(words.find(lowercase) == words.end()) {
                cout << word << " ";
                words.insert(lowercase);
            } else {
                cout << ". ";
            }
        }

        cout << "\n";
    }

    return 0;
}