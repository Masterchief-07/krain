#pragma once

namespace krain
{
    class Base{
        Base() = 0;
        ~Base() = 0;

        public:
        template<typename T, typename J>
        virtual J operator() (const T& x) = 0;
        template<typename T, typename J>
        virtual J operator() (const T& x, const T& y) = 0;
        template<typename T>
        virtual void Forward(T) = 0;
        template<typename T, typename J>
        virtual J Forward(T) = 0;
        template<typename T>
        virtual void Backward(T) = 0;
        template<typename T, typename J>
        virtual J Backward(T) = 0;

    };
    
} // namespace krain

