#include <iostream>
#include <matplotlibcpp.h>
#include <linear.hpp>

namespace plt = matplotlibcpp;

int main() {
    auto X = krain::Vector<double, 1, 1000>::arange(-1, 1);
    std::cout<<"x:"<<X<<"\n";
    double B{7.34}, W{3.15};
    // auto Y = (krain::Vector<float, 1,10>) B;
    auto Y = X * W + B;
    // auto Y = B + W * (X^2);
    std::cout<<"y:"<<Y<<"\n";
    // // plt::plot(X.getDataVector(), Y.getDataVector());
    // // plt::show();

    krain::LinearRegression<double> linear{};
    linear.train(X, Y, 0.01, 0.00001);
    std::cout<<"B:"<<B<<" W:"<<W<<"\n";
    std::cout<<"B_train:"<<linear.getB()<<" W_train:"<<linear.getW()<<"\n";
    plt::plot(linear.loss_evolution);
    plt::plot(linear.w_evolution);
    plt::plot(linear.b_evolution);
    plt::show();
    
    return 0;
}