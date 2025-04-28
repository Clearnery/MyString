#ifndef TEXT_H
#define TEXT_H

#include "String.h"
#include <windows.h>

class TextEditor 
{
private:
    MyString content;
    int fieldLength;
    COORD position;
    HANDLE consoleHandle;

public:
    TextEditor();
    explicit TextEditor(int length);

    void setFieldLength(int length);
    int getFieldLength() const;

    void setPosition(int x, int y);
    COORD getPosition() const;

    void display() const;
    void run();

    const MyString& getContent() const;
};

#endif 