#pragma once
// #include <vector>
#include "vector.hpp"
#include <cmath>

namespace krain
{
template<typename scalar>
requires SCALAR<scalar>
class LinearRegression{
    public:
    LinearRegression(){}
    ~LinearRegression(){}
    template<size_t columns>
    void train(const Vector<scalar, 1, columns>& input, const Vector<scalar, 1, columns>& target, scalar lr=0.001, scalar threshold=0.05)
    {
        w = 0;
        b = 0;
        w_grad = 0;
        b_grad = 0;
        setLR(lr);
        scalar loss = 1;
        while(loss>threshold && !std::isinf(loss))
        {
            loss = steps(input, target);
            loss_evolution.push_back(loss);
        }
        // w_grad = 
    }
    template<size_t columns>
    Vector<scalar, 1, columns> predict(const Vector<scalar, 1, columns>& input)
    {
        return b + w * input;
    }
    void setLR(double lr=0.001)
    {
        m_lr = lr;
    }
    scalar getW() const
    {
        return w;
    }

    scalar getB() const
    {
        return b;
    }
    scalar getWGrad() const
    {
        return w_grad;
    }
    scalar getBGrad() const
    {
        return b_grad;
    }

    private:
    template<size_t columns>
    scalar steps(const Vector<scalar, 1, columns>& input, const Vector<scalar, 1, columns>& target)
    {
        auto output = b + (w * input) ;
        // std::cout<<"output: "<<output<<"\n";
        auto error = output - target;
        // std::cout<<"error: "<<error<<"\n";
        auto loss = (error^2).mean();
        // std::cout<<"loss: "<<loss<<"\n";
        w_grad = wGrad(input, error);
        // std::cout<<"w_grad: "<<w_grad<<"\n";
        b_grad = bGrad(error);
        // std::cout<<"b_grad: "<<b_grad<<"\n";
        w =  w - m_lr * w_grad;
        // std::cout<<"w: "<<w<<"\n";
        b = b - m_lr * b_grad;
        // std::cout<<"b: "<<b<<"\n";
        w_evolution.push_back(w);
        b_evolution.push_back(b);

        return loss;
    }
    template<size_t columns>
    scalar wGrad(const Vector<scalar, 1, columns>& input, const Vector<scalar, 1, columns>& error)
    {
        return 2.0 * (input * error).mean();

    }
    template<size_t columns>
    scalar bGrad(const Vector<scalar, 1, columns>& error)
    {
        return 2.0 * error.mean();
    }

    private:
    scalar w{0}, b{0}, w_grad{0}, b_grad{0}, m_lr{0.001};
    public:
    std::vector<scalar> w_evolution{}, b_evolution{}, loss_evolution{};

};
}