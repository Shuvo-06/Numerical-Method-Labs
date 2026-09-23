#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-5;

int main() {
    auto print = [](vector<vector<double>> &v) {
        for (auto x : v) {
            for (auto y : x) printf("%8.4lf ", y);
            printf("\n");
        }
    };

    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n)), ADJ(n, vector<double>(n)), INV(n, vector<double>(n));
    vector<double> B(n), X(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> A[i][j];
        cin >> B[i];
    }

    auto cofactor = [&](int p, int q) {
        vector<vector<double>> temp(n - 1, vector<double>(n - 1));
        int row = 0, col = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == p || j == q) continue;
                temp[row][col++] = A[i][j];
                if (col == n - 1) {
                    col = 0;
                    row++;
                }
            }
        }

        return temp;
    };

    function<double(vector<vector<double>>, int)> determinant = [&](vector<vector<double>> A, int n) {
        if (n == 1) return A[0][0];

        double det = 0;
        for (int j = 0; j < n; j++) {
            vector<vector<double>> temp(n - 1, vector<double>(n - 1));
            int row = 0, col = 0;
            for (int i = 1; i < n; i++) {
                for (int k = 0; k < n; k++) {
                    if (k == j) continue;
                    temp[row][col++] = A[i][k];
                    if (col == n - 1) {
                        col = 0;
                        row++;
                    }
                }
            }

            int sign = (j % 2 == 0) ? 1 : -1;
            det += sign * A[0][j] * determinant(temp, n - 1);
        }

        return det;
    };

    double det = determinant(A, n);

    cout << "Determinant : " << det << '\n';
    if (fabs(det) < EPS) {
        cout << "Inverse doesn't exist.\n";
        return 0;
    }

    // Adjoint matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<vector<double>> temp = cofactor(i, j);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            ADJ[j][i] = sign * determinant(temp, n - 1);
        }
    }

    // Inverse = Adjoint / Determinant
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) INV[i][j] = ADJ[i][j] / det;
    }

    // X = INV * B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) X[i] += INV[i][j] * B[j];
    }

    cout << "\nInverse Matrix:\n";
    print(INV);

    cout << "\nSolution:\n";
    for (int i = 0; i < n; i++) cout << "X" << i + 1 << " = " << X[i] << '\n';
}