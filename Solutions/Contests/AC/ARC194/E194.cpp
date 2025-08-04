#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

X - 2, Y - 1

000111001 - START
 _____ _
011000011 - GOAL


000111001 - START
000100101
 ___
011011001
    ___
011000101
    ___
011011001
 ___
000111001

011000011 - GOAL

maybe solve with a stack
does greedy work?

If characters are matching, is there any reason to do an operation on these elements?
doesn't seem like it. 
nope. not hard after looking at example
00111. if we move the 00's, we won't really be able to use them. 

then, realize that these operations are reversible and we should try to find a canonical form for both of these strings
let's try making the canonical form be the lexicographically smallest string possible from these strings. 
how can we obtain this?

0c - 2, 1c - 1
000111001
000110011
000100111
000001111



*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}
