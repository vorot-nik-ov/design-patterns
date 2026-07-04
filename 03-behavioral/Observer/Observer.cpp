#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(const string& weather, double temperature) = 0;
    virtual string getName() const = 0;
};

class ISubject {
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};

class WeatherStation : public ISubject {
private:
    vector<IObserver*> observers;
    string weather;
    double temperature;
    double humidity;

public:
    WeatherStation() : temperature(0), humidity(0) {}

    void attach(IObserver* observer) override {
        observers.push_back(observer);
        cout << "(Станция): Наблюдатель '" << observer->getName()
            << "' добавлен." << endl;
    }

    void detach(IObserver* observer) override {
        for (size_t i = 0; i < observers.size(); i++) {
            if (observers[i] == observer) {
                observers.erase(observers.begin() + i);
                cout << "(Станция): Наблюдатель '" << observer->getName()
                    << "' удален." << endl;
                return;
            }
        }
    }

    void notify() override {
        cout << "\n(Станция): Оповещение всех наблюдателей..." << endl;
        for (size_t i = 0; i < observers.size(); i++) {
            observers[i]->update(weather, temperature);
        }
    }

    void setWeather(const string& newWeather, double newTemp) {
        weather = newWeather;
        temperature = newTemp;
        cout << "\n(Станция): Обновление данных о погоде..." << endl;
        cout << "  Погода: " << weather << ", Температура: " << temperature << "°C" << endl;
        notify();
    }
};

class PhoneDisplay : public IObserver {
private:
    string name;
public:
    PhoneDisplay(const string& n) : name(n) {}

    void update(const string& weather, double temperature) override {
        cout << "  (Телефон " << name << "): Получено обновление!" << endl;
        cout << "    Погода: " << weather << endl;
        cout << "    Температура: " << temperature << "°C" << endl;
    }

    string getName() const override {
        return name;
    }
};

class CentralPCDisplay : public IObserver {
private:
    string name;
public:
   CentralPCDisplay(const string& n) : name(n) {}

    void update(const string& weather, double temperature) override {
        cout << "  (Монитор " << name << "): Получено обновление!" << endl;
        if (temperature > 25) {
            cout << "    ВНИМАНИЕ: Высокая температура! (" << temperature << "°C)" << endl;
        }
        else {
            cout << "    Погода: " << weather << endl;
            cout << "    Температура: " << temperature << "°C" << endl;
        }
    }

    string getName() const override {
        return name;
    }
};

class SMSNotification : public IObserver {
private:
    string name;
public:
    SMSNotification(const string& n) : name(n) {}

    void update(const string& weather, double temperature) override {
        cout << "  (SMS): Отправлено сообщение на номер " << name << endl;
        cout << "    Сообщение: Погода " << weather << ", " << temperature << "°C" << endl;
    }

    string getName() const override {
        return name;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    WeatherStation station;

    PhoneDisplay phone1("Виктор");
    PhoneDisplay phone2("Илья");
    CentralPCDisplay monitor("Центральный компьютер");
    SMSNotification sms("+7-***-***-**-**");

    cout << "Подписка на уведомления" << endl;
    station.attach(&phone1);
    station.attach(&phone2);
    station.attach(&monitor);
    station.attach(&sms);

    cout << "\nИзменение погоды" << endl;
    station.setWeather("Солнечно", 28.5);

    cout << "\nИзменение погоды" << endl;
    station.setWeather("Дождливо", 15.0);

    cout << "\nУдаление наблюдателя" << endl;
    station.detach(&phone2);

    cout << "\nИзменение погоды" << endl;
    station.setWeather("Облачно", 20.0);

    return 0;
}