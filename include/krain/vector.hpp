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
        #define VECT2   Vector<T, Columns, Rows>
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
        Vector(const VECT& input):m_data{input.m_data}
        {

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
        // std::array<T, Columns> get(std::size_t row)
        // {
        //     std::size_t begin = getIndex(row, 0);
        //     std::size_t end = begin+Columns;
        //     auto result = std::array<T, Columns>{m_data.begin()+begin, m_data.begin()+end};
        //     return result;
        // }
        std::array<T, Rows*Columns>& getData()
        {
            return m_data;
        }
        std::array<T, Rows*Columns> getData() const
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
        static void add_(VECT& vect, const T& value)
        {
            for(auto& x : vect.m_data)
                x += value;
        }
        static void sub_(VECT& vect, const T& value)
        {
            for(auto& x : vect.m_data)
                x -= value;
        }
        static void mult_(VECT& vect, const T& value)
        {
            for(auto& x : vect.m_data)
                x *= value;
        }
        static void divide_(VECT& vect, const T& value)
        {
            for(auto& x : vect.m_data)
                x /= value;
        }
        static VECT divide(const T& value, VECT vect)
        {
            for(auto& x : vect.m_data)
                x = value/x;
            return vect;
        }
        VECT add(const VECT& vect, const T& value) const
        {
            auto target{vect};
            add_(target, value);
            return target;

        }
        VECT sub(const VECT& vect, const T& value) const
        {
            auto target{vect};
            sub_(target, value);
            return target;

        }
        VECT mult(const VECT& vect, const T& value) const
        {
            auto target{vect};
            mult_(target, value);
            return target;

        }
        VECT divide(const VECT& vect, const T& value) const
        {
            auto target{vect};
            divide_(target, value);
            return target;

        }
        static void power_(VECT& vect, const T& value)
        {
            for(auto& x : vect.m_data)
                x = std::pow(x, value);
        }        
        VECT power(const VECT& vect, const T& value) const
        {
            auto target{vect};
            power_(target, value);
            return target;
        }
        //-----------------operation with vector----------------------
        static void add_(VECT& vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++)
                vect.m_data[i] += vect2.m_data[i];
        }
        static void sub_(VECT& vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++)
                vect.m_data[i] -= vect2.m_data[i];
        }
        static void mult_(VECT& vect, const VECT& vect2)
        {
            for(size_t i=0; i<(Rows * Columns); i++)
                vect.m_data[i] *= vect2.m_data[i];
        }
        VECT add(const VECT& vect, const VECT& vect2) const
        {
            auto target{vect};
            add_(target, vect2);
            return target;
        }
        VECT sub(const VECT& vect, const VECT& vect2) const
        {
            auto target{vect};
            sub_(target, vect2);
            return target;
        }
        VECT mult(const VECT& vect, const VECT& vect2) const
        {
            auto target{vect};
            mult_(target, vect2);
            return target;
        }
        template <size_t NewColumns>
        static Vector<T, Rows, NewColumns> dot(const VECT& vect,
                         const Vector<T, Columns, NewColumns>& vect2
                         )
        {
            Vector<T, Rows, NewColumns> result{};
            for(size_t y1=0; y1 < Rows; y1++)
            {
                for(size_t x1=0; x1 < NewColumns; x1++)
                {
                    T sum = 0;
                    for(size_t x2=0; x2 < Columns; x2++)
                    {
                        sum += vect.get(y1, x2) * vect2.get(x2, x1);
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
            return this->divide(*this, value);
        }
        VECT operator^(const T& value) const
        {
            return power(*this, value);
        }
        //-------
        VECT& operator+=(const T& value)
        {
            add_(*this, value);
            return *this;
        }
        VECT& operator-=(const T& value)
        {
            sub_(*this, value);
            return *this;
        }
        VECT& operator*=(const T& value)
        {
            mult_(*this, value);
            return *this;
        }
        VECT& operator/=(const T& value)
        {
            divide_(*this, value);
            return *this;
        }
        
        //------------------OPERATOR OVERLOAD VECT
        VECT operator+(const VECT& vect) const
        {
            return this->add(*this, vect);
        }
        VECT operator-(const VECT& vect) const
        {
            return this->sub(*this, vect);
        }
        VECT operator*(const VECT& value) const
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
            add_(*this, vect);
            return *this;
        }
        VECT& operator-=(const VECT& vect)
        {
            sub_(*this, vect);
            return *this;
        }
        VECT& operator*=(const VECT& vect)
        {
            mult_(*this, vect);
            return *this;
        }
        VECT& operator=(const VECT& vect)
        {
            const auto& data = vect.getData();
            for(size_t i=0; i<size; i++)
                this->m_data[i] = data[i];
            return *this;
        }
        // VECT& operator/=(const VECT& value)
        // {
        //     return *this = *this / value;
        // }
        //-----------
        bool operator==(const VECT& value) const
        {
            return isEqual(*this, value);
        }
        bool operator!=(const VECT& value) const
        {
            return !(*this==value);
        }
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
        static void sqrt_(VECT& vect)
        {
            for(auto& x : vect.m_data)
                x = std::sqrt(x);
        }
        VECT sqrt() const
        {
            auto result{*this};
            sqrt_(result);
            return result;
        }
        static T sum(const VECT &vect)
        {
            T result=0;
            for(auto const& x : vect.m_data)
                result += x;
            return result;
        }
        T sum() const
        {
            auto value = sum(*this);
            return value;
        }
        static VECT2 Tr(const VECT& vect)
        {
            VECT2 result{};
            for(size_t i=0; i<result.rows; i++)
            {
                for(size_t j=0; j<result.columns; j++)
                {
                    result.get(i,j) = vect.get(j, i);
                }
            }
            return result;
        }
        VECT2 Tr() const
        {
            auto result = Tr(*this);
            return result;
        }
        static T mean(const VECT& input)
        {
            return input.sum()/((T) input.size);
        }
        T mean() const
        {
            T result = mean(*this);
            return result;
        }

        static T norm(const VECT& input)
        {
            T result = 0;
            for(auto const& x: input.m_data)
                result += std::pow(x, 2);
            return std::sqrt(result);
        }

        T norm() const
        {
            T result = norm(*this);
            return result;
        }
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
    return krain::Vector<T, Rows, Columns>::divide(value, vect);
}