#include <iostream>
#include <string>
#include <unordered_map>
#include <locale>

using namespace std;

class AppSettings {
private:
    static AppSettings* instance;

    unordered_map<string, string> settings;

    AppSettings() {
        settings["theme"] = "Светлая";
        settings["language"] = "Русский";
        settings["fontSize"] = "14";
        settings["autoSave"] = "true";
        settings["volume"] = "75";
        cout << "Загружены настройки по умолчанию." << endl;
    }

    ~AppSettings() {
        cout << "Настройки сохранены." << endl;
    }

public:
    AppSettings(const AppSettings&) = delete;
    AppSettings& operator=(const AppSettings&) = delete;

    static AppSettings* getInstance() {
        if (instance == nullptr) {
            instance = new AppSettings();
        }
        return instance;
    }

    static void destroyInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

    string get(const string& key) {
        if (settings.find(key) != settings.end()) {
            return settings[key];
        }
        return "Неизвестно";
    }

    void set(const string& key, const string& value) {
        settings[key] = value;
        cout << "[Настройки]: " << key << " = " << value << endl;
    }

    void showAll() {
        cout << "\nТекущие настройки" << endl;
        for (const auto& pair : settings) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }

    void resetToDefault() {
        settings.clear();
        settings["theme"] = "Светлая";
        settings["language"] = "Русский";
        settings["fontSize"] = "14";
        settings["autoSave"] = "true";
        settings["volume"] = "75";
        cout << "Настройки сброшены к значениям по умолчанию." << endl;
    }
};

AppSettings* AppSettings::instance = nullptr;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Приложение" << endl << endl;

    AppSettings* settings = AppSettings::getInstance();

    settings->showAll();

    cout << "\nИзменение настроек" << endl;
    settings->set("theme", "Тёмная");
    settings->set("fontSize", "16");
    settings->set("autoSave", "false");

    cout << "\nОтдельные настройки" << endl;
    cout << "Тема: " << settings->get("theme") << endl;
    cout << "Размер шрифта: " << settings->get("fontSize") << endl;
    cout << "Автосохранение: " << settings->get("autoSave") << endl;
    cout << "Громкость: " << settings->get("volume") << endl;

    cout << "\nВ меню" << endl;
    AppSettings* sameSettings = AppSettings::getInstance();
    cout << "Те же настройки? " << (settings == sameSettings ? "Да" : "Нет") << endl;
    cout << "Тема: " << sameSettings->get("theme") << endl;

    settings->showAll();

    cout << "\nСброс настроек" << endl;
    settings->resetToDefault();
    settings->showAll();

    AppSettings::destroyInstance();

    return 0;
}