#include <bits/stdc++.h>
using namespace std;

// y = a * e ^ (b * x)
// ln(y) = ln(a) + b * x

int main() {
    int n;
    cin >> n;

    vector<double> x(n), y(n);
    for (double &v : x) cin >> v;
    for (double &v : y) cin >> v;

    double xs = 0, lnys = 0, xlnys = 0, xxs = 0;

    for (int i = 0; i < n; i++) {
        xs += x[i];
        lnys += log(y[i]);
        xlnys += x[i] * log(y[i]);
        xxs += x[i] * x[i];
    }

    cout << fixed << setprecision(6);
    cout << "Table : \n";

    cout << setw(10) << "x : ";
    for (int i = 0; i < n; i++) cout << setw(10) << x[i] << " ";
    cout << setw(10) << "Sum = " << xs << "\n\n";

    cout << setw(10) << "y : ";
    for (int i = 0; i < n; i++) cout << setw(10) << y[i] << " ";
    cout << "\n\n";

    cout << setw(10) << "ln(y) : ";
    for (int i = 0; i < n; i++) cout << setw(10) << log(y[i]) << " ";
    cout << setw(10) << "Sum = " << lnys << "\n\n";

    cout << setw(10) << "x * ln(y) : ";
    for (int i = 0; i < n; i++) cout << setw(10) << x[i] * log(y[i]) << " ";
    cout << setw(10) << "Sum = " << xlnys << "\n\n";

    cout << setw(10) << "x^2 : ";
    for (int i = 0; i < n; i++) cout << setw(10) << x[i] * x[i] << " ";
    cout << setw(10) << "Sum = " << xxs << "\n\n";

    double b = (n * xlnys - xs * lnys) / (n * xxs - xs * xs);
    double a = exp((lnys - b * xs) / n);

    cout << "\nRegression Equation:\n";
    cout << "f(x) = " << a << "e^(" << b << "x)\n";

    double p;
    cout << "\nEnter x: ";
    cin >> p;

    cout << "f(" << p << ") = " << a * exp(b * p) << '\n';
}

/*
5
0 1 2 3 4
2 3.29744 5.43656 8.96338 14.7781

f(x) = 2.000000e^(0.500000x)

f(5) = 24.3651
*/