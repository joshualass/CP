//an intended solution is with segment tree, but this is also solvable with ordered statistics tree
//not easy to solve w/ a segment tree ... binary search in a similar manner that was used in josephusproblemii. 
//much harder to implement
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;

/*
order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero).
*/

typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ordered_set os;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        os.insert({i,num});
    }
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        cout << (*os.find_by_order(num)).second << " ";
        os.erase(os.find_by_order(num));
    }

    return 0;
}