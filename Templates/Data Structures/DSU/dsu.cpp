const int N = 2e5;
int dsu[N];
int depths[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}