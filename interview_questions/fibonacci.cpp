#include <iostream>
#include <utility>

// Write an efficient function to calculate the nth Fibonacci number.

// recursive implementation
int fibonacci(int n) {
    if (n < 0) {
        throw std::invalid_argument("Input cannot be negative");
    }

    if (n == 0) {
        return 0;
    }

	else if (n == 1) {
        return 1;
    }

	else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

// // naive implementation
// int fibonacci(int n)
// {
// 	if (n < 0) {
// 		throw std::invalid_argument("Input cannot be negative");
// 	}

// 	if(n  == 0 || n  == 1) {
// 		return n;
// 	}

// 	int previousNum = 0;
// 	int currentNum = 1;
// 	int i = 2;
// 	while (i <= n) {
// 		int nextNum = previousNum + currentNum;
// 		previousNum = currentNum;
// 		currentNum = nextNum;
// 		++i;
// 	}

// 	return currentNum;
// }

int main() {
	try {
		std::cout<<fibonacci(3)<<std::endl;; // 2
		std::cout<<fibonacci(9)<<std::endl;; // 34
		std::cout<<fibonacci(-2)<<std::endl;; // error
	}

	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
