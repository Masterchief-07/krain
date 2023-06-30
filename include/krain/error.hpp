#pragma once


class MSError{

    public:
    MSError();
    ~MSError(){};
    template<typename T>
    double operator() (T y_hat, T y)
    {
        auto result = y_hat - y

        return 0;
    }

};