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
    for(auto &x : aug) for(auto &y : x) cin >> y;
    original = aug;

    int rank = 0;
    for (int i = 0; i < n; i++) {
        int pivot = rank;
        for (int j = rank + 1; j < n; j++) {
            if(fabs(aug[j][i]) > fabs(aug[pivot][i])) pivot = j;
        }

        if(fabs(aug[pivot][i]) < eps) continue;
        R(rank, pivot);
        for(int j = rank + 1; j < n; j++) {
            double x = aug[j][i] / aug[rank][i];
            R(j, rank, x);
        }
        rank++;
    }

    bool infinite = false;
    for(int i = 0; i < n; i++) {
        bool zero = true;
        for(int j = 0; j < n; j++) {
            if(fabs(aug[i][j]) > eps) {
                zero = false;
                break;
            }
        }

        if (zero && fabs(aug[i][n]) > eps) {
            cout << "No solution" << endl;
            return 0;
        }
        else infinite = true;
    }

    cout << fixed << setprecision(3);
    cout << "Upper Triangular Matrix :" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) cout << setw(10) << aug[i][j];
        cout << endl;
    }

    if(infinite) {
        cout << "Infinity Solution" << endl;
        return 0;
    }

    vector <double> x(n);
    for(int i = n - 1; i >= 0; i--) {
        x[i] = aug[i][n];
        for(int j = i + 1; j < n; j++) x[i] -= aug[i][j] * x[j];
        x[i] /= aug[i][i];
    }

    cout << "Unique Solution" << endl;
    for(int i = 0; i < n; i++) cout << "X" << i + 1 << " = " << x[i] << endl;

    cout << "Verification:" << endl;
    for(int i = 0; i < n; i++) {
        double sum = 0;
        for(int j = 0; j < n; j++) sum += original[i][j] * aug[j][n];
        cout << "Equation " << i + 1 << " : " << sum << " = " << original[i][n] << endl;
    }
    
    return 0;
}