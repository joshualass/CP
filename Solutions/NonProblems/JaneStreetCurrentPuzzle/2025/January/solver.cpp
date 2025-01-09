#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {

    clock_t tStart = clock();

    set<int> need = {0,2,5};
    vector<set<int>> good(10);
    
    for(int exclude = 0; exclude <= 9; exclude++) {
        if(need.count(exclude) == 0) {
            vector<int> perm;
            for(int i = 0; i <= 9; i++) {
                if(i != exclude) {
                    perm.push_back(i);
                }
            }
            for(int p = 0; p < 362880; p++) {
                int res = 0;
                for(int i = 0; i < 10; i++) {
                    res *= 10;
                    res += perm[i];
                }
                // good[res] = 1;
                good[exclude].insert(res);
                next_permutation(perm.begin(), perm.end());
            }
        }
    }

    printf("Time taken find good numbers: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    //this step can take a while. 
    /*

    set<int> gcd_candidates;

    for(int g = 99'999'999; g; g--) {
        if(__builtin_popcount(g) == 1) {
            cout << "time taken to reach g : " << g << " time : " << (double)(clock() - tStart)/CLOCKS_PER_SEC << '\n';
        }
        if(g % 2 == 0 || g % 5 == 0) continue;
        int t = g;
        int c = 0;
        while(t < 1'000'000'000) {
            if(good.count(t)) {
                c++;
                if(c == 10) {
                    break;
                }
            }
            t += g;
        }
        if(c == 10) {
            gcd_candidates.insert(g);
        }
    }

    cout << gcd_candidates.size() << '\n';

    printf("Time taken find gcd candidates: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    //Time taken find gcd candidates: 976.16s. computer diff. 
    //there are 35538 candidates! bruteforce them we can try?

    for(int candidate : gcd_candidates) {
        cout << candidate << '\n';
    }

    */

   /*

    int gcd_candidate_count; cin >> gcd_candidate_count;
    vector<int> gcd_candidates(gcd_candidate_count);
    for(int &x : gcd_candidates) cin >> x;

    //idk what i was doing with this prune, but it helps. 
    vector<int> pruned_candidates;

    for(int gcd_candidate : gcd_candidates) {
    // int gcd_candidate = 1;
        int t = gcd_candidate;
        array<array<int,10>,9> found = {};
        int c = 0;
        while(t < 1'000'000'000) {
            if(good.count(t)) {
                int tt = t;
                for(int i = 0; i < 9; i++) {
                    if(found[i][tt % 10] == 0) {
                        c++;
                        found[i][tt % 10] = 1;
                        if(c == 81) t = 1'000'000'000;
                    }
                    tt /= 10;
                }
            }
            t += gcd_candidate;
        }
        if(c == 81) {
            pruned_candidates.push_back(gcd_candidate);
        }
    }

    printf("Time taken find pruned candidates: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    cout << pruned_candidates.size() << '\n';
    for(int pc : pruned_candidates) cout << pc << '\n';

   */


    /*
    Time taken find pruned candidates: 532.37s
    8613
     */

    // cout << "mih0" << endl;

    int gcd_candidate_count; cin >> gcd_candidate_count;
    vector<int> gcd_candidates(gcd_candidate_count);
    for(int &x : gcd_candidates) cin >> x;

    // cout << "make it here one" << endl;

    //prune candidates by ensuring that it's possible for eaach digit to be in each position
    vector<int> pruned_candidates;

    for(int gcd_candidate : gcd_candidates) {
        // cout << "starting gcd cand : " << gcd_candidate << endl;
        int ok = 0;
        for(int exclude = 0; exclude <= 9; exclude++) {
            array<array<int,10>,9> found = {};
            int c = 0;
            for(int t : good[exclude]) {
                if(t % gcd_candidate == 0) {
                    int tt = t;
                    for(int i = 0; i < 9; i++) {
                        if(found[i][tt % 10] == 0) {
                            c++;
                            found[i][tt % 10] = 1;
                            if(c == 81) {
                                goto endloop;
                            }
                        }
                        tt /= 10;
                    }
                }
            }
            endloop:

            if(c == 81) {
                ok = 1;
                break;
            }
        }
        if(ok) {
            pruned_candidates.push_back(gcd_candidate);
        }
        cout << "cand : " << gcd_candidate << " done" << endl;
    }

    printf("Time taken find pruned candidates: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    cout << pruned_candidates.size() << '\n';
    for(int pc : pruned_candidates) cout << pc << '\n';

    return 0;
}