Z catalan(ll n) {
    return fact[n*2] * inv_fact[n] * inv_fact[n + 1];
}