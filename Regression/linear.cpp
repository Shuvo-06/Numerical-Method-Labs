#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<double> x(n), y(n);
    for (double &v : x) cin >> v;
    for (double &v : y) cin >> v;

    double xs = 0, ys = 0, xys = 0, xss = 0;
    for (int i = 0; i < n; i++) {
        xs += x[i];
        ys += y[i];
        xys += x[i] * y[i];
        xss += x[i] * x[i];
    }

    cout << "Table:\n";

    cout << setw(10) << "x : ";
    for (int i = 0; i < n; i++) cout << setw(10) << x[i] << " ";
    cout << setw(10) << "Sum = " << xs << "\n\n";

    cout << setw(10) << "y : ";
    for (int i = 0; i < n; i++) cout << setw(10) << y[i] << " ";
    cout << setw(10) << "Sum = " << ys << "\n\n";

    cout << setw(10) << "x^2 : ";
    for (int i = 0; i < n; i++) cout << setw(10) << x[i] * x[i] << " ";
    cout << setw(10) << "Sum = " << xss << "\n\n";

    cout << setw(10) << "xy : ";
    for (int i = 0; i < n; i++) cout << setw(10) << x[i] * y[i] << " ";
    cout << setw(10) << "Sum = " << xys << "\n\n";
    
    double a, b;
    b = (n * xys - xs * ys) / (n * xss - xs * xs);
    a = (ys - b * xs) / n;

    cout << fixed << setprecision(6);

    cout << "\nPolynomial:\n";
    cout << "f(x) = " << a;
    if (b >= 0) cout << " + " << b << "x";
    else cout << " - " << -b << "x";
    cout << '\n';

    double p;
    cout << "\nEnter x: ";
    cin >> p;

    cout << "f(" << p << ") = " << a + b * p << '\n';
}

/*
5
1 2 3 4 5
5 8 11 14 17

f(x) = 2.000000 + 3.000000x

f(10) = 32.000000
*/