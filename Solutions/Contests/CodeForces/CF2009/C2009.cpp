#include <bits/stdc++.h>

main() {

    int tc; std::cin >> tc;
    while(tc--) {
        int x, y, k; std::cin >> x >> y >> k;
        std::cout << std::max((x + k - 1) / k * 2 - 1, (y + k - 1) / k * 2) << '\n';
    }

}