#include <iostream>

#define MY_NAME "Ryan"
#define SAY_MY_NAME

int main() {
#ifdef SAY_MY_NAME
    std::cout << "My name is " << MY_NAME << std::endl;
#endif

#ifdef DONT_SAY_MY_NAME
    std::cout << "My name is not Ryan" << std::endl;
#endif

    return 0;
}
