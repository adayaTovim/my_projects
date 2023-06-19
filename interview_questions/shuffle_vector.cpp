//64. Given a vector of T element write a function to shuffle the element.
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::vector<int> shuffleVector(std::vector<int> a_vector) {
	if(a_vector.empty() || a_vector.size() == 1) {
		return a_vector;
	}

    std::vector<int> result;

    while (!a_vector.empty()) {
        int index = std::rand() % a_vector.size();
        // check valid index
		if (index < 0 || index >= a_vector.size()) {
			throw std::range_error("error generating");
        }

        int element = a_vector[index];
        result.push_back(element);
        a_vector.erase(a_vector.begin() + index);
    }

    return result;
}

//with using std::shuffle
// std::vector<int> shuffleVector(std::vector<int> a_vector) {
// 	if(a_vector.empty() || a_vector.size() == 1) {
// 		return a_vector;
// 	}
//     std::default_random_engine rng(std::random_device{}());

//     // shuffle the vector using std::shuffle
//     std::shuffle(a_vector.begin(), a_vector.end(), rng);

//     return a_vector;
// }

void printVector(std::vector<int> a_vector) {
    for(size_t i = 0; i < a_vector.size(); ++i) {
        std::cout<<a_vector[i]<<" ";
    }
    std::cout<<"\n";
}

int main() {
    std::vector<int> vec;
    for(int i = 1; i < 101; ++i) {
        vec.push_back(i);
    }

	std::cout << "vector: ";
    printVector(vec);
    try
	{
		vec = shuffleVector(vec);
		std::cout << "after shuffle: ";
		printVector(vec);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

    return 0;
}
