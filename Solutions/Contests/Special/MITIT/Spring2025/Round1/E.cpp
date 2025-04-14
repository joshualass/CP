#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

0
000111 W
1
001011 L
2
NOT
001011 
BUT
XX1XXX 
XXX0XX 

XX01XX
010101

observations

we see that any XX1XXX and any XXX0XX is bad, when the rest of the string is unsorted somehow
suppose then that 01 is sorted, then we consider the subproblem excluding the inner 01
we can also exlcude the outer subproblem 0 ... 1 as any op doesn't affect the elements. 

We will try an op that sorts up to the first inner pair and make it 100000111110 . make first non 01 into 10, which is bad. 

not too bad for nim i think

*/

void solve() {

    string s; cin >> s;

    auto get_move = [](string s) -> vector<int> {
        
        int oc = count(s.begin(), s.end(), '1'), zc = count(s.begin(), s.end(), '0');
        int n = s.size();
        int stop = 0, start = n;
        for(int i = zc - 1, j = zc; i >= 0, j < n; i--, j++) {
            if(s[i] != '0' || s[j] != '1') {
                stop = i + 1, start = j;
                if(s[i] == '1') stop--;
                if(s[j] == '0') start++;
                break;
            }
        }

        vector<int> res;
        vector<char> check;
        for(int i = 0; i < stop; i++) {
            res.push_back(i);
            check.push_back(s[i]);
        }

        for(int i = start; i < n; i++) {
            res.push_back(i);
            check.push_back(s[i]);
        }

        if(is_sorted(check.begin(), check.end())) res.clear();
        return res;

    };

    if(get_move(s).size() == 0) {
        cout << "Second" << endl;
        cin >> s;
    } else {
        cout << "First" << endl;
    }

    while(!is_sorted(s.begin(), s.end())) {
        vector<int> op = get_move(s);
        cout << op.size();
        for(int x : op) cout << " " << x + 1;
        cout << endl;
        cin >> s;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}