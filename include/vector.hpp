#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>

template<typename T>
concept SCALAR_C = std::is_integral_v<T> || std::is_floating_point_v<T>;
namespace krain
{
    template<SCALAR_C T, std::size_t SizeX, std::size_t SizeY>
    class Vector{
        using VECT  = Vector<T, SizeX, SizeY>;
        public:
        Vector():m_data(0){}
        Vector(const T& value):m_data{}{
            for (auto& x : m_data)
                x = value;
        }
        ~Vector(){}

        T& get(std::size_t posx, std::size_t posy)
        {
            assert(posx < SizeX);
            assert(posy < SizeY);
            auto index = SizeY * posx + posy;
            return m_data[index];
        }

        //-----------------operation with scalar----------------------
        template<SCALAR_C Scalar>
        static VECT add(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x += value;
            return vect;
        }
        template<SCALAR_C Scalar>
        static VECT sub(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x -= value;
            return vect;
        }
        template<SCALAR_C Scalar>
        static VECT mult(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x *= value;
            return vect;
        }
        template<SCALAR_C Scalar>
        static VECT divide(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x /= value;
            return vect;
        }
        template<SCALAR_C Scalar>
        static VECT pow(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                pow(x, value);
            return vect;
        }
        //---------------utilities-------------------------------------
        static VECT sqrt(VECT vect)
        {
            for(auto& x : vect.m_data)
                sqrt(x);
            return vect;
        }
        static T sum(VECT &vect)
        {
            T result=0;
            for(auto const& x : vect.m_data)
                result += x;
            return result;
        }
        T sum()
        {
            return sum(*this);
        }

        //-----------------operation with vector----------------------
        static VECT add(VECT vect, const VECT& vect2)
        {
            for(size_t i=0; i<(SizeX * SizeY); i++)
                vect.m_data[i] += vect2.m_data[i];
            return vect;
        }
        static VECT sub(VECT vect, const VECT& vect2)
        {
            for(size_t i=0; i<(SizeX * SizeY); i++)
                vect.m_data[i] -= vect2.m_data[i];
            return vect;
        }
        static VECT dot(VECT vect, const VECT& vect2);
        static VECT cross(VECT vect, const VECT& vect2);
        static bool isEqual(const VECT& vect, const VECT& vect2)
        {
            for(size_t i=0; i<(SizeX * SizeY); i++){
                if (vect.m_data[i] != vect2.m_data[i])
                    return false;
            }
            return true;
        }
        // template<typename T>
        // static Vector<SizeX, SizeY> mult(VECT& vect, VECT value);
        // template<typename T>
        // static Vector<SizeX, SizeY> divide(VECT& vect, VECT value);

        //-----------------operator overload--------------------------
        template<SCALAR_C Scalar>
        VECT operator+(const Scalar& value)
        {
            return this->add(*this, value);
        }
        template<SCALAR_C Scalar>
        VECT operator-(const Scalar& value)
        {
            return this->sub(*this, value);
        }template<SCALAR_C Scalar>
        VECT operator*(const Scalar& value)
        {
            return this->mul(*this, value);
        }template<SCALAR_C Scalar>
        VECT operator/(const Scalar& value)
        {
            return this->div(*this, value);
        }
        //-------
        template<SCALAR_C Scalar>
        VECT& operator+=(const Scalar& value)
        {
            return *this = *this + value;
        }
        template<SCALAR_C Scalar>
        VECT& operator-=(const Scalar& value)
        {
            return *this = *this - value;
        }template<SCALAR_C Scalar>
        VECT& operator*=(const Scalar& value)
        {
            return *this = *this * value;
        }template<SCALAR_C Scalar>
        VECT& operator/=(const Scalar& value)
        {
            return *this = *this / value;
        }
        //------------------OPERATOR OVERLOAD VECT
        VECT operator+(const VECT& vect)
        {
            return this->add(*this, vect);
        }
        VECT operator-(const VECT& vect)
        {
            return this->sub(*this, vect);
        }
        // VECT operator*(const VECT& value)
        // {
        //     return this->dot(*this, value);
        // }
        // VECT operator/(const VECT& value)
        // {
        //     return this->div(*this, value);
        // }
        //-------
        VECT& operator+=(const VECT& vect)
        {
            return *this = *this + vect;
        }
        VECT& operator-=(const VECT& vect)
        {
            return *this = *this - vect;
        }
        // VECT& operator*=(const VECT& value)
        // {
        //     return *this = *this * value;
        // }
        // VECT& operator/=(const VECT& value)
        // {
        //     return *this = *this / value;
        // }
        //-----------
        //-----------------------OSTREAM------------------
        // ostream operator<<(VEC )
        private:
        std::array<T, SizeX * SizeY> m_data;
    };

}