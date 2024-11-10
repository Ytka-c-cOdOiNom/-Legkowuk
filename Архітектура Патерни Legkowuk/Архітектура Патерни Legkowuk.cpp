#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <windows.h>
using namespace std;

// Клас для представлення шрифта
class Font {
public:
    string name;
    int size;

    Font(const string& name, int size) : name(name), size(size) {}

    void display() const {
        cout << "Шрифт: " << name << ", Розмір: " << size << endl;
    }
};

// Клас для представлення тексту
class Text {
private:
    string content;
    shared_ptr<Font> font;  // Спільний шрифт

public:
    Text(const string& content, shared_ptr<Font> font)
        : content(content), font(font) {}

    void display() const {
        cout << "Текст: " << content << endl;
        font->display();
    }
};

// Клас для фабрики шрифтів (для економії пам'яті)
class TextFactory {
private:
    unordered_map<string, shared_ptr<Font>> fonts;

public:
    shared_ptr<Font> getFont(const string& name, int size) {
        string key = name + to_string(size);  // Створюємо унікальний ключ для кожного шрифта
        if (fonts.find(key) == fonts.end()) {
            fonts[key] = make_shared<Font>(name, size);  // Якщо такого шрифта немає, створюємо новий
            cout << "Створено новий шрифт: " << name << " " << size << endl;
        }
        return fonts[key];
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TextFactory factory;

    // Створення текстів
    shared_ptr<Font> font1 = factory.getFont("Arial", 12);
    shared_ptr<Font> font2 = factory.getFont("Arial", 14);

    Text text1("Привіт, світ!", font1);
    Text text2("Це патерн легковаговик", font1);
    Text text3("Інший текст", font2);

    // Виведення текстів
    text1.display();
    text2.display();
    text3.display();


}
