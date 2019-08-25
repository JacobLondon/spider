#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string SP_EXT = ".sp";
const std::string SP_BIN = "spider";
std::string generated_fname = "sp.out.cpp";
std::string spider_fname = "";
std::string bin_fname = "a.out";
bool make = false;
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
            case 'c':
                clean = true;
                break;
            case 'g':
                if (i + 1 < argc && args[i + 1][0] != '-') generated_fname = args[++i]; // else default
                break;
            case 'o':
                make = true;
                if (i + 1 < argc && args[i + 1][0] != '-') bin_fname = args[++i]; // else default
                break;
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
    command += "cat " + spider_fname + " | " + SP_BIN + " " + spider_fname + " > " + generated_fname;
    system(command.c_str());

    std::string cleaner = "rm " + generated_fname + " Makefile";

    // generate Makefile
    if (make) {
        std::ofstream makefile;
        makefile.open("Makefile");
        makefile << "CC=g++\n"
                 << "TARGET=" + bin_fname + "\n"
                 << "all:\n"
                 << "\t$(CC) -o " + bin_fname + " " + generated_fname + "\n"
                 << "clean:\n"
                 << "\t" + cleaner + " " + bin_fname + "\n";
        makefile.close();
        system("make");
    }

    if (clean) {
        system(cleaner.c_str());
    }

    if (run) {
        command = "./" + bin_fname;
        system(command.c_str());
    }
}