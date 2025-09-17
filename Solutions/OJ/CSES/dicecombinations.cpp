#include <iostream>

const int MOD = 1e9 + 7;

int combo [1000001];

int main()
{
    
    int n; std::cin >> n;
    
    combo[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 6; j++) {
            if(i - j >= 0) {
                combo[i] = (combo[i] + combo[i-j]) % MOD;
            }
        }
    }
    
    std::cout << combo[n] << '\n';

    return 0;
}