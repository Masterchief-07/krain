#include <plot.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <vector.hpp>

int main() {
    krain::Vector<float, 1, 3> direction(3);
    direction.get(0,0) = 3;
    direction.get(0,1) = 6;
    direction.get(0,2) = 9;
    std::cout<<direction.get(0, 1)<<"\n";
    auto newdirection = direction + 6;
    newdirection -= 3;
    std::cout<<krain::Vector<float, 1, 3>::sum(direction)<<"\n";
    std::cout<<newdirection.sum()<<"\n";
    direction += newdirection;
    std::cout<<direction.sum()<<"\n";
    direction -= newdirection;
    std::cout<<direction.sum()<<"\n";

    return 0;
}