// Design a text editor with a cursor that can do the following:

// Add text to where the cursor is.
// Delete text from where the cursor is (simulating the backspace key).
// Move the cursor either left or right.
// When deleting text, only characters to the left of the cursor will be deleted. The cursor will also remain within the actual text and cannot be moved beyond it. More formally, we have that 0 <= cursor.position <= currentText.length always holds.

// Implement the TextEditor class:

// TextEditor() Initializes the object with empty text.
// void addText(string text) Appends text to where the cursor is. The cursor ends to the right of text.
// int deleteText(int k) Deletes k characters to the left of the cursor. Returns the number of characters actually deleted.
// string cursorLeft(int k) Moves the cursor to the left k times. Returns the last min(10, len) characters to the left of the cursor, where len is the number of characters to the left of the cursor.
// string cursorRight(int k) Moves the cursor to the right k times. Returns the last min(10, len) characters to the left of the cursor, where len is the number of characters to the left of the cursor.


// Example 1:

// Input
// ["TextEditor", "addText", "deleteText", "addText", "cursorRight", "cursorLeft", "deleteText", "cursorLeft", "cursorRight"]
// [[], ["leetcode"], [4], ["practice"], [3], [8], [10], [2], [6]]
// Output
// [null, null, 4, null, "etpractice", "leet", 4, "", "practi"]

// Explanation
// TextEditor textEditor = new TextEditor(); // The current text is "|". (The '|' character represents the cursor)
// textEditor.addText("leetcode"); // The current text is "leetcode|".
// textEditor.deleteText(4); // return 4
//                           // The current text is "leet|".
//                           // 4 characters were deleted.
// textEditor.addText("practice"); // The current text is "leetpractice|".
// textEditor.cursorRight(3); // return "etpractice"
//                            // The current text is "leetpractice|".
//                            // The cursor cannot be moved beyond the actual text and thus did not move.
//                            // "etpractice" is the last 10 characters to the left of the cursor.
// textEditor.cursorLeft(8); // return "leet"
//                           // The current text is "leet|practice".
//                           // "leet" is the last min(10, 4) = 4 characters to the left of the cursor.
// textEditor.deleteText(10); // return 4
//                            // The current text is "|practice".
//                            // Only 4 characters were deleted.
// textEditor.cursorLeft(2); // return ""
//                           // The current text is "|practice".
//                           // The cursor cannot be moved beyond the actual text and thus did not move.
//                           // "" is the last min(10, 0) = 0 characters to the left of the cursor.
// textEditor.cursorRight(6); // return "practi"
//                            // The current text is "practi|ce".
//                            // "practi" is the last min(10, 6) = 6 characters to the left of the cursor.



#include <iostream>
#include <string>
#include <cstring>


class TextEditor {
public:
    std::string m_leftText = "";
    std::string m_rightText="";

    TextEditor() {}

    void addText(std::string text) {
        m_leftText += text;
    }

    int deleteText(int k) {
        // find how much we need to delete
        k = std::min(k, (int)m_leftText.size());
        m_leftText.erase((int)m_leftText.size()-k,k);
        return k;
    }

    std::string cursorLeft(int k) {
        // ensure k doesn't exceed left text length
        k = std::min(k, static_cast<int>(m_leftText.size()));
        m_rightText = m_leftText.substr(m_leftText.size() - k) + m_rightText;
        m_leftText.erase(m_leftText.size() - k);

        return m_leftText.size() >= 10 ? m_leftText.substr(m_leftText.size() - 10) : m_leftText;
    }

    std::string cursorRight(int k) {
         // ensure k doesn't exceed right text length
        k = std::min(k, static_cast<int>(m_rightText.size()));
        m_leftText += m_rightText.substr(0, k);
        m_rightText.erase(0, k);

        return m_leftText.size() >= 10 ? m_leftText.substr(m_leftText.size() - 10) : m_leftText;
    }

};

// my old implementation is less efficient
// class TextEditor {
// private:
//     std::string m_str;
//     size_t m_cursor;

// public:
//     TextEditor() {
//         m_cursor = 0;
//     }

//     void addText(std::string text) {
//         size_t originalSize = m_str.size();
//         size_t textSize = text.size();

//         if(originalSize  == m_cursor) {
//             m_str += text;
//         } else {
//             std::string start = "";
//             for(size_t i = 0; i < m_cursor; ++i) {
//                 start += m_str[i];
//             }

//             std::string end = "";
//             for(size_t i = m_cursor; i < originalSize; ++i) {
//                 end += m_str[i];
//             }

//             m_str = start + text + end;
//         }
//         m_cursor += textSize;
//     }

//     int deleteText(int k) {
// 		if(m_cursor == 0) {
// 			return 0;
// 		}
//         int deleted = 0;
// 		while(m_cursor > 0 && k > 0) {
// 			m_str.erase(m_cursor - 1, 1);
//             --k;
//             ++deleted;
// 			--m_cursor;
//         }
//         return deleted;
//     }

//     std::string cursorLeft(int k) {
//         int newCursor = m_cursor;
//         int count = 0;
//         while(count < k && newCursor >= 0) {
//             --newCursor;
//             ++count;
//         }

//         if(k == count) {
//             m_cursor = newCursor;
//         }

//         std::string result = "";
//         for(int i = (m_cursor - 1); i >= 0 && result.size() < 10; --i) {
//             result = m_str[i] + result;
//         }

//         return result;
//     }

//     std::string cursorRight(int k) {
//         size_t size = m_str.size();
//         size_t newCursor = m_cursor;
//         int count = 0;
//         while(count < k && newCursor < size) {
//             ++newCursor;
//             ++count;
//         }

//         if(k == count) {
//             m_cursor = newCursor;
//         }

//         std::string result = "";
//         for(int i = (m_cursor - 1); i >= 0 && result.size() < 10; --i) {
//             result = m_str[i] + result;
//         }

//         return result;
//     }
// };


 int main()
 {
    TextEditor* obj = new TextEditor();
    obj->addText("leetcode");
    std::cout<<obj->deleteText(4)<<std::endl; //4
    obj->addText("practice");
    std::cout<<obj->cursorRight(3)<<std::endl; //"etpractice"
    std::cout<<obj->cursorLeft(8)<<std::endl;  //"leet"
    std::cout<<obj->deleteText(10)<<std::endl; //4
    std::cout<<obj->cursorLeft(2)<<std::endl;  //""
    std::cout<<obj->cursorRight(6)<<std::endl; //"practi"


    return 0;
 }
