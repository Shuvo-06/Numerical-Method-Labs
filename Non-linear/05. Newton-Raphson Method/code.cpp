#include <bits/stdc++.h>
using namespace std;

#define sp(x) fixed << setprecision(6)

int deg;
vector <int> func, der;
const double eps = 1e-3;
const double steps = 0.45;

int main() {
    cin >> deg;
    func.resize(deg + 1);
    der.resize(deg);
    for (int i = deg; i >= 0; i--) {
        cin >> func[i];
        if (i != 0) der[i] = func[i + 1] * (i + 1);
    }

    cout << "Function : ";
    for (int i = deg; i >= 0; i--) {
        if (func[i] == 0) continue;
        if (i != deg && func[i] >= 0) cout << "+";

        if (func[i] == -1) cout << '-';
        else if (func[i] == 1) {}
        else cout << func[i];

        if (i != 0) cout << "x";
        if (i > 1) cout << "^" << i;
    }
    cout << " = 0" << endl;

    cout << "Derivative : ";
    for (int i = deg - 1; i >= 0; i--) {
        if (der[i] == 0) continue;
        if (i != deg - 1 && der[i] >= 0) cout << "+";

        if (der[i] == -1) cout << '-';
        else if (der[i] == 1) {}
        else cout << der[i];

        if (i != 0) cout << "x";
        if (i > 1) cout << "^" << i;
    }
    cout << " = 0" << endl;


    auto f = [&](double x) {
        double xpow = 1.00, ans = 0;
        for (auto val : func) {
            ans += val * xpow;
            xpow *= x;
        }
        return ans;
    };

    auto df = [&](double x) {
        double xpow = 1.00, ans = 0;
        for (auto val : der) {
            ans += val * xpow;
            xpow *= x;
        }
        return ans;
    };

    function <pair <double, int> (double)> nr = [&](double x) {
        for (int it = 1; ;it++) {
            double nx = x - f(x) / df(x);
            if (fabs(nx - x) < eps && fabs(f(nx)) < eps) return make_pair(nx, it);
            x = nx;
        }
    };

    double xmax = sqrt((func[deg - 1] / func[deg]) * (func[deg - 1] / func[deg]) - 2 * (func[deg - 2] / func[deg]));
    for (double i = -xmax; i < xmax; i += steps) {
        if (f(i) * f(i + steps) < 0) {
            auto p = nr(i);
            double rt = p.first;
            int it = p.second;

            cout << endl;
            cout << "Root : " << rt << endl;
            cout << "Iteration : " << it << endl;
            cout << "Search interval for the root : [" << i << " " << i + steps << "]\n";
            cout << fixed << sp(6) << "f(x) = " << f(rt) << endl;
            cout << fixed << sp(6) << "f'(x) = " << df(rt) << endl;
        }
    }

}

/*
4
1 0 -5 0 4

4
1 -3 2 6 0

// keep a equation of 5-degree and 3-degree that satisifies the xmax range also
*/
