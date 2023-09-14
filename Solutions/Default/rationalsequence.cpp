#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    int tc = 0;
    while(++tc<= t) {
        cout << tc << " ";
        
        int burn ;cin >> burn;
        string word; cin >> word;
        int index = word.find('/');
        int numerator = stoi(word.substr(0,index));
        int denominator = stoi(word.substr(index + 1));

        if(denominator == 1) {
            // cout << numerator + 1 << "/1\n";
            cout << "1/" << numerator + 1 << "\n";
            continue;
        }
        int upleft = numerator / denominator;
        numerator %= denominator;
        denominator -= numerator;
        numerator += denominator;
        denominator += numerator * upleft;
        cout << numerator << "/" << denominator << "\n";
    }

    return 0;
}