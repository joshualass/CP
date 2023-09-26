const int N = 1e5;
int n;
int t[2 * N];

void build() {
    for (int i = n - 1; i > 0; --i) {
        t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
}

void modify(int p, int value) {
    p += n;
    t[p] = value;
    while(p > 1) {
        t[p / 2] = max(t[p], t[p ^ 1]);
        p /= 2;
    }
}

int query(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    while(l < r) {
        if (l % 2 == 1) {
            ans = max(ans,t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            ans = max(ans, t[r]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}