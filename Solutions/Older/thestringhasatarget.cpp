#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        string word; cin >> word;
        int index = -1;
        int least = 'z' + 1;
        for(int i = n-1; i >= 0;i--) {
            if(word[i] < least) {
                least = word[i];
                index = i;
            }
        }
        
        cout << word.substr(index,1) + word.substr(0,index) + word.substr(index + 1, n - index - 1) << "\n";

        // char least = 'z' + 1;
        // int index = -1;
        // char first = word[0];
        // bool same = true;
        // for(int i = 1; i < n; i++) {
        //     if(word[i] != word[i-1]) {
        //         same = false;
        //     }
        //     if(!same) {
        //         if(word[i] < least) {
        //             least = word[i];
        //             index = i;
        //         }
        //     }

        //     // string test = word.substr(i,1) + word.substr(0,i) + word.substr(i + 1, n - i - 1);
        //     // if(i == 0) {
        //     //     best = test;
        //     // } else if(test < best) {
        //     //     best = test;
        //     // }
        // }
        // if(least <= first) {
            // cout << word.substr(index,1) + word.substr(0,index) + word.substr(index + 1, n - index - 1) << "\n";
        // } else {
        //     cout << word << "\n";
        // }
    }

    return 0;
}