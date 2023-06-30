#pragma once

#include <filesystem>
#include <fstream>
#include <cassert>

class CSV
{
    public:
    CSV(std::filesystem::path const& filepath);

    private:
    std::ifstream m_file;
};

CSV::CSV(std::filesystem::path const& filepath):m_file{filepath}
{
    assert(m_file.is_open());

}