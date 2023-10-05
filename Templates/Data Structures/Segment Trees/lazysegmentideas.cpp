/* -- ASSIGNMENT MODIFY, SUM QUERY -- */
function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return val;};
function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll rangeLength) -> ll{return val * rangeLength;};
function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return a + b;};
run_segt_tests(n, 0, 0, modifyElement, modifyRange, queryType);

/* -- INCREMENT MODIFY, SUM QUERY -- */
function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return src + val;};
function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll rangeLength) -> ll{return src + val * rangeLength;};
function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return a + b;};
SegtreeLazy tree(n, 0, 0, modifyElement, modifyRange, queryType);

/* -- INCREMENT MODIFY, MINIMUM QUERY -- */
function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return src + val;};
function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return min(a, b);};
run_segt_tests(n, 0, 1e9, modifyElement, modifyRange, queryType);

/* -- ASSIGNMENT MODIFY, MINIMUM QUERY -- */
function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return val;};
function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return val;};
function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return min(a, b);};
run_segt_tests(n, 0, 1e9, modifyElement, modifyRange, queryType);