#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    auto capitalize = [&](string s) -> string {
        string res = "";
        for(int i = 0; i < s.size(); i++) {
            if(s[i] >= 'a' && s[i] <= 'z') {
                res.push_back(s[i] - 'a' + 'A');
            } else if(s[i] >= 'A' && s[i] <= 'Z') {
                res.push_back(s[i] - 'A' + 'a');
            } else {
                res.push_back(s[i]);
            }
        }
        return res;
    };

    auto left_shift = [&](string s) -> string {
        string blah = "7890-=yuiop[]\\hjkl;'nm,./&*()_+YUIOP{}|HJKL:\"NM<>?";
        string tran = "67890-tyuiop[]ghjkl;bnm,.^&*()_TYUIOP{}GHJKL:BNM<>";  
        map<char,char> m;
        for(int i = 0; i < blah.size(); i++) {
            m[blah[i]] = tran[i];
        }
        string res = "";
        for(int i = 0; i < s.size(); i++) {
            if(m.count(s[i])) {
                res.push_back(m[s[i]]);
            } else {
                res.push_back(s[i]);
            }
        }
        return res;
    };

    auto right_shift = [&](string s) -> string {
        string blah = "`123456qwertasdfgzxcvb~!@#$%^QWERTASDFGZXCVB";
        string tran = "1234567wertysdfghxcvbn!@#$%^&WERTYSDFGHXCVBN";
        map<char,char> m;
        for(int i = 0; i < blah.size(); i++) {
            m[blah[i]] = tran[i];
        }
        string res = "";
        for(int i = 0; i < s.size(); i++) {
            if(m.count(s[i])) {
                res.push_back(m[s[i]]);
            } else {
                res.push_back(s[i]);
            }
        }
        return res;
    };


    auto check_missing = [&](string s, string t) -> bool {
        for(int i = 0; i < t.size(); i++) {
            if(s == (t.substr(0,i) + t.substr(i + 1))) return 1;
        }
        return 0;
    };

    string s; cin >> s;
    string cap = capitalize(s);
    string l = left_shift(s), r = right_shift(s);
    string L = capitalize(l), R = capitalize(r);

    // cout << "s : " << s << " cap : " << cap << " l : " << l << " L : " << L << " r : " << r << " R : " << R << '\n';

    set<string> good = {s,cap,l,L,r,R};

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        string t; cin >> t;
        bool found = 0;
        if(good.count(t)) found = 1;


        if(check_missing(t,s)) found = 1;
        if(check_missing(s,t)) found = 1;
        if(check_missing(t,cap)) found = 1;
        if(check_missing(cap,t)) found = 1;

        cout << (found ? "YES" : "NO") << '\n';
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     string s; cin >> s;

//     auto cap = [&](string s) -> string {
//         string c = "";
//         for(int i = 0; i < s.size(); i++) {
//             if(s[i] >= 'a' && s[i] <= 'z') {
//                 c.push_back(s[i] - 'a' + 'A');
//             } else if(s[i] >= 'A' && s[i] <= 'Z') {
//                 c.push_back(s[i] - 'A' + 'a');
//             } else {
//                 c.push_back(s[i]);
//             }
//         }
//         return c;
//     };   

//     auto shift_right = [&](string s) -> string {
//         string res = "";
//         for(int i = 0; i < s.size(); i++) {
//             switch(s[i]) {
//                 case '`' : res.push_back('1'); break;
//                 case '~' : res.push_back('!'); break;
//                 case '1' : res.push_back('2'); break;
//                 case '!' : res.push_back('@'); break;
//                 case '2' : res.push_back('3'); break;
//                 case '@' : res.push_back('#'); break;
//                 case '3' : res.push_back('4'); break;
//                 case '#' : res.push_back('$'); break;
//                 case '4' : res.push_back('5'); break;
//                 case '$' : res.push_back('%'); break;
//                 case '5' : res.push_back('6'); break;
//                 case '%' : res.push_back('^'); break;
//                 case '6' : res.push_back('7'); break;
//                 case '^' : res.push_back('&'); break;
//                 case 'q' : res.push_back('w'); break;
//                 case 'Q' : res.push_back('W'); break;
//                 case 'w' : res.push_back('e'); break;
//                 case 'W' : res.push_back('E'); break;
//                 case 'e' : res.push_back('r'); break;
//                 case 'E' : res.push_back('R'); break;
//                 case 'r' : res.push_back('t'); break;
//                 case 'R' : res.push_back('T'); break;
//                 case 't' : res.push_back('y'); break;
//                 case 'T' : res.push_back('Y'); break;
//                 case 'a' : res.push_back('s'); break;
//                 case 'A' : res.push_back('S'); break;
//                 case 's' : res.push_back('d'); break;
//                 case 'S' : res.push_back('D'); break;
//                 case 'd' : res.push_back('f'); break;
//                 case 'D' : res.push_back('F'); break;
//                 case 'f' : res.push_back('g'); break;
//                 case 'F' : res.push_back('G'); break;
//                 case 'g' : res.push_back('h'); break;
//                 case 'G' : res.push_back('H'); break;
//                 case 'z' : res.push_back('x'); break;
//                 case 'Z' : res.push_back('X'); break;
//                 case 'x' : res.push_back('c'); break;
//                 case 'X' : res.push_back('C'); break;
//                 case 'c' : res.push_back('v'); break;
//                 case 'C' : res.push_back('V'); break;
//                 case 'v' : res.push_back('b'); break;
//                 case 'V' : res.push_back('B'); break;
//                 case 'b' : res.push_back('n'); break;
//                 case 'B' : res.push_back('N'); break;
//                 default : res.push_back(s[i]);
//             }
//         }
//         return res;
//     };

//     auto shift_left = [&](string s) -> string {
//         string res = "";
//         for(int i = 0; i < s.size(); i++) {
//             switch(s[i]) {
//                 case '7' : res.push_back('6'); break;
//                 case '&' : res.push_back('^'); break;
//                 case '8' : res.push_back('7'); break;
//                 case '*' : res.push_back('&'); break;
//                 case '9' : res.push_back('8'); break;
//                 case '(' : res.push_back('*'); break;
//                 case '0' : res.push_back('9'); break;
//                 case ')' : res.push_back('('); break;
//                 case '-' : res.push_back('0'); break;
//                 case '_' : res.push_back(')'); break;
//                 case '=' : res.push_back('-'); break;
//                 case '+' : res.push_back('_'); break;
//                 case 'y' : res.push_back('t'); break;
//                 case 'Y' : res.push_back('T'); break;
//                 case 'u' : res.push_back('y'); break;
//                 case 'U' : res.push_back('Y'); break;
//                 case 'i' : res.push_back('u'); break;
//                 case 'I' : res.push_back('U'); break;
//                 case 'o' : res.push_back('i'); break;
//                 case 'O' : res.push_back('I'); break;
//                 case 'p' : res.push_back('o'); break;
//                 case 'P' : res.push_back('O'); break;
//                 case '[' : res.push_back('p'); break;
//                 case '{' : res.push_back('P'); break;
//                 case ']' : res.push_back('['); break;
//                 case '}' : res.push_back('{'); break;
//                 case '\\' : res.push_back(']'); break;
//                 case '|' : res.push_back('}'); break;
//                 case 'h' : res.push_back('g'); break;
//                 case 'H' : res.push_back('G'); break;
//                 case 'j' : res.push_back('h'); break;
//                 case 'J' : res.push_back('H'); break;
//                 case 'k' : res.push_back('j'); break;
//                 case 'K' : res.push_back('J'); break;
//                 case 'l' : res.push_back('k'); break;
//                 case 'L' : res.push_back('K'); break;
//                 case ';' : res.push_back('l'); break;
//                 case ':' : res.push_back('L'); break;
//                 case '\'' : res.push_back(';'); break;
//                 case '"' : res.push_back(':'); break;
//                 case 'n' : res.push_back('b'); break;
//                 case 'N' : res.push_back('B'); break;
//                 case 'm' : res.push_back('n'); break;
//                 case 'M' : res.push_back('N'); break;
//                 case ',' : res.push_back('m'); break;
//                 case '<' : res.push_back('M'); break;
//                 case '.' : res.push_back(','); break;
//                 case '>' : res.push_back('<'); break;
//                 case '/' : res.push_back('.'); break;
//                 case '?' : res.push_back('>'); break;
//                 default : res.push_back(s[i]);
//             }
//         }
//         return res;
//     };

//     auto can_insert = [&](string small, string large) -> bool {
//         for(int skip = 0; skip < large.size(); skip++) {
//             string t = large.substr(0,skip) + large.substr(skip + 1);
//             if(t == small) return 1;
//         }
//         return 0;
//     };

//     string l = shift_left(s), r = shift_right(s), c = cap(s);
//     string L = cap(l), R = cap(l);

//     set<string> shifts = {s, l, r, c, L, R};

//     // for(string shift : shifts) {
//     //     cout << "shift : " << shift << '\n';
//     // }

//     int q; cin >> q;
//     for(int i = 0; i < q; i++) {
//         string t; cin >> t;
//         bool f = 0;
//         if(shifts.count(t)) {
//             f = 1;
//         }
//         if(t.size() < s.size()) {
//             f |= can_insert(t, s);
//             f |= can_insert(t, c);
//         }
//         if(t.size() > s.size()) {
//             f |= can_insert(s, t);
//             f |= can_insert(c, t);
//         }
//         cout << (f ? "YES" : "NO") << '\n';
//     }

//     return 0;
// }