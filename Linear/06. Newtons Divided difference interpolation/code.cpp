#include <bits/stdc++.h>
using namespace std;

double divided_difference(vector<double> &x, vector<double> &y, double pos) {
    int n = x.size();
    vector<vector<double>> d(n, vector<double>(n));

    for (int i = 0; i < n; i++) d[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i + j < n; i++)
            d[i][j] = (d[i + 1][j - 1] - d[i][j - 1]) / (x[i + j] - x[i]);

    double ans = d[0][0], product = 1;
    for (int j = 1; j < n; j++) {
        product *= pos - x[j - 1];
        ans += d[0][j] * product;
    }
    return ans;
}

int main() {
    int n;
    cin >> n;

    vector<double> x(n), y(n);
    for (auto &v : x) cin >> v;
    for (auto &v : y) cin >> v;

    double pos;
    cin >> pos;
    cout << fixed << setprecision(10);
    cout << divided_difference(x, y, pos) << '\n';
}