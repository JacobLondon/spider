#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string SP_EXT = ".sp";
const std::string WEB_BIN = "web";
std::string generated_fname = "sp.out.cpp";
std::string spider_fname = "";
std::string bin_fname = "a.out";
bool compile = false;
bool clean = false;
bool run = false;

void argparse(int argc, char** argv);
void build();

int main(int argc, char** argv)
{
    argparse(argc, argv);
    build();

    return 0;
}

void argparse(int argc, char** argv)
{
    std::vector<std::string> args(argv + 1, argv + argc);

    // parse arguments
    for (int i = 0; i < args.size(); i++) {
        // find spider file extension
        if (args[i].find(SP_EXT) != std::string::npos)
            spider_fname = args[i];

        // parse optional args
        else if (args[i][0] == '-') {
            switch(args[i][1]) {
            // specify to compile the generated file
            case 'c':
                clean = true;
                break;
            // specify generated_fname
            case 'g':
                if (i + 1 < argc && args[i + 1][0] != '-') generated_fname = args[++i]; // else default
                break;
            // specify to compile and allow a bin name
            case 'o':
                compile = true;
                if (i + 1 < argc && args[i + 1][0] != '-') bin_fname = args[++i]; // else default
                break;
            // specify to run the binary after compiling it
            case 'r':
                run = true;
                break;
            }
        }
    }

    if (spider_fname == "") {
        std::cerr << "Spider input file missing from argument list." << std::endl;
        exit(-1);
    }
}

void build()
{
    std::string command = "";

    // generate cpp file
    command += "cat " + spider_fname + " | " + WEB_BIN + " " + spider_fname + " > " + generated_fname;
    system(command.c_str());

    // generate Makefile
    if (compile) {
        command = "g++ " + generated_fname + " -o " + bin_fname;
        system(command.c_str());
    }

    if (run) {
        command = "./" + bin_fname;
        system(command.c_str());
    }

    if (clean) {
        command = "rm " + generated_fname + " " + bin_fname;
        system(command.c_str());
    }
}