#pragma once
#include <vector>

namespace krain
{
class Tensor1D
{
    public:
        Tensor1D(std::size_t size):m_size{size}, m_data(size)
        {

        }

        float get(std::size_t pos)
        {
            return m_data[pos];
        }

        void set(float value, std::size_t x)
        {
            m_data[x] = value;
        }

    private:
        std::vector<float> m_data;
        std::size_t m_size;
};

class Tensor2D
{
    public:
        Tensor2D(std::size_t x, std::size_t y):m_x{x}, m_y{y}, m_data(x*y)
        {

        }
        float get(std::size_t x, std::size_t y);
        float set(float value, std::size_t x, std::size_t y);
    private:
        std::vector<float> m_data;
        std::size_t m_x, m_y;

};

class Tensor3D
{
    public:
        Tensor3D(std::size_t x, std::size_t y, std::size_t z):m_x{x}, m_y{y}, m_z{z}, m_data(x*y*z)
        {

        }
        float get (std::size_t x, std::size_t y, std::size_t z) const
        {
            return m_data[x];
        }
        void set(float value, std::size_t x, std::size_t y, std::size_t z)
        {
            m_data[x] = value;
        }
    private:
        std::vector<float> m_data;
        std::size_t m_x, m_y, m_z;

};
}