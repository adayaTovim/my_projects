// Describe a data structure for which getValue(int index), setValue(int index, int value), and setAllValues(int value) are all O(1).

#include <iostream>
#include <vector>

class grades {
public:
    explicit grades(int a_grade = 0) : m_setAll(a_grade),
                                m_grades(10, a_grade), m_setAllflags(10, false) {}

    void set(int a_index, int a_grade) {
        if (a_index < 0 || a_index >= static_cast<int>(m_grades.size())) {
            std::cerr << "Out of range\n";
        } else {
            m_grades[a_index] = a_grade;
            m_setAllflags[a_index] = false;
        }
    }

    void setAll(int a_grade) {
        m_setAll = a_grade;
    	std::vector<bool>(10, true).swap(m_setAllflags); // replace old vector with new vector
    }

    int get(int a_index) {
        if (a_index < 0 || a_index >= static_cast<int>(m_grades.size())) {
            std::cerr << "Out of range\n";
            return -1;
        }
        if(m_setAllflags[a_index]){
            m_grades[a_index] = m_setAll;
            m_setAllflags[a_index] = false;
            return m_grades[a_index];
        } else {
            return m_grades[a_index];
        }
    }

private:
    std::vector<int> m_grades;
    std::vector<bool> m_setAllflags;
    int m_setAll;
};

int main()
{
    grades myGrades;
    myGrades.setAll(100);
    myGrades.set(2, 90);
    myGrades.set(3, 80);

    //myGrades.setAll(0);

    for (int i = 0; i < 10; ++i) {
        std::cout << "Grade " << i << ": " << myGrades.get(i) << std::endl;
    }

    return 0;
}

// another way without swap between vectors is to use clock



