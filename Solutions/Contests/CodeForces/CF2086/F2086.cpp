#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
baaab

baaaba

baabaab 

babaaabb

babaaabba
babaaabab
-----|-----
babaaababb

bababaaabbb
bababababab

------|------
babababababb
bababbbababa

bababbbababaa
babababababab

bababbbababab
bababbabbabab

-------|-------
bababbabbababb
babababbbababb

babababbbababba
babababbbababab

babababbbababbb
babababbbbbabab


babababababbb
bababbbababab


bababbbbbabab
   
babaaabb
babaaabbb

After 3 iterations, let outside letter be the letter which is majority. 

Situations
More outside than inside, even outside parity
More outside than inside, odd outside parity
More inside than outside, even outside parity
More inside than outside, odd outside partiy




More inside letter, Even parity outside
bababaaa ... aaababab

If we get inside letter first, 
bababaaa ... aaabababa

If we get inside again, back to 
bababaaa ... aaababab
else, make center be outside letter 
bababaaa ... aabaa ... aaababab

                   |
babababa ... babbbbabbbbab ... abababab

                    |
babababa ... babbbbabbbbab ... ababababb
babababa ... bababbabbbbbb ... ababababb

babababa ... bababbabbbbbb ... ababababba
babababa ... bababbabbbbbb ... ababababba

babababa ... bababbabbbbbb ... ababababbb
babababa ... bababbbbbbbbb ... ababababab

babababa ... bababbbbbbbab ... ababababbb
bbbababa ... bababbbabbbab ... ababababbb

                     |
bbbababa ... bababbbabbbab ... ababababbba
bbbababa ... bababbbbbbbab ... abababababa

babababa ... bababbbbbbbbb ... abababababab

bbbababa ... bababbbabbbab ... ababababbba





prefs
                   |
babababa ... babbbbabbbbab ... abababab
ab
                    |
babababa ... bababbbbbbbab ... ababababab
ba
                    |
babababa ... bababbbbbbbab ... ababababab
aa
                    |
babababa ... bababbbabbbab ... ababababab
bb
                    |
babababa ... babbbbbabbbbb ... ababababab

a- objectives
babababa ... bababbbbbbbab ... ababababab
babababa ... bababbbabbbab ... ababababab
-------- ... -------|----- ... ----------
Then, to help both
babababa ... babbbbabbbbab ... ababababa
                1  2
babababa ... bababbbbbbbab ... ababababa

babababa ... bababbbbbbbab ... ababababab ok

babababa ... bababbbbbbbab ... ababababaa
                    1                   2
babababa ... bababbbabbbab ... ababababab ok

b- objectives
babababa ... bababbbbbbbab ... ababababab
babababa ... babbbbbabbbbb ... ababababab
-------- ... ---|---|---|- ... ----------
See if we can help both, but they differ a bit. 
babababa ... babbbbabbbbab ... ababababb
                   1                   2
babababa ... babbbbbbbbbab ... ababababa

babababa ... babbbbbbbbbab ... ababababaa
                1                       2
babababa ... bababbbbbbbab ... ababababab ok 

babababa ... babbbbbbbbbab ... ababababab
                    1   2
babababa ... babbbbbabbbbb ... ababababab ok

hardest case to prove works. this should be a correct setup of targ. 

bababababb
bababbbabab
bababababab

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto ispal = [&](string s) -> bool {
        int ok = 1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] != s[s.size() - i - 1]) ok = 0;
        }
        return ok;
    };

    string t = "";

    auto op = [&](int i, int j) -> void {
        if(i != -1) {
            swap(t[i], t[j]);
        }
        cout << i + 1 << " " << j + 1 << endl;
    };

    char out, in;

    auto get_targ = [&](int ocnt, int icnt) -> string {
        assert((ocnt + icnt) & 1);
        string f = "", b = "";
        while(ocnt >= 2 || icnt >= 2) {
            if(f.size() % 2 == 0) {
                if(ocnt >= 2) {
                    f.push_back(out);
                    ocnt -= 2;
                } else {
                    f.push_back(in);
                    icnt -= 2;
                }
            } else {
                if(icnt >= 2) {
                    f.push_back(in);
                    icnt -= 2;
                } else {
                    f.push_back(out);
                    ocnt -= 2;
                }
            }
        }
        b = f;
        reverse(b.begin(), b.end());
        if(ocnt) {
            f.push_back(out);
        } else {
            f.push_back(in);
        }
        return f + b;
    };

    auto cnt_diff = [](string a, string b) -> int {
        int res = 0;
        for(int i = 0; i < a.size(); i++) {
            if(a[i] != b[i]) res++;
        }
        return res;
    };

    while(1) {
        char c; cin >> c;
        if(c == '0') break;

        if(t.size() <= 2) {
            t.push_back(c);
            if(t.size() == 3) {
                if(!ispal(t)) {
                    int a, b;
                    for(int i = 0; i < 2; i++) {
                        for(int j = i + 1; j < 3; j++) {
                            swap(t[i], t[j]);
                            if(ispal(t)) {
                                a = i, b = j;
                            }
                            swap(t[i], t[j]);
                        }
                    }
                    op(a, b);
                } else {
                    op(-1, -1);
                }
                out = t[0];
                in = (out == 'a' ? 'b' : 'a');
            } else {
                op(-1,-1);
            }
        } else {

            t.push_back(c);

            if(t.size() % 2 == 0) {

                int oc = count(t.begin(), t.end(), out);
                int ic = count(t.begin(), t.end(), in);

                // cout << "current t : " << t << '\n';

                string to = get_targ(oc + 1, ic);
                string ti = get_targ(oc, ic + 1);

                // cout << "to : " << to << '\n';
                // cout << "tb : " << ti << '\n';

                int best_swap_diff = INT_MAX;
                int a, b; 
                for(int i = 0; i < t.size(); i++) {
                    for(int j = i; j < t.size(); j++) {
                        swap(t[i], t[j]);
                        int diffo = cnt_diff(to, t + out);
                        int diffi = cnt_diff(ti, t + in);
                        if(max(diffo, diffi) < best_swap_diff) {
                            best_swap_diff = max(diffo, diffi);
                            a = i;
                            b = j;
                        }
                        swap(t[i], t[j]);
                    }
                }
                if(a == b) {
                    a = -1;
                    b = -1;
                }

                op(a,b);

            } else {

                int oc = count(t.begin(), t.end(), out);
                int ic = count(t.begin(), t.end(), in);

                string targ = get_targ(oc, ic);

                int f = 0;
                int a, b; 

                for(int i = 0; i < t.size(); i++) {
                    for(int j = i; j < t.size(); j++) {
                        swap(t[i], t[j]);
                        if(t == targ) {
                            f = 1;
                            a = i;
                            b = j;
                        }
                        swap(t[i], t[j]);
                    }
                }

                assert(f);

                if(a == b) {
                    a = -1;
                    b = -1;
                }

                op(a,b);

            }

        }

        // cerr << "T : " << t << endl;
    }

    return 0;
}

/*


a
ab
abb
12
bab

baba
babab
bababa
  34
baabba
baabbab
  34
bababab

babababa
babababab

bababababb
     ^   ^
bababbbaba

bababbbabab

bababbbababb






*/