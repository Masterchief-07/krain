#include <iostream>
#include <matplotlibcpp.h>
#include <linear.hpp>

int main() {

    matrix::Matrix1D<double> hello{{1,2,3,4,5,6,7,8}};
    std::cout<<hello<<"\n";
    std::cout<<hello.mean()<<"\n";
    
    return 0;
}