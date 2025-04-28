#include "MyString.h"
#include "Text.h"
#include <conio.h>
#include <cstdlib>
#include <cstring>

// Конструкторы
TextEditor::TextEditor()
    : fieldLength(20),
    consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
{
    position.X = 0;
    position.Y = 0;
}

TextEditor::TextEditor(int length)
    : fieldLength(length > 0 ? length : 20),
    consoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
{
    position.X = 0;
    position.Y = 0;
}

// Установка длины поля с обрезкой содержимого
void TextEditor::setFieldLength(int length)
{
    fieldLength = (length < 0) ? 0 : length;
    if (content.size() > static_cast<size_t>(fieldLength))
    {
        content = content.substr(0, fieldLength);
    }
}

// Установка позиции в консоли
void TextEditor::setPosition(int x, int y)
{
    position.X = static_cast<SHORT>(x);
    position.Y = static_cast<SHORT>(y);
}

// Отображение текстового поля
void TextEditor::display() const
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    COORD originalPos = csbi.dwCursorPosition;

    SetConsoleCursorPosition(consoleHandle, position);

    std::cout << "[";
    for (int i = 0; i < fieldLength; ++i)
    {
        std::cout << (i < static_cast<int>(content.size()) ? content[i] : ' ');
    }
    std::cout << "]";

    SetConsoleCursorPosition(consoleHandle, originalPos);
}

// Основной цикл ввода
void TextEditor::run()
{
    content = MyString(); // Сброс содержимого

    COORD inputPos = position;
    inputPos.X += 1;
    SetConsoleCursorPosition(consoleHandle, inputPos);

    int ch;
    while ((ch = _getch()) != 13) // Enter для завершения
    {
        if (ch == 8) // Backspace
        {
            if (!content.empty())
            {
                content = content.substr(0, content.size() - 1);
                display();
            }
        }
        else if (isprint(ch) && content.size() < static_cast<size_t>(fieldLength))
        {
            // Создаем MyString из одного символа
            char tempStr[] = { static_cast<char>(ch), '\0' };
            content = content + MyString(tempStr);
            display();
        }
    }
}

const MyString& TextEditor::getContent() const
{
    return content;
}