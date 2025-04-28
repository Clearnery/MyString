#ifndef MYSTRING_H

#include <cstring>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

class MyString {
private:
    char* data;
    size_t length;

    void freeMemory();
    void copyFrom(const MyString& other);
    void moveFrom(MyString&& other) noexcept;

public:
    // Конструкторы и деструктор
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    // Методы доступа
    const char* c_str() const;
    size_t size() const;
    bool empty() const;

    // Операторы
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    MyString operator+(const MyString& other) const;
    MyString operator*(size_t k) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator>(const MyString& other) const;
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);

    // Методы работы со строками
    MyString substr(size_t start, size_t len) const;
    int findFirst(const MyString& substr) const;
    int findFirst(char c) const;
    std::vector<MyString> split(char delimiter) const;

    // Дополнительные методы
    MyString duplicate(size_t k) const;
    std::vector<int> findAll(const MyString& substr) const;
    char mostFrequentChar() const;
    std::vector<char> uniqueChars() const;
};

#endif 