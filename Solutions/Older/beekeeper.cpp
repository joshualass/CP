#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    while(n != 0) {
        string most = "";
        int m = -1;
        for(int i = 0; i < n; i++) {
            string in; cin >> in;
            int count = 0;
            for(int i = 0; i < in.size() - 1; i++) {
                if(in[i] == in[i+1] && (in[i] == 'a' || in[i] == 'e' || in[i] == 'o' || in[i] == 'u' || in[i] == 'i' || in[i] == 'y')) {
                    count++;
                }
            }
            if(count > m) {
                m = count;
                most = in;
            }
        }   
        cout << most << '\n';

        cin >> n;
    }

    return 0;
}