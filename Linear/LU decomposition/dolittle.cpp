#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-4;

int main() {
    start:

    auto print = [](vector <vector <double>> &v) {
        for (auto x : v) {
            for (auto y : x) {
                printf("%8.4lf\t", y);
            }
            printf("\n");
        }
    };

    int n;
    cout << "Enter the number of equation : "; cin >> n;
    vector <vector <double>> A(n, vector <double> (n)), L(n, vector <double> (n)), U(n, vector <double> (n));
    vector <double> B(n), Z(n), X(n);

    cout << "Enter the augmented matrix: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> A[i][j];
        cin >> B[i];
    }

    for (int i = 0; i < n; i++) L[i][i] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
            U[i][j] = (A[i][j] - sum) / L[i][i];
        }

        for (int j = i + 1; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) sum += L[j][k] * U[k][i];
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }

    cout << "L = \n"; print(L);
    cout << "U = \n"; print(U);

    // zero check
    bool infinity = false;
    for (int i = 0; i < n; i++) {
        bool zeroRow = true;
        for (int j = 0; j < n; j++) {
            if (fabs(U[i][j]) > eps) {
                zeroRow = false;
                break;
            }
        }

        if (zeroRow) {
            if (fabs(Z[i]) > eps) {
                cout << "No solution found.\n";
                return 0;
            }
            else infinity = true;
        }
    }
    if (infinity) {
        cout << "There are infinite solutions.\n";
        return 0;
    }

    // forward substitution
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) sum += L[i][j] * Z[j];
        Z[i] = (B[i] - sum) / L[i][i];
    }

    // backward substitution
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = n - 1; j > i; j--) sum += U[i][j] * X[j];
        X[i] = (Z[i] - sum) / U[i][i];
    }

    for (int i = 0; i < n; i++) cout << "X" << i + 1 << " = " << X[i] << "\n";

    cout << "Solve another system? (y / n) ";
    char ch; cin >> ch;
    if (ch == 'y') goto start;
}