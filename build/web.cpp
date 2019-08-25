#include <cstdlib>
#include <string>
#include <vector>

const std::string SP_EXT = ".sp";
const std::string SP_BIN = "spider";
std::string fout = "sp.out.cpp";
std::string fname = "";
std::string command = "";

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv + 1, argv + argc);

    for (int i = 0; i < args.size(); i++) {
        if (args[i].find(SP_EXT) != std::string::npos)
            fname = args[i];
        else if (args[i] == "-o") {
            fout = args[++i];
        }

    }

    command += "cat " + fname + " | " + SP_BIN + " " + fname + " > " + fout;

    system(command.c_str());
    return 0;
}