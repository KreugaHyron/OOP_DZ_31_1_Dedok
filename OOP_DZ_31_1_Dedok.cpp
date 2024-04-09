#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
//класс MyString
class MyString {
private:
    char* str;
    int size;
public:
    MyString() : size(80) {
        str = new char[size + 1];
        for (int i = 0; i <= size; ++i) {
            str[i] = '\0';
        }
    }
    MyString(int customSize) : size(customSize) {
        str = new char[size + 1];
        for (int i = 0; i <= size; ++i) {
            str[i] = '\0';
        }
    }
    MyString(const char* initialStr) : size(strlen(initialStr)) {
        str = new char[size + 1];
        strcpy(str, initialStr);
    }
    MyString(const MyString& other) : size(other.size) {
        str = new char[size + 1];
        strcpy(str, other.str);
    }
    MyString(initializer_list<char> list) : size(list.size()) {
        str = new char[size + 1];
        int i = 0;
        for (char c : list) {
            str[i++] = c;
        }
        str[size] = '\0';
    }
    MyString(MyString&& other) noexcept : str(nullptr), size(0) {
        str = other.str;
        size = other.size;
        other.str = nullptr;
        other.size = 0;
    }
    ~MyString() {
        delete[] str;
    }
    void inputString() {
        cout << "Введите строку: ";
        cin >> str;
    }
    void outputString() const {
        cout << "String: " << str << "\n";
    }
    static int getCount() {
        static int count = 0;
        return count;
    }
    MyString& operator++() {
        char* temp = new char[size + 2];
        strcpy(temp, str);
        temp[size] = 'x';
        temp[size + 1] = '\0';
        delete[] str;
        str = temp;
        size++;
        return *this;
    }
    MyString& operator--() {
        if (size > 0) {
            str[size - 1] = '\0';
            size--;
        }
        return *this;
    }
    MyString operator+(int count) const {
        MyString result(*this);
        char* temp = new char[result.size + count + 1];
        strcpy(temp, result.str);
        for (int i = 0; i < count; ++i) {
            temp[result.size + i] = 'x';
        }
        temp[result.size + count] = '\0';
        delete[] result.str;
        result.str = temp;
        result.size += count;
        return result;
    }
    MyString operator-(int count) const {
        MyString result(*this);
        if (count >= result.size) {
            delete[] result.str;
            result.str = new char[1];
            result.str[0] = '\0';
            result.size = 0;
        }
        else {
            result.size -= count;
            result.str[result.size] = '\0';
        }
        return result;
    }
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            size = other.size;
            other.str = nullptr;
            other.size = 0;
        }
        return *this;
    }
    MyString operator++(int) {
        MyString temp(*this);
        ++(*this);
        return temp;
    }
    MyString operator--(int) {
        MyString temp(*this);
        --(*this);
        return temp;
    }
    friend MyString operator+(int count, const MyString& myString) {
        MyString result(count + myString.size);
        for (int i = 0; i < count; ++i) {
            result.str[i] = 'x';
        }
        strcpy(result.str + count, myString.str);
        return result;
    }

    friend ostream& operator<<(ostream& os, const MyString& myString) {
        os << myString.str;
        return os;
    }

    friend istream& operator>>(istream& is, MyString& myString) {
        char buffer[1000];
        is >> buffer;
        delete[] myString.str;
        myString.size = strlen(buffer);
        myString.str = new char[myString.size + 1];
        strcpy(myString.str, buffer);
        return is;
    }
};
int main()
{
    setlocale(LC_ALL, "RUS");
    MyString s = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    cout << "Введенная строка: " << s << endl;
}

