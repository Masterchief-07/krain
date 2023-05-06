#include <plot.hpp>
#include <vector>
#include <iostream>
#include <cmath>

int main() {
    Plot myploter{"../venv/bin/python"};
    // std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    // std::vector<double> y = {0.0, 2.0, 4.0, 6.0, 8.0};
    int n = 5000; // number of data points
    std::vector<double> x(n),y(n);
    for(int i=0; i<n; ++i) {
        double t = 2*M_PI*i/n;
        x.at(i) = 16*sin(t)*sin(t)*sin(t);
        y.at(i) = 13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t);
    }
    myploter(x, y);
}