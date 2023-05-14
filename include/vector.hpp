#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>

template<typename T>
concept SCALAR = (std::is_integral_v<T> || std::is_floating_point_v<T>) && std::is_scalar_v<T>;

namespace krain
{
    template<typename T, std::size_t Rows, std::size_t Columns>
    requires SCALAR<T>
    class Vector{
        using VECT = Vector<T, Rows, Columns>;
        using VECT2  = Vector<T, Columns, Rows>;
        public:
        const size_t rows{Rows}, columns{Columns}, size{Rows*Columns};
        Vector():m_data{0}{
            assert(Rows > 0);
            assert(Columns > 0);
        }
        // Vector(const T& value):m_data{}{
        //     for (auto& x : m_data)
        //         x = value;
        // }
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
        std::array<T, Rows*Columns>& getData()
        {
            return m_data;
        }
        std::vector<T> getDataVector() 
        {
            std::vector<T> outvect(m_data.size());
            for (size_t i=0; i< m_data.size(); i++)
                outvect[i] = m_data[i];
            return outvect;
        }

        //-----------------operation with scalar----------------------
        template<typename Scalar>
        requires SCALAR<Scalar>
        static VECT add(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x += value;
            return vect;
        }
        template<typename Scalar>
        requires SCALAR<Scalar>
        static VECT sub(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x -= value;
            return vect;
        }
        template<typename Scalar>
        requires SCALAR<Scalar>
        static VECT mult(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x *= value;
            return vect;
        }
        template<typename Scalar>
        requires SCALAR<Scalar>
        static VECT divide(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x /= value;
            return vect;
        }
        template<typename Scalar>
        requires SCALAR<Scalar>
        static VECT power(VECT vect, const Scalar& value)
        {
            for(auto& x : vect.m_data)
                x = pow(x, value);
            return vect;
        }        //-----------------operation with vector----------------------
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
        static VECT mult(VECT vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++)
                vect.m_data[i] *= vect2.m_data[i];
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
        VECT operator+(const T& value) const
        {
            return this->add(*this, value);
        }
        VECT operator-(const T& value) const
        {
            return this->sub(*this, value);
        }
        VECT operator*(const T& value) const
        {
            return this->mult(*this, value);
        }
        VECT operator/(const T& value) const
        {
            return this->div(*this, value);
        }
        //-------
        VECT& operator+=(const T& value)
        {
            return *this = *this + value;
        }
        VECT& operator-=(const T& value)
        {
            return *this = *this - value;
        }
        VECT& operator*=(const T& value)
        {
            return *this = *this * value;
        }
        VECT& operator/=(const T& value)
        {
            return *this = *this / value;
        }
        VECT operator^(const T& value)
        {
            return this->power(*this, value);
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
        VECT operator*(const VECT& value)
        {
            return this->mult(*this, value);
        }
        // VECT operator^(const VECT& value)
        // {
        //     return this->pow(*this, value);
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
        VECT& operator*=(const VECT& value)
        {
            return *this = *this * value;
        }
        // VECT& operator/=(const VECT& value)
        // {
        //     return *this = *this / value;
        // }
        //-----------
        //-----------------------OSTREAM------------------
        friend std::ostream& operator<<(std::ostream& os, const VECT& obj)
        {
            os << "[";
            for(size_t i=0; i<obj.rows; i++)
            {
                os<<"[";
                for(size_t j=0; j<obj.columns; j++)
                {
                    os<<obj.get(i, j);
                    if(j < obj.columns-1)
                        os<<", ";
                }
                    os<<"]";
                if(i < obj.rows-1)
                {
                    os<<"\n";
                }
            }
            os << "]";
            return os;
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

        // static VECT mean(VECT vect)
        // {

        // }
        //----------------------generator-----------------------------------
        static VECT arange(T start, T end)
        {
            assert(start < end);
            VECT output;
            T steps = (end - start)/(Rows*Columns);
            for(size_t i=0; i < output.size; i++)
            {
                output.m_data[i] = start;
                start+=steps;
            }
            return output;
            
        }

        static VECT arange(size_t end)
        {
            return arange(0, end);
        }


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
template<typename Scalar, typename T, std::size_t Rows, std::size_t Columns>
requires SCALAR<Scalar>
krain::Vector<T, Rows, Columns> operator+(const Scalar& value, const krain::Vector<T, Rows, Columns>& vect)
{
    return vect+value;
}
template<typename Scalar, typename T, std::size_t Rows, std::size_t Columns>
requires SCALAR<Scalar>
krain::Vector<T, Rows, Columns> operator-(const Scalar& value, const krain::Vector<T, Rows, Columns>& vect)
{
    return vect-value;
}
template<typename Scalar, typename T, std::size_t Rows, std::size_t Columns>
requires SCALAR<Scalar>
krain::Vector<T, Rows, Columns> operator*(const Scalar& value, const krain::Vector<T, Rows, Columns>& vect)
{
    return vect*value;
}
template<typename Scalar, typename T, std::size_t Rows, std::size_t Columns>
requires SCALAR<Scalar>
krain::Vector<T, Rows, Columns> operator/(const Scalar& value, const krain::Vector<T, Rows, Columns>& vect)
{
    return vect/value;
}