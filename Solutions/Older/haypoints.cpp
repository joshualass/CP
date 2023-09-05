#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, n;
    cin >> M >> n;

    map<string, int> m;

    for(int i = 0; i < M; i++) {
        string word;
        int value;
        cin >> word >> value;
        m[word] = value;
    }
    for(int i = 0; i < n; i++) {
        string word;
        cin >> word;
        int sum = 0;
        while(word != ".") {
            if(m.find(word) != m.end()) {
                sum += m[word];
            }
            cin >> word;
        }
        cout << sum << '\n';
    }

    return 0;
}