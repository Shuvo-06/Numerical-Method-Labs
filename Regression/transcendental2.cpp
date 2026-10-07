#include <bits/stdc++.h>
using namespace std;

// y = a * b ^ x
// lny = ln(a) + x * ln(b)

int main() {
    int n;
    cin >> n;
    vector <double> x(n), y(n);
    for (auto &v : x) cin >> v;
    for (auto &v : y) cin >> v; 

    double xs = 0, ys = 0, xys = 0, xxs = 0;
    for (int i = 0 ;i < n; i++) {
        xs += x[i];
        ys += log(y[i]);
        xys += x[i] * log(y[i]);
        xxs += x[i] * x[i];
    }

    cout << fixed << setprecision(6);
    cout << "Table : \n";
    cout << setw(10) << "x : " << setw(10) << "y : " << setw(10) << "ln(x) : " << setw(10) << "ln(y) : " << setw(10) << "xy : " << setw(10) << "x^2 : " << "\n";
    for (int i = 0; i < n; i++) {
        cout << setw(10) << x[i] << " ";
        cout << setw(10) << y[i] << " ";
        cout << setw(10) << log(x[i]) << " ";
        cout << setw(10) << log(y[i]) << " ";
        cout << setw(10) << log(x[i]) * log(y[i]) << " ";
        cout << setw(10) << log(x[i]) * log(x[i]) << "\n";
    }

    double bp = (n * xys - xs * ys) / (n * xxs - xs * xs);
    double ap = (ys - bp * xs) / n;
    double b = exp(bp);
    double a = exp(ap);

    cout << "\nRegression Equation:\n";
    cout << "f(x) = " << a << " * " << b << "^x\n";

    double p;
    cin >> p;
    cout << "f(" << p << ") = " << a * pow(b, p) << '\n';

    return 0;
}