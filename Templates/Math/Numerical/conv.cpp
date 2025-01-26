vector<double> conv(const vector<double>& a, const vector<double>& b) {
    if (a.empty() || b.empty()) return {};
    vector<double> res(a.size() + b.size() - 1);
    int L = 32 - __builtin_clz(res.size()), n = 1 << L;
    vector<complex<double>> in(n), out(n);
    copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i < b.size(); i++) 
        in[i].imag(b[i]);
    fft(in);
    for (complex<double>& x : in) 
        x *= x;
    for (int i = 0; i < n; i++) 
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i = 0; i < res.size(); i++) 
        res[i] = imag(out[i]) / (4 * n);
    return res;
}