#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
How large of a set of lengths exists such that they do not form a non-degenerate triangle? Just look at the fibonacci sequence. 
Using this, we can see that if the set is larger than or equal to 48, it will always be possible. 
Otherwise, we observe that 2 sides of each of the triangles should be adjacent to each other. Using this, we can iterate over all pairs of adjacent lengths in sorted order
and seeing if it is possible to find 2 third side lengths that do not intersect with the other side lengths. This takes length ^ 2 per query.
This can be done linear time by observing that the third length of the triangle should also be near the first 2 sides. 
*/

vector<int> forpainorforglory(47);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        if(r - l > 47) {
            cout << "YES\n";
        } else {
            for(int j = 0; j < r - l; j++) {
                forpainorforglory[j] = a[j + l];
            }
            sort(forpainorforglory.begin(), forpainorforglory.begin() + r - l);
            
            vector<array<int,2>> bests(r - l - 1, {INT_MAX,0});
            for(int j = 0; j < r - l - 1; j++) {
                int diff = forpainorforglory[j + 1] - forpainorforglory[j];
                int sum = forpainorforglory[j] + forpainorforglory[j + 1];
                for(int k = 0; k < r - l; k++) {
                    if(forpainorforglory[k] > diff && forpainorforglory[k] < sum) {
                        bests[j][0] = min(bests[j][0], k);
                        bests[j][1] = k + 1;
                    }
                }
            }

            bool found = 0;

            for(int lo = 0; lo < r - l - 1 && !found; lo++) {
                for(int hi = lo + 2; hi < r - l - 1 && !found; hi++) {
                    bool look = 0;
                    int lopos = -1;
                    bool hiok = 0;
                    int hipos = -1;
                    for(int j = bests[lo][0]; j < bests[lo][1]; j++) {
                        if(j != lo && j != lo + 1 && j != hi && j != hi + 1) {
                            if(lopos == -1) {
                                lopos = j;
                            } else {
                                look = 1;
                                break;
                            }
                        }
                    }
                    for(int j = bests[hi][0]; j < bests[hi][1]; j++) {
                        if(j != lo && j != lo + 1 && j != hi && j != hi + 1) {
                            if(hipos == -1) {
                                hipos = j;
                            } else {
                                hiok = 1;
                                break;
                            }
                        }
                    }

                    if(look && hiok) {
                        found = 1;
                    } else if(look) {
                        if(hipos != -1) {
                            found = 1;
                        }
                    } else if(hiok) {
                        if(lopos != -1) {
                            found = 1;
                        }
                    } else {
                        if(lopos != -1 && hipos != -1 && lopos != hipos) {
                            found = 1;
                        }
                    }
                }
            }

            cout << (found ? "YES" : "NO") << '\n';
            
        }
    }

    return 0;
}