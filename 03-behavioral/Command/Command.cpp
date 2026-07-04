#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

class Printer {
public:
    void turnOn() { cout << "[Принтер]: Включен" << endl; }
    void turnOff() { cout << "[Принтер]: Выключен" << endl; }
    void print() { cout << "[Принтер]: Печатает документ" << endl; }
};

class Scanner {
public:
    void turnOn() { cout << "[Сканер]: Включен" << endl; }
    void turnOff() { cout << "[Сканер]: Выключен" << endl; }
    void scan() { cout << "[Сканер]: Сканирует документ" << endl; }
};

class Projector {
public:
    void turnOn() { cout << "[Проектор]: Включен" << endl; }
    void turnOff() { cout << "[Проектор]: Выключен" << endl; }
    void showPresentation() { cout << "[Проектор]: Показывает презентацию" << endl; }
};

class Speakers {
public:
    void turnOn() { cout << "[Колонки]: Включены" << endl; }
    void turnOff() { cout << "[Колонки]: Выключены" << endl; }
    void playSound() { cout << "[Колонки]: Воспроизводят звук" << endl; }
};

class ICommand {
public:
    virtual ~ICommand() {}
    virtual void execute() = 0;
};

class PrinterCommand : public ICommand {
private:
    Printer* printer;
public:
    PrinterCommand(Printer* p) : printer(p) {}
    void execute() override {
        printer->turnOn();
        printer->print();
        printer->turnOff();
    }
};

class ScannerCommand : public ICommand {
private:
    Scanner* scanner;
public:
    ScannerCommand(Scanner* s) : scanner(s) {}
    void execute() override {
        scanner->turnOn();
        scanner->scan();
        scanner->turnOff();
    }
};

class ProjectorCommand : public ICommand {
private:
    Projector* projector;
public:
    ProjectorCommand(Projector* p) : projector(p) {}
    void execute() override {
        projector->turnOn();
        projector->showPresentation();
        projector->turnOff();
    }
};

class SpeakersCommand : public ICommand {
private:
    Speakers* speakers;
public:
    SpeakersCommand(Speakers* s) : speakers(s) {}
    void execute() override {
        speakers->turnOn();
        speakers->playSound();
        speakers->turnOff();
    }
};

class MacroCommand : public ICommand {
private:
    vector<ICommand*> commands;
public:
    void addCommand(ICommand* cmd) {
        commands.push_back(cmd);
    }
    void execute() override {
        for (size_t i = 0; i < commands.size(); ++i) {
            commands[i]->execute();
            cout << endl;
        }
    }
};

class Button {
private:
    ICommand* slot;
public:
    Button() : slot(NULL) {}
    void setCommand(ICommand* cmd) { slot = cmd; }
    void press() {
        if (slot != NULL) {
            slot->execute();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Printer printer;
    Scanner scanner;
    Projector projector;
    Speakers speakers;

    PrinterCommand print(&printer);
    ScannerCommand scan(&scanner);
    ProjectorCommand show(&projector);
    SpeakersCommand sound(&speakers);

    Button button;

    cout << "=== Одиночные команды ===" << endl;
    button.setCommand(&print);
    button.press();

    cout << endl;
    button.setCommand(&scan);
    button.press();

    cout << endl;
    button.setCommand(&show);
    button.press();

    cout << endl;
    button.setCommand(&sound);
    button.press();

    cout << "\n=== Макрокоманда \"Презентация\" ===" << endl;
    MacroCommand presentationMacro;
    presentationMacro.addCommand(&show);
    presentationMacro.addCommand(&sound);

    button.setCommand(&presentationMacro);
    button.press();

    return 0;
}