//given an array of incomes and dates, calculate the total incomes in year.

#include <iostream>
#include <vector>
#include <string>

struct IncomeRecord {
    double m_income;
    std::string m_date; //in DD.MM.YYYY format
};

double calculateTotalIncomeInYear(const std::vector<IncomeRecord>& a_incomeRecords, int a_year) {
    double totalIncome = 0.0;

    for (auto record : a_incomeRecords) {
        std::string yearStr = record.m_date.substr(6, 4);
        int year = std::stoi(yearStr);

        if (year == a_year) {
            totalIncome += record.m_income;
        }
    }

    return totalIncome;
}

int main() {
    std::vector<IncomeRecord> incomeRecords = {
        {10000.0, "15.01.2023"},
        {12000.0, "15.02.2023"},
        {8000.0, "15.03.2023"},
        {15000.0, "15.03.2024"},
        {15000.0, "15.03.2024"},
        {15000.0, "15.03.2024"},
        {15000.0, "15.03.2024"}

    };

    double total2023 = calculateTotalIncomeInYear(incomeRecords, 2023);
    double total2024 = calculateTotalIncomeInYear(incomeRecords, 2023);
    double total2025 = calculateTotalIncomeInYear(incomeRecords, 2025);

    std::cout << "Total income in year 2023" << ": $" << total2023 << std::endl;
    std::cout << "Total income in year 2024" << ": $" << total2024 << std::endl;
    std::cout << "Total income in year 2025" << ": $" << total2025 << std::endl;

    return 0;
}

