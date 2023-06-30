#pragma once
// #include <vector>
#include "matrix1d.hpp"
#include "matrix2d.hpp"
#include <cmath>

namespace krain
{
template<typename scalar>
requires SCALAR<scalar>
class LinearRegression{
    public:
    LinearRegression(){}
    ~LinearRegression(){}
    void train(const matrix::Matrix1D<scalar>& input, const matrix::Matrix1D<scalar>& target, scalar lr=0.001, scalar threshold=0.05)
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
    void train(const matrix::Matrix2D<scalar>& input, const matrix::Matrix2D<scalar>& target, scalar lr=0.001, scalar threshold=0.05)
    {
        w = 0;
        b = 0;
        w_grad = 0;
        b_grad = 0;
        setLR(lr);
        scalar loss = 1;
        while(loss>threshold && !std::isinf(loss))
        {
            loss = 0;
            for(size_t i=0; i<input.getRows(); i++)
            {
                loss += steps(input.at(i), target);
            }
            loss /= input.getRows();
            loss_evolution.push_back(loss);
        }
    }
    matrix::Matrix1D<scalar> predict(const matrix::Matrix1D<scalar>& input)
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
    scalar steps(const matrix::Matrix1D<scalar>& input, const matrix::Matrix1D<scalar>& target)
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
    scalar wGrad(const matrix::Matrix1D<scalar>& input, const matrix::Matrix1D<scalar>& error)
    {
        return 2.0 * (input * error).mean();

    }
    scalar bGrad(const matrix::Matrix1D<scalar>& error)
    {
        return 2.0 * error.mean();
    }

    private:
    scalar w{0}, b{0}, w_grad{0}, b_grad{0}, m_lr{0.001};
    public:
    std::vector<scalar> w_evolution{}, b_evolution{}, loss_evolution{};

};

class LogisticRegression
{

};
}