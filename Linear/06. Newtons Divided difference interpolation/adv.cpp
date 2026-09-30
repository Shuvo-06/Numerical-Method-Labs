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

vector<double> differentiate(vector<double> a) {
    vector<double> b;
    for (int i = 1; i < a.size(); i++) b.push_back(i * a[i]);
    return b;
}

vector<double> divided_difference_polynomial(vector<double> &x, vector<double> &y) {
    int n = x.size();
    vector<vector<double>> d(n, vector<double>(n));
    for (int i = 0; i < n; i++) d[i][0] = y[i];

    for (int j = 1; j < n; j++)
        for (int i = 0; i + j < n; i++)
            d[i][j] = (d[i + 1][j - 1] - d[i][j - 1]) / (x[i + j] - x[i]);

    vector<double> ans = {d[0][0]}, basis = {1};
    for (int j = 1; j < n; j++) {
        vector<double> factor = {-x[j - 1], 1};
        basis = multiply(basis, factor);
        ans = add(ans, scale(basis, d[0][j]));
    }
    return ans;
}

double evaluate(vector<double> p, double x) {
    double ans = 0;
    for (int i = p.size() - 1; i >= 0; i--) ans = ans * x + p[i];
    return ans;
}

void print_polynomial(vector<double> p) {
    cout << fixed << setprecision(6);
    for (int i = p.size() - 1; i >= 0; i--) {
        if (abs(p[i]) < 1e-9) continue;
        if (i != p.size() - 1 && p[i] > 0) cout << "+";
        if (i == 0) cout << p[i];
        else if (i == 1) cout << p[i] << "x";
        else cout << p[i] << "x^" << i;
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for (auto &v : x) cin >> v;
    for (auto &v : y) cin >> v;

    vector<double> p = divided_difference_polynomial(x, y);
    vector<double> dp = differentiate(p);

    cout << "Polynomial: "; print_polynomial(p);
    cout << "Derivative: "; print_polynomial(dp);

    double pos;
    cin >> pos;
    cout << "P(" << pos << ") = " << evaluate(p, pos) << '\n';
    cout << "P'(" << pos << ") = " << evaluate(dp, pos) << '\n';
}