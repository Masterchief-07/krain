#include <plot.hpp>
#include <vector>
#include <iostream>
#include <cmath>

int main() {
    Plot myploter{"../venv/bin/python"};
    int n = 50; // number of data points
    std::vector<double> x(n),y(n), x_2(n), y_2(n);
    for(int i=0; i<n; ++i) {
        double t = 2*M_PI*i/n;
        x.at(i) = 16*sin(t)*sin(t)*sin(t);
        y.at(i) = 13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t);
    }
    for(int i=0; i<n; ++i) {
        double t = 2*M_PI*i/n;
        x_2.at(i) = 10*sin(t)*sin(t)*sin(t);
        y_2.at(i) = 7*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t);
    }
    // myploter(x, y);
    myploter.plot(x, y);
    myploter.plot(x_2, y_2, "b*");
    myploter.show();
}