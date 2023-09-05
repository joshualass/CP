#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool copy(string line) {
    if(line.length() % 2 == 1 || line.length() == 0) {
        return false;
    }
    for(int i = 0; i < line.length() / 2; i++) {
        if(line[i] != line[i + line.length() / 2]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string read;
    cin >> read;

    while(true) {
        if(copy(read)) {
            string bit;
            cout << "? flip" << endl;
            cin >> bit;
            string burn;
            for(int i = 0; i < read.size() / 2; i++) {
                cout << "? left" << endl;
                cin >> burn;
            }
            if(bit == burn) {
                break;
            } else {
                for(int i = 0; i < read.size() / 2; i++) {
                    cout << "? right" << endl;
                    cin >> burn;
                }
                read[read.size() - 1] = bit[0];
            }
        } else {
            string bit;
            cout << "? right" << endl;
            cin >> bit;
            read += bit;
        }
    }
   cout << "! " << read.size() / 2 << '\n';
    return 0;
}