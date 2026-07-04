#include <iostream>
#include <string>
#include <locale>

using namespace std;

class Dollar
{
public:
    unsigned int getCourse() { return 76; }
    string getName() { return "Доллар"; }
};

class Euro
{
public:
    unsigned int getCourse() { return 84; }
    string getName() { return "Евро"; }
};

class Pound
{
public:
    unsigned int getCourse() { return 98; }
    string getName() { return "Фунт"; }
};

class Ruble
{
public:
    virtual ~Ruble() {}
    virtual double convert(double amount) = 0;
    virtual void showCourse() = 0;
};

class ConverterDollarToRuble : public Dollar, public Ruble
{
public:
    double convert(double amount) override {
        return amount * getCourse();
    }
    void showCourse() override
    {
        cout << "Курс " << getName() << " к рублю: " << getCourse() << endl;
    }
};

class ConverterEuroToRuble : public Euro, public Ruble
{
public:
    double convert(double amount) override {
        return amount * getCourse();
    }

    void showCourse() override
    {
        cout << "Курс " << getName() << " к рублю: " << getCourse() << endl;
    }
};

class ConverterPoundToRuble : public Pound, public Ruble
{
public:
    double convert(double amount) override {
        return amount * getCourse();
    }
    void showCourse() override
    {
        cout << "Курс " << getName() << " к рублю: " << getCourse() << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Добро пожаловать." << endl;
    cout << "Выберите валюту, которую будете обменивать на рубли:" << endl;
    cout << "1. Доллар" << endl;
    cout << "2. Евро" << endl;
    cout << "3. Фунт" << endl;

    int choice;
    cin >> choice;

    Ruble* converter = nullptr;

    switch (choice)
    {
    case 1:
    {
        converter = new ConverterDollarToRuble();
        break;
    }
    case 2:
    {
        converter = new ConverterEuroToRuble();
        break;
    }
    case 3:
    {
        converter = new ConverterPoundToRuble();
        break;
    }
    default:
        cout << "Неверный выбор!" << endl;
        return 0;
    }

    converter->showCourse();

    double amount;
    cout << "Введите сумму: ";
    cin >> amount;

    cout << "В рублях: " << converter->convert(amount) << endl;

    delete converter;

    return 0;
}