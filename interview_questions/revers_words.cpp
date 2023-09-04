#include <iostream>
#include <string>

void reverseStr(std::string& a_word, int a_start, int a_end) {
    while (a_start < a_end) {
        std::swap(a_word[a_start], a_word[a_end]);
        ++a_start;
        --a_end;
    }
}

void reverseWordsInStr(std::string& a_str) {

	int length = a_str.length();
	if(length < 3) {
		return;
	}

	int start = 0;
    int end = length - 1;

    //revers all string
    reverseStr(a_str, start, end);
    std::cout<<a_str<<std::endl;

    for (int i = 0; i <= end; ++i) {
        if (a_str[i] == ' ') {
            //revers each word
            reverseStr(a_str, start, i - 1);
            start = i + 1;
        }
        else if (i == end) {
            reverseStr(a_str, start, i);
        }
    }
}

int main() {
    std::string str1 = "hello world";
    reverseWordsInStr(str1);

    std::cout << str1 << "\n"; // prints "world hello"

    return 0;
}
