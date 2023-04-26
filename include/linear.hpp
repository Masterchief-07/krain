#pragma once
#include <vector>
#include <tensor.hpp>

namespace krain
{
class LinearRegression{
    public:
    LinearRegression();
    ~LinearRegression(){}
    void train(std::vector<float>& input, std::vector<float>& target);
    std::vector<float> predict(std::vector<float>& input);

    private:
    float wGrad(std::vector<float>& input);
    float bGrad();

    private:
    float w{0}, b{0}, w_grad{0}, b_grad{0};
};
}