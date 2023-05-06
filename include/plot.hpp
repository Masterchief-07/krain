#pragma once

/*
    plot data to matplotlib
*/
#include <string>
#include <cstdlib>


class Plot{

    public:
    Plot(std::string path_python_env):m_path_python(path_python_env)
    {
        init();
    }
    ~Plot(){};
    template<typename T>
    void operator() (T& x, T& y)
    {
        std::string x_str = arrayToString(x),
                    y_str = arrayToString(y);
        std::string code = "\""+m_python_code + "\"" + " "+ x_str + " "+ y_str;
        executedPythonCode(code);
    }

    private:
    std::string m_path_python;
    template<typename T>
    std::string arrayToString(const T& values, const std::string separator=",")
    {
        std::string data;
        for (int i=0; i<values.size()-1; i++)
            data += std::to_string(values[i]) + separator;
        data+= std::to_string(values[values.size()-1]);

        return data;
    };
    void init()
    {
        std::string code =  "import tkinter\nimport matplotlib";
        code = "\"" + code + "\"";
        executedPythonCode(code);
    }
    void executedPythonCode(std::string& code)
    {
        std::string command = m_path_python+" -c " + code;
        system(command.c_str());
    }


    std::string m_python_code = R"(
import sys
import matplotlib.pyplot as plt

# Read data from command-line arguments
x = list(map(float, sys.argv[1].split(',')))
y = list(map(float, sys.argv[2].split(',')))

# Create a plot
plt.plot(x, y)
plt.xlabel('X axis label')
plt.ylabel('Y axis label')
plt.title('Plot title')
plt.show()
    )";

};