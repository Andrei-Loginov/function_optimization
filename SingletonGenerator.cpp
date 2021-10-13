#include "SingletonGenerator.h"

std::mt19937 SingletonGenerator::mersennetwister;

std::mt19937& SingletonGenerator::get_mt(){
    return mersennetwister;
}
