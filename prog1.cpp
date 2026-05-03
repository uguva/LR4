#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct TableRow1 {
    int n;
    double a, b, diff;
};

struct TableRow2 {
    int n;
    double x_n, x_n1, diff;
};

vector<TableRow1> bisection(double a, double b, double eps) {
    vector<TableRow1> res;
    int n = 0;
    while (abs(b - a) >= eps) {
        res.push_back({n, a, b, abs(b - a)});
        double c = (a + b) / 2.0;
        if ((sin(a) - 2 * a - 1) * (sin(c) - 2 * c - 1) < 0) {
            b = c;
        } else {
            a = c;
        }
        n++;
    }
    res.push_back({n, a, b, abs(b - a)});
    return res;
}

vector<TableRow2> newton(double x0, double eps) {
    vector<TableRow2> res;
    int n = 0;
    double diff = eps + 1.0;
    while (diff >= eps) {
        double fx = sin(x0) - 2 * x0 - 1;
        double dfx = cos(x0) - 2;
        double x1 = x0 - fx / dfx;
        diff = abs(x1 - x0);
        res.push_back({n, x0, x1, diff});
        x0 = x1;
        n++;
    }
    return res;
}

vector<TableRow2> simple_iteration(double x0, double eps) {
    vector<TableRow2> res;
    int n = 0;
    double diff = eps + 1.0;
    while (diff >= eps) {
        double x1 = (sin(x0) - 1) / 2.0;
        diff = abs(x1 - x0);
        res.push_back({n, x0, x1, diff});
        x0 = x1;
        n++;
    }
    return res;
}

int main() {
    double a, b, eps, x0_n, x0_s;
    if (cin >> a >> b >> eps >> x0_n >> x0_s) {
        vector<TableRow1> b_res = bisection(a, b, eps);
        for (auto r : b_res) {
            cout << r.n << " " << r.a << " " << r.b << " " << r.diff << "\n";
        }
        
        vector<TableRow2> n_res = newton(x0_n, eps);
        for (auto r : n_res) {
            cout << r.n << " " << r.x_n << " " << r.x_n1 << " " << r.diff << "\n";
        }

        vector<TableRow2> s_res = simple_iteration(x0_s, eps);
        for (auto r : s_res) {
            cout << r.n << " " << r.x_n << " " << r.x_n1 << " " << r.diff << "\n";
        }
    }
    return 0;
}
