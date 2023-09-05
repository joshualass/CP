#include <bits/stdc++.h>
typedef unsigned long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<pair<ll,ll>> &x) {
    cout << " --- vector --- \n";
    for(pair<ll,ll> y : x) {
        cout << y.first << " " << y.second << " | ";
    }
    cout << "\n";
}

const int SIZE = 1000001;
const ll MOD = 1000000007;

// ll nexts[SIZE];
vector<ll> nexts(SIZE);
vector<pair<ll,ll>> problems(0);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, t; cin >> n >> t;
    ll a, b, c, to; cin >> a >> b >> c >> to;
    ll index = to;
    ll size = 1;
    cout << "1\n";
    while(nexts[index] != 0) {
        ll num = 1 + (a*index+b)%c;
        nexts[index] = num;
        index = num;
        size++;
    }
    cout << "2\n";
    ll cyclebegin = index;
    index = to;
    ll precycle = 0;
    cout << "cyclebegin: " << cyclebegin << " index: " << index << "\n";
    while(index != cyclebegin) {
        precycle++;
        problems.push_back({index,1});
        index = nexts[index];
    }
    cout << "size: " << size << " precycle: " << precycle << "\n";
    ll cyclesize = size - precycle;
    cout << "3\n";
    ll left = n - precycle;
    cout << left << " " << cyclesize << "3\n";
    ll cycleextras = left % cyclesize; //error why?
    cout << "3\n";
    ll cyclebase = left / cyclesize;
    cout << "cyclesize: " << cyclesize << " left: " << left << " cycleextras: " << cycleextras << " cyclebase: " << cyclebase << "\n";
    for(int i = 0; i < cyclesize; i++) {
        if(i < cycleextras) {
            problems.push_back({cyclebegin,cyclebase+1});
        } else {
            problems.push_back({cyclebegin,cyclebase});
        }
    }
    cout << "4\n";
    sort(problems.begin(),problems.end());
    printV(problems);
    ll totalproblems = 0;
    ll pref = 0;
    ll penalty = 0;
    for(int i = 0; i < problems.size(); i++) {
        ll maxprob = problems[i].second;
        if(pref + problems[i].second * problems[i].first > t) {
            maxprob = (t - pref) / problems[i].first;
        }
        if(maxprob == 0) {
            break;
        }
        ll addedpenalty = (((pref * maxprob)%MOD) + ((problems[i].first*(maxprob)%MOD)*(maxprob-1)/2)%MOD)%MOD;
        if(maxprob) {
            addedpenalty = problems[i].first;
        }
        totalproblems += maxprob;
        penalty += addedpenalty;
        penalty %= MOD;
        pref += maxprob * problems[i].first;
        pref %= MOD;
    }
    cout << totalproblems << " " << penalty << "\n";
    return 0;
}