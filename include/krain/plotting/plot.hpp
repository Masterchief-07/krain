#pragma once

/*
    plot data to matplotlib
*/
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
class Plot{

    public:
    Plot(std::string path_python_env):m_path_python(path_python_env)
    {
        init();
        m_pythonCode << R"(
import sys
import matplotlib.pyplot as plt
x = []
y = []
with open('input.txt') as F:
    lines = F.readlines()
    for line in lines:
        x_, y_ = line.split(' ')
        # print(x_, '\n', y_)
        x_ = list(map(float, x_.split(',')))
        y_ = list(map(float, y_.split(',')))
        x.append(x_)
        y.append(y_)
)";
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
                    // m_input << addInput(x_str, y_str).str();
                    addInputInFile(x_str, y_str);
                    m_pythonCode << addPlot(plot_type, linewidth, markersize).str();
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
    void init()
    {
        std::string code =  "import tkinter\nimport matplotlib";
        code = "\"" + code + "\"";
        executedPythonCode(code);
    }
    template<typename T>
    std::string arrayToString(const T& values, const std::string separator=",")
    {
        std::string data;
        for (int i=0; i<values.size()-1; i++)
            data += std::to_string(values[i]) + separator;
        data+= std::to_string(values[values.size()-1]);

        return data;
    };
    void addInputInFile(std::string& x, std::string&y, std::string filename="input.txt")
    {
        std::ofstream file;
        if (m_input_num == 0)
            file.open(filename);
        else
            file.open(filename, std::ofstream::app);
        file << x<<" ";
        file << y<<"\n";
        file.close();
    }
    void executedPythonCode(std::string& code)
    {
        std::string command = m_path_python+" -c " + code;
        // std::cout<<command<<"\n";
        system(command.c_str());
    }

    std::stringstream addInput(std::string& x, std::string& y)
    {
        addInputInFile(x, y);
        std::stringstream data;
        data<<x<<" "<<y<<" ";
        return data;
    }

    std::stringstream addPlot(
                        const std::string plot_type="r*",
                        const int linewidth=2,
                        const int markersize=3
                        )
    {
        m_input_num +=1;
        std::stringstream data{};
        data << "plt.plot(x["<<m_input_num-1<<"], y["<<m_input_num-1<<"], \'"<<plot_type<<"\', linewidth="<<linewidth<<", markersize="<<markersize<<")\n";
        return data;
    }
};