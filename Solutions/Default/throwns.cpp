#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    stack<int> s;
    int pos = 0;
    s.push(0);

    for(int i = 0; i < k; i++) {
        string wrd;cin >> wrd;
        // cout << pos << "\n";
        if(wrd == "undo") {
            int times; cin >> times;
            for(int i = 0; i < times; i++) {
                s.pop();
            }
            pos = s.top();
        } else {
            int move = stoi(wrd) % n;
            // cout << "word: " << wrd << " move: " << move << "\n";
            int newPos = pos + move;
            while(newPos >= n) {
                newPos -= n;
            } 
            while(newPos < 0) {
                newPos += n;
            }
            pos = newPos;
            s.push(pos);
        }
    }
    cout << pos << "\n";
    return 0;
}