#include <iostream>
#include <fstream>

#include "sexpr/oop_parser.h"

int main(int argc, char ** argv)
{
    if (argc != 2) {
        std::cout << "Expect one and only one parameter which should be the path to the sexp file to parse" << std::endl;
        return 0;
    }

    std::ifstream file_stream (argv[1], std::ifstream::in);
    if (!file_stream.good()) {
        std::cerr << "Could not open the file with the given path: " << argv[1] << std::endl;
        return -1;
    }

    try
    {
        std::cout << *sexpr::oop::parse(file_stream) << std::endl;
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "Could not parse the given file: " << argv[1] << std::endl;
        return -1;
    }
    return 0;
}

