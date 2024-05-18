#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

set<int> getcnts1(string word, vector<string> &a) {
    vector<set<int>> v(word.size() + 1);
    v[0].insert(0);
    for(int i = 1; i <= word.size(); i++) {
        for(string tryword : a) {
            if(i - (int) tryword.size() >= 0 && tryword == word.substr(i-tryword.size(),tryword.size())) {
                for(int x : v[i-tryword.size()]) {
                    v[i].insert(x + 1);
                }
            }
        }
    }
    return v.back();
}

void recur(vector<set<int>> &getcnts, int i, int score, set<int> &found) {
    if(i == getcnts.size()) {
        found.insert(score);
        return;
    }
    for(int x : getcnts[i]) {
        recur(getcnts,i+1,score+x,found);
    }
}

set<int> getcnts1(vector<string> &a, string line) {
    stringstream ss(line);

    string word;
    // ss >> word;
    vector<set<int>> getcnts;
    while(!ss.eof()) {
        ss >> word;
        getcnts.push_back(getcnts1(word,a));
        // cout << "word : " << word << " s : " << getcnts.back() << '\n';
    }
    set<int> found;
    recur(getcnts,0,0,found);
    return found;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<string> a(n);
    for(string &x : a) cin >> x;
    cin.ignore();
    bool ok = 1;


    string line1;
    string line2;
    string line3;

    getline(cin,line1);
    getline(cin,line2);
    getline(cin,line3);
    // cout << "line3 : " << line3 << '\n';
    set<int> s1 = getcnts1(a,line1);
    set<int> s2 = getcnts1(a,line2);
    set<int> s3 = getcnts1(a,line3);

    // cout << "s1 : " << s1 << '\n';

    // cout << "s2 : " << s2 << '\n';
    
    // cout << "s3 : " << s3 << '\n';

    if(s1.count(5) && s2.count(7) && s3.count(5)) {
        cout << "haiku\n";
    } else {
        cout << "come back next year\n";
    }

    return 0;
}