//formula for catalan number - C = 1 / (n + 1) * (2n choose n)
ll catalan(ll n, ll MOD = 1e9 + 7) {
    return modDivide(modDivide(factorials[n*2], factorials[n] * factorials[n] % MOD, MOD), n + 1, MOD);
}