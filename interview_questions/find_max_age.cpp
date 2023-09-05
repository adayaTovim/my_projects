#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

int findMaxAgeInFile(const std::string& a_filename) {
    std::ifstream file(a_filename);
    if (!file) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return -1;
    }

    std::unordered_map<std::string, int> nameAndAge;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int age;
        if (iss >> name >> age) {
            nameAndAge[name] = age;
        }
    }

    file.close();

    // search for the maximum age in the map
    int maxAge = -1;
    for (const auto& i : nameAndAge) {
        if (i.second > maxAge) {
            maxAge = i.second;
        }
    }

    return maxAge;
}

int main() {
    std::string filename = "data.txt";

    int maxAge = findMaxAgeInFile(filename);

    if (maxAge != -1) {
        std::cout << "Maximum age is: " << maxAge << std::endl;
    } else {
        std::cout << "No data found in the file." << std::endl;
    }

    return 0;
}
