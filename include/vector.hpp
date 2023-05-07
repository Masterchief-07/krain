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
    template<SCALAR_C T, std::size_t Rows, std::size_t Columns>
    class Vector{
        using VECT  = Vector<T, Rows, Columns>;
        using VECT2  = Vector<T, Columns, Rows>;
        public:
        Vector():m_data{0}{
            assert(Rows > 0);
            assert(Columns > 0);
        }
        Vector(const T& value):m_data{}{
            for (auto& x : m_data)
                x = value;
        }
        Vector(const std::array<T, Rows*Columns>& value):m_data{value}{
        }
        ~Vector(){}

        T& get(std::size_t row, std::size_t column)
        {
            return m_data[getIndex(row, column)];
        }
        T get (std::size_t row, std::size_t column) const
        {
            return m_data[getIndex(row, column)];
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
        static VECT2 Tr(const VECT& vect)
        {
            VECT2 result{vect.m_data};
            return result;
        }
        VECT2 Tr()
        {
            return Tr(*this);
        }

        //-----------------operation with vector----------------------
        static VECT add(VECT vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++)
                vect.m_data[i] += vect2.m_data[i];
            return vect;
        }
        static VECT sub(VECT vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++)
                vect.m_data[i] -= vect2.m_data[i];
            return vect;
        }
        template <size_t NewColumns>
        static Vector<T, Rows, NewColumns> dot(const VECT& vect,
                         const Vector<T, Columns, NewColumns>& vect2
                         )
        {
            Vector<T, Rows, NewColumns> result{0};
            for(size_t y1=0; y1 < Rows; y1++)
            {
                for(size_t x1=0; x1 < NewColumns; x1++)
                {
                    T sum = 0;
                    for(size_t x2=0; x2 < Columns; x2++)
                    {
                        sum += vect.get(y1, x2) * vect2.get(x2, y1);
                    }
                    result.get(y1, x1) = sum;
                }
            }
            return result;
        }
        template <size_t NewColumns>
        Vector<T, Rows, NewColumns> dot(const Vector<T, Columns, NewColumns>& vect)
        {
            return dot(*this, vect);
        }

        static VECT cross(VECT vect, const VECT2& vect2);
        static bool isEqual(const VECT& vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++){
                if (vect.m_data[i] != vect2.m_data[i])
                    return false;
            }
            return true;
        }
        // template<typename T>
        // static Vector<Rows, Columns> mult(VECT& vect, VECT value);
        // template<typename T>
        // static Vector<Rows, Columns> divide(VECT& vect, VECT value);

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
        std::array<T, Rows * Columns> m_data;
        size_t getIndex(std::size_t row, std::size_t column) const
        {
            assert(row < Rows);
            assert(column < Columns);
            auto index = Columns * row + column;
            return index;
        }
    };

}