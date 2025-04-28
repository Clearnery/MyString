#include <cstring>
#include "MyString.h"
#include "Text.h"
#include <iostream>

int main() 
{
    // Создаем редактор с полем ввода длиной 15 символов
    TextEditor editor(15);

    // Устанавливаем позицию в консоли (колонка 10, строка 5)
    editor.setPosition(10, 5);

    std::cout << "Однострочный текстовый редактор\n";
    std::cout << "Нажмите Enter в редакторе для завершения ввода\n\n";

    // Отображаем редактор и запускаем ввод
    editor.display();
    editor.run();

    // Получаем введенную строку
    MyString input = editor.getContent();
    std::cout << "\n\nВы ввели: " << input << std::endl;

    // Демонстрация дополнительных методов класса MyString
    std::cout << "\nДемонстрация работы со строкой:\n";
    std::cout << "Дублирование строки 3 раза: " << input.duplicate(3) << std::endl;
    std::cout << "Наиболее частый символ: " << input.mostFrequentChar() << std::endl;

    std::cout << "Уникальные символы: ";
    for (char c : input.uniqueChars()) 
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}