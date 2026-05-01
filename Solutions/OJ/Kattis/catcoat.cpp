#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string male, female;
    getline(cin, male);
    getline(cin, female);

    string m, f;

    auto getcat = [&](string male) -> string {
        
    };

    if(male == "Black") {
        m = "ooB-D-";
    } else if(male == "Blue") {
        m = "ooB-dd";
    } else if(male == "Chocolate") {
        m = "oobbD-";
    } else if(male == "Lilac") {

        gm = {0, 0, 1, -1, 0, 0};
    }

    switch(male) {
        case "Black" : {}
    }

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// struct cat {
//     int ismale;
//     array<int,2> black, red, dilute;

//     cat() {}
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     string female, male;
//     getline(cin, female);
//     getline(cin, male);

//     cat curmale;
//     cat curfemale;

//     map<string,int> cats;

//     auto add_color = [&](cat c) -> void {

//     };

//     set<string> red = {

//     }

//     set<string> black_cats = {
//         "Black", "Blue", "Chocolate", "Lilac"
//     };

//     set<string> partial_cats = {
//         "Black-Red Tortie", "Blue-Cream Tortie", "Chocolate-Red Tortie", "Lilac-Cream Tortie"
//     };

//     auto dfs = [&](auto self, int cur) -> void {
//         if(cur == 0) {
//             //red is dominant
//             if(black_cats.count(male) == 0) {
//                 curmale.red = {1, 1};
//             } else {
//                 curmale.red = {0, 0};
//             }
//             self(self, cur + 1);
//         } else if(cur == 1) {
//             //red is dominant
//             if(black_cats.count(male) == 0) {
//                 for(int i = 0; i < 2; i++) {
//                     for(int = 0; j < 2; j++) {
//                         curmale.black = {i, j};
//                         self(self, cur + 1);
//                     }
//                 }
//             } else {
//                 if(male == "Black" || male == "Blue") {
//                     for(int i = 0; i < 2; i++) {
//                         curmale.black = {1, i};
//                         self(self, cur + 1);
//                     }
//                 } else {
//                     curmale.black = {0, 0};
//                     self(self, cur + 1);
//                 }
//             }
//         } else if(cur == 2) {
//             //red is dominant
//             if(black_cats.count(male) == 0) {
//                 if(male == "Red") {
//                     for(int i = 0; i < 2; i++) {
//                         curmale.dilute = {1, i};
//                         self(self, cur + 1);
//                     }
//                 } else {
//                     curmale.dilute = {0, 0};
//                     self(self, cur + 1);
//                 }
//             } else {
//                 if(male == "Black" || male == "Chocolate") {
//                     for(int i = 0; i < 2; i++) {
//                         curmale.dilute = {1, i};
//                         self(self, cur + 1);
//                     }
//                 } else {
//                     curmale.dilute = {0, 0};
//                     self(self, cur + 1);
//                 }
//             }
//         } else if(cur == 3) {
//             if(partial_cats.count(female)) {
//                 curfemale.red = {1, 0};
//                 self(self, cur + 1);
//             } else if(black_cats.count(female)) {
//                 curfemale.red = {0, 0};
//             } else {
//                 curfemale.red = {1, 1};
//             }
//         } else if(cur == 4) {
            


//         } else if(cur == 5) {

//         } else if(cur == 6) {

//         }
//     };

//     return 0;
// }
