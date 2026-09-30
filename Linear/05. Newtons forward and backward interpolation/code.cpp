#include <bits/stdc++.h>
using namespace std;

double forward_interpolation(vector<double> &t, vector<double> &s, double pos) {
    int n = t.size();
    double h = t[1] - t[0], u = (pos - t[0]) / h;

    vector<vector<double>> d(n, vector<double>(n));
    for (int i = 0; i < n; i++) d[i][0] = s[i];
    for (int j = 1; j < n; j++) for (int i = 0; i + j < n; i++)
        d[i][j] = d[i + 1][j - 1] - d[i][j - 1];

    double ans = s[0], up = 1, fact = 1;
    for (int j = 1; j < n; j++) {
        up *= u - (j - 1);
        fact *= j;
        ans += up * d[0][j] / fact;
    }

    return ans;
}

double backward_interpolation(vector<double> &t, vector<double> &s, double pos) {
    int n = t.size();
    double h = t[1] - t[0], u = (pos - t[n - 1]) / h;

    vector<vector<double>> d(n, vector<double>(n));
    for (int i = 0; i < n; i++) d[i][0] = s[i];
    for (int j = 1; j < n; j++) for (int i = 0; i + j < n; i++)
        d[i][j] = d[i + 1][j - 1] - d[i][j - 1];

    double ans = s.back(), up = 1, fact = 1;
    for (int j = 1; j < n; j++) {
        up *= u + (j - 1);
        fact *= j;
        ans += up / fact * d[n - j - 1][j];
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

    cout << fixed << setprecision(10);
    cout << "Forward: " << forward_interpolation(t, s, pos) << '\n';
    cout << "Backward: " << backward_interpolation(t, s, pos) << '\n';
}
