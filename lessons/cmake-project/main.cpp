#include <iostream>
#include "config.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << CMakeProject_VERSION_MAJOR << "."
                  << CMakeProject_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
      }

    return 0;
}
