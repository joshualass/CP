#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    int res = 0;
    vector<int> v(24*60*60);

    auto parser = [&](string s, int mx) -> vector<int> {
        // cout << "s : " << s << " mx : " << mx << endl;
        vector<int> a;
        if(s[0] == '*') {
            for(int i = 0; i < mx; i++) a.push_back(i);
        } else {
            int p = 0;
            for(int i = 0; i < s.size(); i++) {
                if(s[i] == ',') {
                    string t = s.substr(p,i-p);
                    // cout << "tm : " << t << endl;
                    if(count(t.begin(),t.end(), '-')) {
                        for(int j = 0; j < t.size(); j++) {
                            if(t[j] == '-') {
                                for(int lo = stoi(t.substr(0,j)); lo <= stoi(t.substr(j+1)); lo++) {
                                    a.push_back(lo);
                                }
                            }
                        }
                    } else {
                        a.push_back(stoi(t));
                    }
                    p = i + 1;
                }
            }
            // cout << "p : " << p << '\n';
            string t = s.substr(p);
            // cout << "te : " << t << endl;
            if(count(t.begin(),t.end(), '-')) {
                for(int j = 0; j < t.size(); j++) {
                    if(t[j] == '-') {
                        for(int lo = stoi(t.substr(0,j)); lo <= stoi(t.substr(j+1)); lo++) {
                            a.push_back(lo);
                        }
                    }
                }
            } else {
                a.push_back(stoi(t));
            }
        }
        return a;
    };

    for(int i = 0; i < n; i++) {
        string h, m, s; cin >> h >> m >> s;
        vector<int> ah = parser(h, 24);
        vector<int> am = parser(m, 60);
        vector<int> as = parser(s, 60); 

        // cout << "ah : " << ah << '\n';
        // cout << "am : " << am << '\n';
        // cout << "as : " << as << '\n';

        for(int hr : ah) {
            for(int min : am) {
                for(int sec : as) {
                    res++;
                    v[hr*60*60+min*60+sec] = 1;
                }
            }
        }
    }

    cout << accumulate(v.begin(), v.end(), 0) << " " << res << '\n';

    return 0;
}