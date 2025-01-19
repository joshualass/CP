#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

string encrypt(string key, string txt) {
    string s = "";
    for(int i = 0; i < txt.size(); i++){
        char c = txt[i];
        if('a' <= c && c <= 'z') s.push_back(c);
        if('A' <= c && c <= 'Z') s.push_back(c - ('A' - 'a'));
    }
    string res(s.size(), '.');
    vector<int> inc(key.size() + 1);
    for(int i = 0; i < key.size(); i++) inc[i] = key[i] - 'a' + 2;
    inc[key.size()] = 1;
    int aptr = 0;
    for(int i = 0; i < inc.size(); i++){
        int cinc = inc[i];
        if(i % 2 == 0) {
            int cnt = 0;
            for(int i = 0; i < res.size(); i++) {
                if(res[i] == '.') cnt ++;
                if(cnt == cinc) cnt = 0, res[i] = s[aptr ++];
            }
        }
        else {
            int cnt = 0;
            for(int i = res.size() - 1; i >= 0; i--){
                if(res[i] == '.') cnt ++;
                if(cnt == cinc) cnt = 0, res[i] = s[aptr ++];
            }
        }
    }
    return res;
}

string decrypt(string key, string s) {
    string rres(s.size(), '.');
    string res(s.size(), '.');
    vector<int> inc(key.size() + 1);
    for(int i = 0; i < key.size(); i++) inc[i] = key[i] - 'a' + 2;
    inc[key.size()] = 1;
    int aptr = 0;
    for(int i = 0; i < inc.size(); i++){
        int cinc = inc[i];
        if(i % 2 == 0) {
            int cnt = 0;
            for(int i = 0; i < res.size(); i++) {
                if(res[i] == '.') cnt ++;
                if(cnt == cinc) cnt = 0, rres[aptr ++] = s[i], res[i] = 'a';
            }
        }
        else {
            int cnt = 0;
            for(int i = res.size() - 1; i >= 0; i--){
                if(res[i] == '.') cnt ++;
                if(cnt == cinc) cnt = 0, rres[aptr ++] = s[i], res[i] = 'a';
            }
        }
    }
    return rres;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string op, key, txt;
    cin >> op >> key;
    getline(cin, txt);
    getline(cin, txt);
    cout << (op == "E"? encrypt(key, txt) : decrypt(key, txt)) << "\n";

    return 0;
}