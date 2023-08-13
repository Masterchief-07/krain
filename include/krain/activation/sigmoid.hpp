#pragma once
#include <cmath>
namespace krain
{

template <typename T>
T sigmoid(const T& value)
{
    return 1/(1+exp(-value));
}

template <typename T>
T dsigmoid(const T& value)
{
    T compute = sigmoid(value);
    return compute * (1 - compute);
}

template<typename T>
class Sigmoid{
    T result;

    public:
        Sigmoid():result{0}{};
        ~Sigmoid(){};
        T operator()(const T& value)
        {
            result = sigmoid(value);
            return result;
        }
        T derive(){
            return result * (1 - result);
        }
};
} // namespace krain
