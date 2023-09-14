#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        set<int> s;
        for(int i = 1; i <= n; i++) {
            s.insert(i);
        }
        
        for(int i = 0; i < n; i++) { 
            int num; cin >> num;
            int add = 0;
            if(num == *(s.begin())) {
                add = 1;
            }
            cout << (*(s.begin()+1)) << " ";
            s.erase((*(s.begin()+1)));
        }
        cout<< '\n';
    }

    return 0;
}