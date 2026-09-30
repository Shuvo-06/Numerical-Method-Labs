#include <bits/stdc++.h>
using namespace std;

vector<double> add(vector<double> a, vector<double> b) {
    int n = max(a.size(), b.size());
    vector<double> c(n);
    for (int i = 0; i < n; i++) {
        if (i < a.size()) c[i] += a[i];
        if (i < b.size()) c[i] += b[i];
    }
    return c;
}

vector<double> multiply(vector<double> a, vector<double> b) {
    vector<double> c(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++) for (int j = 0; j < b.size(); j++)
        c[i + j] += a[i] * b[j];
    return c;
}

vector<double> scale(vector<double> a, double k) {
    for (double &x : a) x *= k;
    return a;
}

vector<double> forward_polynomial(vector<double> &t, vector<double> &s) {
    int n = t.size();
    double h = t[1] - t[0];

    vector<vector<double>> d(n, vector<double>(n));
    for (int i = 0; i < n; i++) d[i][0] = s[i];
    for (int j = 1; j < n; j++) for (int i = 0; i + j < n; i++)
        d[i][j] = d[i + 1][j - 1] - d[i][j - 1];


    vector<double> ans = {s[0]}, basis = {1};
    double fact = 1;
    for (int k = 1; k < n; k++) {
        fact *= k;
        vector<double> factor = {-(t[0] + (k - 1) * h) / h, 1.0 / h};
        basis = multiply(basis, factor);
        ans = add(ans, scale(basis, d[0][k] / fact));
    }

    return ans;
}

vector<double> backward_polynomial(vector<double> &t, vector<double> &s) {
    int n = t.size();
    double h = t[1] - t[0];

    vector<vector<double>> d(n, vector<double>(n));
    for (int i = 0; i < n; i++) d[i][0] = s[i];
    for (int j = 1; j < n; j++) for (int i = 0; i + j < n; i++)
        d[i][j] = d[i + 1][j - 1] - d[i][j - 1];

    vector<double> ans = {s.back()}, basis = {1};
    double fact = 1;
    for (int k = 1; k < n; k++) {
        fact *= k;
        vector<double> factor = {-(t[n - 1] - (k - 1) * h) / h, 1.0 / h};
        basis = multiply(basis, factor);
        ans = add(ans, scale(basis, d[n - k - 1][k] / fact));
    }

    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<double> t(n), s(n);
    for (auto &x : t) cin >> x;
    for (auto &x : s) cin >> x;

    double pos;
    cin >> pos;
    forward_interpolation(t, s, pos);
    backward_interpolation(t, s, pos);
}
