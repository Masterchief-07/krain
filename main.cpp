#include <iostream>
#include <matplotlibcpp.h>
#include <linear.hpp>

namespace plt = matplotlibcpp;

int test (const int& a, const int& b)
{
    return a+b;
}

int main() {
    auto X = krain::Vector<double, 1, 10>::arange(0.5, 1);
    std::cout<<"x:"<<X<<"\n";
    double B{7.34}, W{3.15};
    // auto Y = (krain::Vector<float, 1,10>) B;
    auto Y = X * W + B;
    // auto Y = B + W * (X^2);
    // std::cout<<"y:"<<Y<<"\n";
    // plt::plot(X.getDataVector(), Y.getDataVector());
    // plt::show();

    // krain::LinearRegression<double> linear{};
    // linear.train(X, Y);
    auto a{10}, b{20};
    std::cout<<test(a,  b)<<"\n";
    
    return 0;
}