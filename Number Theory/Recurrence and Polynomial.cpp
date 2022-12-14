//If there is a linear recurrence of order n , give it first 2n terms and it will
//find the linear recurrence, if you give some random numbers,result is useless
// look at examples
vector<ll> berlekampMassey(vector<ll> s) {
    ll n = sz(s), L = 0, m = 0;
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;

    ll b = 1;
    for(ll i=0;i<n;i++) { ++m;
        ll d = s[i] % MOD;
        for(ll j=1;j<L+1;j++) d = (d + C[j] * s[i - j]) % MOD;
        if (!d) continue;
        T = C; ll coef = d * power(b, MOD-2,MOD) % MOD;
        for(ll j=m;j<n;j++) C[j] = (C[j] - coef * B[j - m]) % MOD;
        if (2 * L > i) continue;
        L = i + 1 - L; B = T; b = d; m = 0;
    }

    C.resize(L + 1); C.erase(C.begin());
    for (ll& x : C) x = (MOD - x) % MOD;
    return C;
}
//{0, 1, 1, 2, 3, 5} {1, 1}, {0, 1, 1, 1, 0, -1} {1, 0, 1000000006}
//{0, 1, 423, 43, 0, 543} {402187050, 874879090, 632104496}


//For numerical precision, pick x[k] = c ∗ cos(k/(n − 1) ∗ π), k = 0 . . . n − 1.
vd interpolate(vd x, vd y, int n) {
    vd res(n), temp(n);
    rep(k,0,n-1) rep(i,k+1,n)
    y[i] = (y[i] - y[k]) / (x[i] - x[k]);
    double last = 0; temp[0] = 1;
    rep(k,0,n) rep(i,0,n) {
        res[i] += y[k] * temp[i];
        swap(last, temp[i]);
        temp[i] -= last * x[k];
    }
    return res;
}
//For dividing Polynomial, if the diff in deg is small or 1 of them is small,do normal div otherwise A*B.inverse(d1-d2+1);
poly inverse(int n) const {  // 1 / p(x) % x^n, O(nlogn)
    assert(a[0] != 0);//check a0 of polynmial
    poly ans{mint(1) / a[0]};//mod_xk(n) is first n terms
    for(int i = 1; i < n; i *= 2) {
        ans = (ans * mint(2) - ans * ans * mod_xk(2 * i)).mod_xk(2 * i);
    }
    return ans.mod_xk(n);
}
