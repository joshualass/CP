#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// swag O(n) solution 
// 3 1 4 2 
//if we include 2, we cannot include 3 on the left
//include more elements to the right, we have to exclude elements to the left because 
//we fix left end point of operation, 

/*
first, and pretty clear to see is that you need to compute r[i] and l[i] which point to nearest right and left indices that will require an operation on this range of elements
It is not too hard to compute the total length of all the operations. We can do this by finding the number of operations on all subarrays for each element in the array pretty easily with the l and r arrays.
What's tricky is counting the total number of operations for all subarrays. To do this, we try counting the number of operations having a left endpoint of each element.

The condition for a subarray to have an operation with left endpoint on element i is that all elements left of i must be strictly less than all of those right of i, additionally, an element less than a[i] must be present to the right.

To calculate the ops, we will maintain a decreasing monotonic stack. It is decreasing because it is ordered by least to most limiting elements. The smallest elements don't impose as many restrictions as the larger elements.
decreasing storing elements to the right. 

The next problem is computing the index of the first element less than j right of a specific element i when calculating the ops as we don't know for each element j which element the element i will be. 

The element that will be a leftendpoint when looking at element j is the first element that is greater than a[j]. Essentially, we need first smallest k such that a[j] > a[k] and k > i. 
We can find i pretty easily as it is the first element after j that is greater than j. Then we can add j to the stack looking for min. 
Interesting thing happening here, we have a monotonic decreasing stack storing elements that are looking for a maximum, 
Once we find this maximum, we add push it to the stack of monotonic increasing elements that are looking for a min.
It is interesting how the second stack that is looking for mins is monotonic increasing. 

Discussed with Andwerp, ask him if you forget.

i, j, k. i is the left endpoint, j is a set of left ends of the array, k is fixed.
The elements before i are all less than i, and we look at them with a decreasing monotonic stack because the lower values are less limiting.

every j, i pair is precomputable, so just need to find j, i, k pairs. 

*/

void solve() {
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    stack<array<int,2>> s; 
    vector<int> r(n);//stores earliest index j such that j > i and a[j] < a[i]
    vector<int> l(n);//stores latest index j such that j < i and a[j] > a[i]

    for(int i = n - 1; i >= 0; i--) {
        r[i] = n;
        while(s.size() && s.top()[0] > a[i]) s.pop();
        if(s.size()) {
            r[i] = s.top()[1];
        }
        s.push({a[i],i});
    }

    while(s.size()) s.pop();

    for(int i = 0; i < n; i++) {
        l[i] = -1;
        while(s.size() && s.top()[0] < a[i]) s.pop();
        if(s.size()) {
            l[i] = s.top()[1];
        }
        s.push({a[i],i});
    }

    stack<int> lfmax, lfmin; //looking for max/min
    vector<int> rop(n, -1); //if -1, should never be used

    for(int i = 0; i < n; i++) {
        //first check mins
        while(lfmin.size() && a[i] < a[lfmin.top()]) {
            rop[lfmin.top()] = i;
            lfmin.pop();
        }
        //second check maxs
        while(lfmax.size() && a[i] > a[lfmax.top()]) {
            lfmin.push(lfmax.top());
            lfmax.pop();
        }
        lfmax.push(i);
    }

    while(lfmin.size()) {
        rop[lfmin.top()] = n;
        lfmin.pop();
    }

    cout << "a : " << a << '\n';
    cout << "l : " << l << '\n';
    cout << "r : " << r << '\n';
    cout << "rop : " << rop << '\n';

    while(s.size()) s.pop();

    //maintain that s is a monotonic decreasing stack. 

    ll ops = 0, totallength = 0;
    for(int i = 0; i < n; i++) {
        //for totallength of all ops done
        totallength += 1LL * (i + 1) * (n - i); //how many subarrays include element i
        totallength -= 1LL * (r[i] - i) * (i - l[i]); //subtract all subarrays which will not include this element in the range sort operation

        int cnt = 1;
        while(s.size() && a[s.top()[0]] < a[i]) {
            ops += 1LL * s.top()[1] * (rop[s.top()[0]] - r[i]);
            cnt += s.top()[1];
            s.pop();
        }
        ops += n - r[i];
        s.push({i, cnt});
        cout << "i : " << i << " cnt : " << cnt << '\n';
    }

    // cout << "total length : " << totallength << " ops : " << ops << '\n';
    cout << totallength - ops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}