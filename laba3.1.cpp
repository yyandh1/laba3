#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double y;
double func1(double x) {
    y = x/3 + 0.67;
    return y;
}

double func2(double x) {
    y = tan(x/2);
    return y;
}

double func3(double x) {
    y = (0.5 * x) - 1.5;
    return y;
}



int main()
{
    cout << "Funktionswert" << endl;
    cout << "X" << "\t" << "Y" << endl;


    double dx = 0.5;
    for (double x = -5; x <= 5; x += dx) {

        if (x >= -5 & x <= -2) {
            cout << fixed << setprecision(2) << x << "  " << func1(x) << endl;
        }
        if (x >= -2 & x <= 2) {
            cout << fixed << setprecision(2) << x << "  " << func2(x) << endl;
        }
        if (x >= 2 & x <= 5) {
            cout << fixed << setprecision(2) << x << "  " << func3(x) << endl;
        }
    }
   return 0;
}