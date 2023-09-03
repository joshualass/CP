#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        if(n % 2 == 0) {
            cout << "-1\n";
            continue;
        }
        string out = "";
        n--;
        n /= 2;
        int size = 0;
        while(n != 0) {
            size++;
            if(n % 2) {
                out = "2 " + out;
            } else {
                out = "1 " + out;
            }
            n /= 2;
        }
        cout << size << "\n" << out << "\n";
    }

    return 0;
}