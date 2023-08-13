#pragma once
#include "matrix1d.hpp"
#include "sigmoid.hpp"

namespace krain
{
    template <typename scalar>
    class LogisticRegression
    {
        private:
        scalar

        public:
        LogisticRegression();
        ~LogisticRegression();

        matrix::Matrix1D<scalar> Forward(const matrix::Matrix1D<scalar>& input)
        {
            return 
        }


    };

}