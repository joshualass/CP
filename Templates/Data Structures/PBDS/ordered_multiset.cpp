#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type,
             less<pair<int, int> >, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset; //able to 