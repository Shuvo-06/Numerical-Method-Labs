#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-3;

int n;
vector <vector <double>> aug, original;

void R(int r1, int r2) {
    swap(aug[r1], aug[r2]);
}

void R(int r1, int r2, double x) {
    for(int j = 0; j <= n; j++) aug[r1][j] -= x * aug[r2][j];
}

void R(int r, double x) {
    for(int j = 0; j <= n; j++) aug[r][j] /= x;
}

int main() {
    cin >> n;
    aug.resize(n, vector <double>(n + 1));
    original.resize(n, vector <double>(n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> aug[i][j];
            original[i][j] = aug[i][j];
        }
    }

    int rank = 0;
    for (int col = 0; col < n && rank < n; col++) {
        int pivot = rank;

        for (int i = rank + 1; i < n; i++) {
            if (fabs(aug[i][col]) > fabs(aug[pivot][col])) pivot = i;
        }

        if(fabs(aug[pivot][col]) < eps) continue;
        R(rank, pivot);
        R(rank, aug[rank][col]);
        for (int i = 0; i < n; i++) {
            if (i == rank) continue;
            R(i, rank, aug[i][col]);
        }
        rank++;
    }

    cout << "Reduced Echelon Form :" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) cout << setw(10) << fixed << setprecision(3) << aug[i][j];
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        bool rowZero = true;
        for (int j = 0; j < n; j++) {
            if (fabs(aug[i][j]) > eps) {
                rowZero = false;
                break;
            }
        }

        if(rowZero && fabs(aug[i][n]) > eps) {
            cout << "No solution" << endl;
            return 0;
        }
    }

    if(rank < n) {
        cout << "Infinity Solution" << endl;
        return 0;
    }

    cout << "Unique Solution" << endl;
    for (int i = 0; i < n; i++) cout << "X" << i + 1 << " = " << aug[i][n] << endl;

    cout << "Verification:" << endl;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) sum += original[i][j] * aug[j][n];
        cout << "Equation " << i + 1 << " : " << sum << " = " << original[i][n] << endl;
    }

    return 0;
}