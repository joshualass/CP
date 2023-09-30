#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-->0) {
        int cnt;
        cin >> cnt;
        int index = 0;
        int sum = 0;
        int prev = cnt;
        bool flag = false;
        while(cnt != 0) {
            if(flag) {

            } else {
                
            }
            cout << "- " << (int(pow(2,index))) << "\n";
            cout.flush();
            if(cnt == prev - 1) {
                sum += pow(2,index);
                index++;
            } else {

            }

            prev = cnt;
            cin >> cnt;
        }


    }

    return 0;
}