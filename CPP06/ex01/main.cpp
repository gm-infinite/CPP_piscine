#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main(void)
{
    Data original(42);

    std::cout << "=== Original ===" << std::endl;
    std::cout << "Address: " << &original << std::endl;
    std::cout << "Value:   " << original.getdata_int() << std::endl;

    uintptr_t serialized = Serializer::serialize(&original);
    std::cout << "\n=== Serialized ===" << std::endl;
    std::cout << "Raw: " << serialized << std::endl;

    Data* restored = Serializer::deserialize(serialized);
    std::cout << "\n=== Deserialized ===" << std::endl;
    std::cout << "Address: " << restored << std::endl;
    std::cout << "Value:   " << restored->getdata_int() << std::endl;

    std::cout << "\n=== Verification ===" << std::endl;
    if (restored == &original)
        std::cout << "SUCCESS: Pointers match!" << std::endl;
    else
        std::cout << "FAILURE: Pointers don't match!" << std::endl;

    return 0;
}