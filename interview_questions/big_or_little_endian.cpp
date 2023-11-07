#include <iostream>
#include <cstdint>

bool isLittleEndian() {
    int num = 0x00000001;
    int* byte = static_cast<int*>(&num);
    return (*byte == 1);
}

int main() {
    if (isLittleEndian()) {
        std::cout << "Little-Endian" << std::endl;
    } else {
        std::cout << "Big-Endian" << std::endl;
    }

    return 0;
}
