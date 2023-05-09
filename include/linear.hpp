#pragma once
// #include <vector>
#include "vector.hpp"

namespace krain
{
template<SCALAR_C scalar>
class LinearRegression{
    public:
    LinearRegression(){};
    ~LinearRegression(){}
    template<size_t columns>
    void train(Vector<scalar, 1, columns>& input, Vector<scalar, 1, columns>& target)
    {
        auto output = input * w + b;

    }
    template<size_t columns>
    Vector<scalar, 1, columns> predict(Vector<scalar, 1, columns>& input)
    {

    }

    private:
    float wGrad(std::vector<float>& input);
    float bGrad();

    private:
    scalar w{0}, b{0}, w_grad{0}, b_grad{0};

};
}