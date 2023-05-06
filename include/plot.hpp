#pragma once

/*
    plot data to matplotlib
*/
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
class Plot{

    public:
    Plot(std::string path_python_env):m_path_python(path_python_env)
    {
        init();
        m_pythonCode << R"(
import sys
import matplotlib.pyplot as plt)";
    }
    ~Plot(){};
    template<typename T>
    void operator() (T& x, T& y)
    {
        // std::string x_str = arrayToString(x),
        //             y_str = arrayToString(y);
        // std::string code = "\""+getPythonCode() + "\"" + " "+ x_str + " "+ y_str;
        // executedPythonCode(code);
    }
    template<typename T>
    void plot(T& x, T&y,
                std::string plot_type="r-", int linewidth=3, int markersize=3)
    {
        std::string x_str = arrayToString(x),
                    y_str = arrayToString(y);
                    m_input << add_input(x_str, y_str).str();
                    m_pythonCode << add_plot(plot_type, linewidth, markersize).str();
    }

    void show(
        std::string x_title="x_title",
        std::string y_title="y_title",
        std::string title="title"
    )
    {
        
        m_pythonCode << "plt.xlabel(\'"<<x_title <<"\')\n";
        m_pythonCode << "plt.ylabel(\'" << y_title << "\')\n";
        m_pythonCode << "plt.title(\'" << title << "\')\n";
        m_pythonCode << "plt.show()\n";
        
        std::string result = "\""+m_pythonCode.str()+"\" "+m_input.str();
        executedPythonCode(result);
    }

    private:
    std::string m_path_python;
    std::stringstream m_input{};
    std::stringstream m_pythonCode{};
    std::size_t m_input_num{0};
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
        // std::cout<<command<<"\n";
        system(command.c_str());
    }

    std::stringstream add_input(std::string& x, std::string& y)
    {
        std::stringstream data;
        data<<x<<" "<<y<<" ";
        return data;
    }

    std::stringstream add_plot(
                        const std::string plot_type="r*",
                        const int linewidth=2,
                        const int markersize=3
                        )
    {
        m_input_num +=2;
        std::stringstream data{};
        data << R"(
# Read data from command-line arguments
x = list(map(float, sys.argv[)"<<m_input_num-1<<R"(].split(',')))
y = list(map(float, sys.argv[)"<<m_input_num<<R"(].split(',')))
# Create a plot
)";
        // python_code += "\n";
        data << "plt.plot(x, y, \'"<<plot_type<<"\', linewidth="<<linewidth<<", markersize="<<markersize<<")\n";
        
        // std::cout<<data.str()<<"\n";
        return data;
    }

//     std::string m_python_code = R"(
// import sys
// import matplotlib.pyplot as plt

// # Read data from command-line arguments
// x = list(map(float, sys.argv[1].split(',')))
// y = list(map(float, sys.argv[2].split(',')))

// # Create a plot
// plt.plot(x, y)
// plt.xlabel('X axis label')
// plt.ylabel('Y axis label')
// plt.title('Plot title')
// plt.show()
//     )";

};