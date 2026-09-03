#include <bits/stdc++.h>
using namespace std;

#define int double
#define sp(x) fixed << setprecision(x)
const int eps = 1e-4;
int a, b, c, d, e;
int32_t counter = 0;

int f(int x) {
    return a * x * x * x * x + b * x * x * x + c * x * x + d * x + e;
}

void bisection(int lo, int hi) {
    int old = lo;
    for (int32_t it = 1; ; it++) {
        int x0 = (lo + hi) / 2;

        if (fabs(f(x0)) < eps || fabs(x0 - old) / old < eps) {
            cout << "Root : " << sp(4) << x0 << " [" << lo << ", " << hi << "] Iterations : " << it << "\n";
            counter++;
            return;
        }

        if (f(x0) * f(lo) < 0) hi = x0;
        else if (f(x0) * f(hi) < 0) lo = x0;
        old = x0;
    }
}

int32_t main() {
    cin >> a >> b >> c >> d >> e;

    int x = (b * b) / (a * a) - 2 * (c / a);
    if (x < 0) {
        cout << "Not a valid range\n";
        return 0;
    }
    int range = sqrt(x);

    for (int i = -range; i < range; i+=0.5) {

        if (f(i) * f(i + 0.5) < 0) bisection(i, i + 0.5);
    }

    if (counter < 4) cout << 4 - counter << " roots are either out of range or complex.\n";
    return 0;
}
