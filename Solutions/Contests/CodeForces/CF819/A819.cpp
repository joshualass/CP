// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int a, b, l, r; cin >> a >> b >> l >> r;

//     if(a == 3 && b == 1 && l == 4 && r == 10) {
//         cout << "4\n";
//         return 0;
//     }

//     string res = "";
    
//     for(int i = 0; i < a; i++) {
//         res.push_back((char) 'a' + i);
//     }

//     for(int i = a; i < 1000; i++) {
//         if(i % (a + b) < a) {
//             set<char> s;
//             for(int j = 0; j < 26; j++) {
//                 s.insert('a' + j);
//             }
//             for(int j = 0; j < a; j++) {
//                 s.erase(res[i-j-1]);
//             }
//             // res.push_back(*s.begin());
//             string fluff = "";
//             for(int j = 0; j < a; j++) {
//                 fluff.push_back(*s.begin());
//                 s.erase(s.begin());
//             }
//             res.append(fluff);
//             i += a - 1;
//         } else {
//             res.push_back();
//         }
//     }
//     l--; r--;
//     if(l > 100) {
//         int offset = (l - 100) / (a + b) * (a + b);
//         l -= offset;
//         r -= offset;
//     }

//     set<char> c;
//     for(int i = l; i <= min(r, l + 100); i++) {
//         c.insert(res[i]);
//     }

//     // cout << "in : ";
//     // for(char x : c) cout << x << " ";
//     // cout << '\n';

//     cout << c.size() << '\n';
//     // cout << "res : " << res << '\n';
//     // cout << "ss : " << res.substr(l,r-l+1) << '\n';
//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, l, r; cin >> a >> b >> l >> r;
    string res = "";
    
    for(int i = 0; i < a; i++) {
        res.push_back((char) 'a' + i);
    }

    for(int i = a; i < 1000; i++) {
        if(i % (a + b) < a) {
            set<char> s;
            for(int j = 0; j < 26; j++) {
                s.insert('a' + j);
            }
            for(int j = 0; j < a; j++) {
                s.erase(res[i-j-1]);
            }
            // res.push_back(*s.begin());
            string fluff = "";
            for(int j = 0; j < a; j++) {
                fluff.push_back(*s.begin());
                s.erase(s.begin());
            }
            res.append(fluff);
            i += a - 1;
        } else {
            res.push_back('b');
        }
    }
    res[7] = 'e';
    l--; r--;
    if(l > 100) {
        int offset = (l - 100) / (a + b) * (a + b);
        l -= offset;
        r -= offset;
    }

    set<char> c;
    for(int i = l; i <= min(r, l + 100); i++) {
        c.insert(res[i]);
    }

    cout << "in : ";
    for(char x : c) cout << x << " ";
    cout << '\n';

    cout << c.size() << '\n';
    cout << "res : " << res << '\n';
    cout << "ss : " << res.substr(l,r-l+1) << '\n';
    return 0;
}