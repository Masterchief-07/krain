#pragma once
// #include <vector>
#include "vector.hpp"

namespace krain
{
template<typename scalar>
requires SCALAR<scalar>
class LinearRegression{
    public:
    LinearRegression(){}
    ~LinearRegression(){}
    template<size_t columns>
    void train(const Vector<scalar, 1, columns>& input, const Vector<scalar, 1, columns>& target)
    {
        scalar loss = 1;
        while(loss>0.001)
        {
            loss = steps(input, target);
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
        auto output = b + w * input ;
        std::cout<<"output: "<<output<<"\n";
        auto error = output - target;
        std::cout<<"error: "<<error<<"\n";
        auto loss = (error^2).sum();
        std::cout<<"loss: "<<loss<<"\n";
        w_grad = wGrad(input, error);
        b_grad = bGrad(error);
        w -= m_lr * w_grad;
        b -= m_lr * b_grad;

        return loss;
    }
    template<size_t columns>
    scalar wGrad(const Vector<scalar, 1, columns>& input, const Vector<scalar, 1, columns>& error)
    {
        return 2 * (input * error).sum() / (scalar) input.size();

    }
    template<size_t columns>
    scalar bGrad(const Vector<scalar, 1, columns>& error)
    {
        return 2 * (error).sum() / (scalar) error.size();
    }

    private:
    scalar w{0}, b{0}, w_grad{0}, b_grad{0}, m_lr{0.001};

};
}