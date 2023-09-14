#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    for(int i = 1; i <= t; i++) {
        int s; cin >> s;
        priority_queue<int> reds;
        priority_queue<int> blues;
        for(int b = 0; b < s; b++) {
            string line; cin >> line;
            if(line[line.size()-1] == 'B') {
                reds.push(stoi(line.substr(0,line.size()-1)));
            } else {
                blues.push(stoi(line.substr(0,line.size()-1)));
            }
        }
        int size = min(reds.size(), blues.size());
        int totalB = min(reds.size(), blues.size());
        int totalR = min(reds.size(), blues.size());
        int rL = 0;
        int bL = 0;
        while(totalB > 0) {
            rL += reds.top();
            reds.pop();
            totalB--;
        }
        while(totalR > 0) {
            bL += blues.top();
            blues.pop();
            totalR--;
        }
        cout << "Case #" << i << ": " << rL + bL - size * 2 << '\n';
    }    

    return 0;
}