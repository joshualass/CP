#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-->0) {

        int n;
        cin >> n;
        int total = 0;
        int most = 0;
        int mostindex = 0;
        bool tie = false;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            int num;
            cin >> num;
            total += num;
            if(num == most) {
                tie = true;
            } else if(num > most) {
                tie = false;
                mostindex = i + 1;
                most = num;
            }
        }

        if(tie) {
            cout << "no winner" << '\n';
        } else {
            if(most * 2 > total) {
                cout << "majority winner " << mostindex << '\n';
            } else {
                cout << "minority winner " << mostindex << '\n';
            }
        }

    }

    return 0;
}