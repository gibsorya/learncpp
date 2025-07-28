#include <iostream>

// forward declaration so the compiler knows about the function and doesn't complain :)
int add(int a, int b);

int main() {
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << "\n";

    return 0;
}
