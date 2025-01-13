/*

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;

    //build transformation matrix
    int posCnt = 3, stateCnt = 4;
    int numStates = power(stateCnt, posCnt);
    vector transform(numStates, vector<Z>(numStates));
    vector base(numStates, vector<Z>(numStates));
    for(int i = 0; i < numStates; i++) {
        base[i][i] = 1;
    }

    // from col
    // to row

    auto unhash = [&](int hash) -> vector<int> {
        vector<int> res;
        for(int i = 0; i < posCnt; i++) {
            res.push_back(hash % stateCnt);
            hash /= stateCnt;
        }
        return res;
    };

    auto hash = [&](vector<int> state) -> int {
        int res = 0;
        for(int i = posCnt - 1; i >= 0; i--) {
            res *= stateCnt;
            res += state[i];
        }
        return res;
    };

    for(int h = 0; h < numStates; h++) {
        vector<int> state = unhash(h);
        for(int pos = 0; pos < posCnt; pos++) {
            for(int type = 0; type < stateCnt; type++) {
                if(type == 3) {
                    swap(state[pos], type);
                    transform[hash(state)][h] = n - (3 - count(state.begin(), state.end(), 3));
                    swap(state[pos], type);
                } else {
                    if(count(state.begin(), state.end(), type) == 0) {
                        swap(state[pos], type);
                        transform[hash(state)][h] = 1;
                        swap(state[pos], type);
                    }
                }
            }
            for(int pos2 = pos + 1; pos2 < posCnt; pos2++) {
                swap(state[pos],state[pos2]);
                transform[hash(state)][h] = 1;
                swap(state[pos],state[pos2]);
            }
            transform[h][h] = (n - 3) * (n - 4) / 2;
        }
    }

    Matrix<Z> tmat(transform);
    Matrix<Z> bmat(base);
    matpow(bmat, tmat, m);

    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
    }
    Z res = 0;

    return 0;
}

*/