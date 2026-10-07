#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, d;
    cin >> m;
    vector<double> x(m), y(m);
    for (double &v : x) cin >> v;
    for (double &v : y) cin >> v;

    cin >> d;
    vector<vector<double>> a(d + 1, vector<double>(d + 2));

    for (int i = 0; i <= d; i++) {
        for (int j = 0; j <= d; j++) {
            for (int k = 0; k < m; k++) a[i][j] += pow(x[k], i + j);
        }
        for (int k = 0; k < m; k++) a[i][d + 1] += y[k] * pow(x[k], i);
    }

    for (int i = 0; i <= d; i++) {
        int p = i;
        
        for (int j = i + 1; j <= d; j++) {
            if (abs(a[j][i]) > abs(a[p][i])) p = j;
        }

        swap(a[i], a[p]);

        for (int j = i + 1; j <= d; j++) {
            double r = a[j][i] / a[i][i];
            for (int k = i; k <= d + 1; k++) a[j][k] -= r * a[i][k];
        }
    }

    vector<double> c(d + 1);

    for (int i = d; i >= 0; i--) {
        c[i] = a[i][d + 1];
        for (int j = i + 1; j <= d; j++) c[i] -= a[i][j] * c[j];
        c[i] /= a[i][i];
    }

    cout << fixed << setprecision(6);

    cout << "\nTable:\n";
    cout << "x\tf(x)\n";
    for (int i = 0; i < m; i++) cout << x[i] << '\t' << y[i] << '\n';

    cout << "\nPolynomial:\n";
    cout << "f(x) = ";
    for (int i = d; i >= 0; i--) {
        if (i != d) {
            if (c[i] >= 0) cout << " + ";
            else cout << " - ";
        } 
        else if (c[i] < 0) cout << "-";

        cout << abs(c[i]);

        if (i >= 1) cout << "x";
        if (i >= 2) cout << "^" << i;
    }
    cout << '\n';

    double p;
    cout << "\nEnter x: ";
    cin >> p;
    double ans = 0;
    for (int i = 0; i <= d; i++) ans += c[i] * pow(p, i);
    cout << "f(" << p << ") = " << ans << '\n';
}