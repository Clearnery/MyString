#include <cstring>
#include "MyString.h"
#include <cstdlib>
#include <algorithm>



void MyString::freeMemory() 
{
    delete[] data;
    data = nullptr;
    length = 0;
}

void MyString::copyFrom(const MyString& other) 
{
    length = other.length;
    data = new char[length + 1];
    std::strcpy(data, other.data);
}

void MyString::moveFrom(MyString&& other) noexcept 
{
    data = other.data;
    length = other.length;
    other.data = nullptr;
    other.length = 0;
}

MyString::MyString() : data(nullptr), length(0) {
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* str) : data(nullptr), length(0) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }
    else {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
}

MyString MyString::substr(size_t start, size_t len) const
{
    if (start >= length) return MyString();

    len = (start + len > length) ? (length - start) : len;
    char* newData = new char[len + 1];
    strncpy(newData, data + start, len);
    newData[len] = '\0';
    return MyString(newData);
}

MyString::MyString(const MyString& other) : data(nullptr), length(0) {
    copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept : data(nullptr), length(0) {
    moveFrom(std::move(other));
}

MyString::~MyString() {
    freeMemory();
}

const char* MyString::c_str() const {
    return data ? data : "";
}

size_t MyString::size() const {
    return length;
}

bool MyString::empty() const {
    return length == 0;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

MyString MyString::operator+(const MyString& other) const {
    MyString result;
    result.length = length + other.length;
    result.data = new char[result.length + 1];
    std::strcpy(result.data, data);
    std::strcat(result.data, other.data);
    return result;
}

MyString MyString::operator*(size_t k) const {
    if (k == 0) return MyString();

    MyString result;
    result.length = length * k;
    result.data = new char[result.length + 1];
    result.data[0] = '\0';

    for (size_t i = 0; i < k; ++i) {
        std::strcat(result.data, data);
    }

    return result;
}

bool MyString::operator==(const MyString& other) const {
    if (length != other.length) return false;
    return std::strcmp(data, other.data) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator<(const MyString& other) const {
    return std::strcmp(data, other.data) < 0;
}

bool MyString::operator>(const MyString& other) const {
    return std::strcmp(data, other.data) > 0;
}

char& MyString::operator[](size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const char& MyString::operator[](size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << (str.data ? str.data : "");
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[1024];
    is >> buffer;
    str = MyString(buffer);
    return is;
}

int MyString::findFirst(const MyString& substr) const {
    if (substr.length == 0) return 0;
    if (length < substr.length) return -1;

    const char* pos = strstr(data, substr.data);
    return pos ? pos - data : -1;
}

int MyString::findFirst(char c) const {
    const char* pos = strchr(data, c);
    return pos ? pos - data : -1;
}

std::vector<MyString> MyString::split(char delimiter) const {
    std::vector<MyString> result;
    if (length == 0) return result;

    size_t start = 0;
    for (size_t i = 0; i <= length; ++i) {
        if (data[i] == delimiter || data[i] == '\0') {
            if (i > start) {
                char* temp = new char[i - start + 1];
                std::strncpy(temp, data + start, i - start);
                temp[i - start] = '\0';
                result.emplace_back(temp);
                delete[] temp;
            }
            start = i + 1;
        }
    }

    return result;
}

MyString MyString::duplicate(size_t k) const {
    return *this * k;
}

std::vector<int> MyString::findAll(const MyString& substr) const {
    std::vector<int> positions;
    if (substr.length == 0 || substr.length > length) return positions;

    size_t pos = 0;
    while ((pos = findFirst(substr)) != -1) {
        positions.push_back(pos);
        pos += substr.length;
    }

    return positions;
}

char MyString::mostFrequentChar() const {
    if (length == 0) return '\0';

    std::unordered_map<char, int> freq;
    for (size_t i = 0; i < length; ++i) {
        freq[data[i]]++;
    }

    return std::max_element(freq.begin(), freq.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; })->first;
}

std::vector<char> MyString::uniqueChars() const {
    std::vector<char> result;
    if (length == 0) return result;

    bool seen[256] = { false };
    for (size_t i = 0; i < length; ++i) {
        if (!seen[static_cast<unsigned char>(data[i])]) {
            seen[static_cast<unsigned char>(data[i])] = true;
            result.push_back(data[i]);
        }
    }

    return result;
}
