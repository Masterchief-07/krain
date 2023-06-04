#pragma once
#include <vector.hpp>
#include <concepts>
#include <random>

//------generating random values-----------------------
namespace krain::random
{
    template<typename T>
    concept FLOATING = std::is_floating_point_v<T>;
    //probability mass functions
    template<typename T>
    requires FLOATING<T>
    class Uniform
    {
        public:
        Uniform(const uint seed):m_seed{seed}, m_urgb{seed};
        {

        }
        T gen(T min, T max)
        {

        }
        void seed(uint seed)
        {
            m_seed = seed;
        }
        int seed() const
        {
            return m_seed;
        }
        private:
        uint m_seed;
        std::mt19937 m_urgb;


    };

    //probability discret functions
    template<typename T>
    requires FLOATING<T>
    class PDF
    {

    };

};