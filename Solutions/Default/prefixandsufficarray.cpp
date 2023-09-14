 #include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while(t-->0) {
        int l; cin >> l;
        string first = "";
        string second = "";
        for(int i = 0; i < l * 2 -2; i++) {
            string in; cin >> in;
            if(in.size() == l -1) {
                if(first == "") {
                    first = in;
                } else {
                    second = in;
                }
            }
        }
        bool flag1 = true;
        bool flag2 = true;
        // cout << first << " " << second << '\n';
        for(int i = 0; i < l - 1; i++) {
            if(first[i] != second[l-i-2]) {
                flag1 = false;
            }
        }
        for(int i = 0; i < l - 1; i++) {
            if(second[i] != first[l-i-2]) {
                flag2 = false;
            }
        }
        if(flag1 || flag2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}