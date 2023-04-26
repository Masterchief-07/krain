#pragma once
#include <vector>
#include <tensor.hpp>

namespace krain
{
class LinearRegression{
    public:
    LinearRegression();
    ~LinearRegression(){}
    void train(std::vector<float> data);
    void predict(std::vector<float> data);

    private:
    float wGrad();
    float bGrad();

    private:
    float w{0}, b{0}, w_grad{0}, b_grad{0};
};
}