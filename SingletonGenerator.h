#ifndef SINGLETONGENERATOR_H
#define SINGLETONGENERATOR_H
#include <random>


class SingletonGenerator
{
    static std::mt19937 mersennetwister;
public:
    static std::mt19937& get_mt();
};

#endif // SINGLETONGENERATOR_H
