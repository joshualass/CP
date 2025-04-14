#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     string s; cin >> s;
//     int n = s.size();

//     int c = 0;

//     auto check = [&](set<int> a) -> bool {
//         string t(n, '#');
//         for(int x : a) t[x] = '.';

//         int ok = 1;
//         for(int len = 1; len <= n; len += 2) {
//             for(int i = 0; i + len < n; i++) {
//                 if(t[i] == '.' && t[i + len] == '.') {
//                     ok = 0;
//                 }
//             }
//         }

//         for(int len = 2; len <= n; len += 2) {
//             for(int i = 0; i + len * 2 < n; i++) {
//                 if(t[i] == '.' && t[i+len] == '.' && t[i + len * 2] == '.') {
//                     ok = 0;
//                 }
//             }
//         }

//         c++;

//         return ok;

//     };

//     set<int> res;

//     // for(int i0 = 0; i0 < n; i0++) {
//     //     if(s[i0] == '#') continue;
//     //     for(int i1 = i0 + 1; i1 < n; i1++) {
//     //         if(s[i1] == '#') continue;
//     //         for(int i2 = i1 + 1; i2 < n; i2++) {
//     //             if(s[i2] == '#') continue;
//     //             for(int i3 = i2 + 1; i3 < n; i3++) {
//     //                 if(s[i3] == '#') continue;
//     //                 for(int i4 = i3 + 1; i4 < n; i4++) {
//     //                     if(s[i4] == '#') continue;
//     //                     for(int i5 = i4 + 1; i5 < n; i5++) {
//     //                         if(s[i5] == '#') continue;
//     //                         for(int i6 = i5 + 1; i6 < n; i6++) {
//     //                             if(s[i6] == '#') continue;
//     //                             if(check({i0, i1,i2, i3, i4, i5, i6})) {
//     //                                 res = {i0, i1, i2, i3, i4, i5, i6};
//     //                                 goto end;
//     //                             }
//     //                         }
//     //                     }
//     //                 }
//     //             }
//     //         }
//     //     }
//     // }

//     // for(int i0 = 0; i0 < n; i0++) {
//     //     if(s[i0] == '#') continue;
//     //     for(int i1 = i0 + 1; i1 < n; i1++) {
//     //         if(s[i1] == '#') continue;
//     //         for(int i2 = i1 + 1; i2 < n; i2++) {
//     //             if(s[i2] == '#') continue;
//     //             for(int i3 = i2 + 1; i3 < n; i3++) {
//     //                 if(s[i3] == '#') continue;
//     //                 for(int i4 = i3 + 1; i4 < n; i4++) {
//     //                     if(s[i4] == '#') continue;
//     //                     for(int i5 = i4 + 1; i5 < n; i5++) {
//     //                         if(s[i5] == '#') continue;
//     //                         if(check({i0, i1,i2, i3, i4, i5})) {
//     //                             res = {i0, i1, i2, i3, i4, i5};
//     //                             goto end;
//     //                         }
//     //                     }
//     //                 }
//     //             }
//     //         }
//     //     }
//     // }

//     for(int i0 = 0; i0 < n; i0++) {
//         if(s[i0] == '#') continue;
//         for(int i1 = i0 + 1; i1 < n; i1++) {
//             if(s[i1] == '#') continue;
//             for(int i2 = i1 + 1; i2 < n; i2++) {
//                 if(s[i2] == '#') continue;
//                 for(int i3 = i2 + 1; i3 < n; i3++) {
//                     if(s[i3] == '#') continue;
//                     for(int i4 = i3 + 1; i4 < n; i4++) {
//                         if(s[i4] == '#') continue;
//                         if(check({i0, i1,i2, i3, i4})) {
//                             res = {i0, i1, i2, i3, i4};
//                             goto end;
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     for(int i0 = 0; i0 < n; i0++) {
//         if(s[i0] == '#') continue;
//         for(int i1 = i0 + 1; i1 < n; i1++) {
//             if(s[i1] == '#') continue;
//             for(int i2 = i1 + 1; i2 < n; i2++) {
//                 if(s[i2] == '#') continue;
//                 for(int i3 = i2 + 1; i3 < n; i3++) {
//                     if(s[i3] == '#') continue;
//                     if(check({i0, i1,i2, i3})) {
//                         res = {i0, i1, i2, i3};
//                         goto end;
//                     }
//                 }
//             }
//         }
//     }

//     for(int i0 = 0; i0 < n; i0++) {
//         if(s[i0] == '#') continue;
//         for(int i1 = i0 + 1; i1 < n; i1++) {
//             if(s[i1] == '#') continue;
//             for(int i2 = i1 + 1; i2 < n; i2++) {
//                 if(s[i2] == '#') continue;
//                 if(check({i0, i1,i2})) {
//                     res = {i0, i1, i2};
//                     goto end;
//                 }
//             }
//         }
//     }

//     for(int i0 = 0; i0 < n; i0++) {
//         if(s[i0] == '#') continue;
//         for(int i1 = i0 + 1; i1 < n; i1++) {
//             if(s[i1] == '#') continue;
//             if(check({i0, i1})) {
//                 res = {i0, i1};
//                 goto end;
//             }
//         }
//     }

//     for(int i0 = 0; i0 < n; i0++) {
//         if(s[i0] == '#') continue;
//         if(check({i0})) {
//             res = {i0};
//             goto end;
//         }
//     }

// end:

//     for(int i = 0; i < n; i++) {
//         if(res.count(i) == 0) s[i] = '#';
//     }
//     cout << count(s.begin(), s.end(), '#') << '\n';
//     cout << s << '\n';

//     cout << "c : " << c << '\n';

//     return 0;
// }
