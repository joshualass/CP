#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    while(N-->0) {
        int L;
        cin >> L;
        vector<int> odds(0);
        vector<int> evens(0);

        for(int i = 1; i <= L; i++) {
            int num;
            cin >> num;
            if(num % 2 == 0) {
                evens.push_back(i);
            } else {
                odds.push_back(i);
            }
        
        }
        if(odds.size() >= 3) {
            cout << "YES" << "\n";
            cout << odds[0] << " " << odds[1] << " " << odds[2] << "\n";
        } else if(odds.size() >= 1 && evens.size() >= 2) {
            cout << "YES" << "\n";
            cout << odds[0] << " " << evens[0] << " " << evens[1] << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }

    return 0;
}