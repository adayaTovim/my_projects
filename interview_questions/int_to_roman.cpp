#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<int,std::string> roman = {{1,"I"},{5,"V"},{10,"X"},{50,"L"},{100,"C"},{500,"D"},{1000,"M"}};

std::string intToRoman(int a_num)
{
    if(a_num < 0 || a_num > 3999) {
        return "invalid input";
    }

    std::string result = "";
    for(const auto& pair : roman) {
        int value = pair.first;
        std::string str = pair.second;

        while(a_num >= value) {
            result += str;
            a_num -= value;
        }
    }
    return result;
}

// naive case
// std::string intToRoman(int a_num)
// {
//     std::string str = "";
//     if(a_num < 0 || a_num > 3999) {
//         return str;
//     }

//     while(a_num > 0) {
//         if(a_num >= 1000) {
//             str = str + roman[1000];
//             a_num = a_num - 1000;
//             continue;
//         } else if(a_num >= 500) {
//             str = str + roman[500];
//             a_num = a_num - 500;
//             continue;
//         } else if(a_num >= 100) {
//             str = str + roman[100];
//             a_num = a_num - 100;
//             continue;
//         } else if(a_num >= 50) {
//             str = str + roman[50];
//             a_num = a_num - 50;
//             continue;
//         } else if(a_num >= 10) {
//             str = str + roman[10];
//             a_num = a_num - 10;
//             continue;
//         } else if(a_num >= 5) {
//             str = str + roman[5];
//             a_num = a_num - 5;
//             continue;
//         } else if(a_num >= 1) {
//             str = str + roman[1];
//             a_num = a_num - 1;
//             continue;
//         }
//     }
//     return str;
// }

int main()
{
    int num = 100;
    std::string result = intToRoman(num);

    std::cout<<result<<"\n";

    return 0;
}
