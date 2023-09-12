//implement a function to convert an integer column number (used in Excel spreadsheets) into its corresponding column label
//(e.g., 1 -> "A", 2 -> "B", 27 -> "AA", etc.).

#include <unordered_map>
#include <iostream>

std::string findExcelColumn(int a_col)
{
    std::string result ="";
    while(a_col > 0) {
        int remainder = (a_col - 1) % 26;
        char colChar = 'A' + remainder;
        result += colChar;
        a_col = (a_col - 1) /  26;
    }


    return result;
}

int main()
{
    std::cout<<findExcelColumn(27)<<std::endl;

    return 0;
}

