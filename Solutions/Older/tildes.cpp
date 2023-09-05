#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> points(1000001);
vector<int> sizes(1000001);
vector<int> elements(1000001,1);

int find(int index) {
    if (points[index] == index) {
        return index;
    } else {
        points[index] = find(points[index]);
        return points[index];
    }
}

void unify(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) { //they are already unified!
        return;
    }
    if(sizes[a] == sizes[b]) {
        elements[a] += elements[b];        
        points[b] = a;
        sizes[a]++;
    } else if(sizes[a] < sizes[b]) {
        elements[b] += elements[a];
        points[a] = b;
    } else {
        elements[a] += elements[b];
        points[b] = a;
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= 1000000; i++) {
        points[i] = i;
    }

    for(int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if(c == 't') {
            int a, b;
            cin >> a >> b;
            unify(a,b);
        } else {
            int a;
            cin >> a;
            cout << elements[find(a)] << '\n';
        }
    }

    // for(int i = 0; i < 15; i++) {
    //     cout << points[i] << ' ';
    // }
    // cout << '\n';
    // for(int i = 0; i < 15; i++) {
    //     cout << sizes[i] << ' ';
    // }
    // cout << '\n';
    // for(int i = 0; i < 15; i++) {
    //     cout << elements[i] << ' ';
    // }
    // cout << '\n';


    return 0;
}