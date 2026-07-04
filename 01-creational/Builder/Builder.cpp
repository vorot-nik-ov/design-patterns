#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Seat {
private:
    string comfortLevel;
public:
    Seat(string comfortLevel = "Стандарт") {
        this->comfortLevel = comfortLevel;
    }

    string getComfort() const {
        return comfortLevel;
    }
};

class Wheel {
private:
    string gripQuality;
public:
    Wheel(string gripQuality = "Голая резина") {
        this->gripQuality = gripQuality;
    }

    string getGrip() const {
        return gripQuality;
    }
};

class Engine {
private:
    int horsepower;
public:
    Engine(int horsepower = 0) {
        this->horsepower = horsepower;
    }

    int getHorsePower() const {
        return horsepower;
    }
};

class ABS {
private:
    bool enabled;
public:
    ABS(bool enabled = false) {
        this->enabled = enabled;
    }

    void enable() {
        enabled = true;
    }

    string getStatus() const {
        return enabled ? "Включена" : "Отсутствует";
    }
};

class GPS {
private:
    bool enabled;
public:
    GPS(bool enabled = false) {
        this->enabled = enabled;
    }

    void enable() {
        enabled = true;
    }

    string getStatus() const {
        return enabled ? "Включен" : "Отсутствует";
    }
};

class Car {
public:
    vector<Seat> seats;
    ABS ABSystem;
    GPS GPSystem;
    Engine engine;
    vector<Wheel> wheels;
    int speed = 0;

    void Drive() {
        if (speed < 100) {
            speed += 10;
        }
    }

    void setSpeed(int spd) {
        speed = spd;
    }

    void getInfo() {
        cout << "Информация об автомобиле" << endl;

        if (!seats.empty())
            cout << "Тип сидений: " << seats[0].getComfort() << endl;

        cout << "Мощность двигателя: " << engine.getHorsePower() << " л.с." << endl;

        if (!wheels.empty())
            cout << "Тип колес: " << wheels[0].getGrip() << endl;

        cout << "ABS: " << ABSystem.getStatus() << endl;
        cout << "GPS: " << GPSystem.getStatus() << endl;

        cout << "Скорость: " << speed << " км/ч" << endl;
    }
};

class Manual {
private:
    string seats;
    int enginePower;
    string wheels;
    bool hasABS = false;
    bool hasGPS = false;

public:
    void setSeats(string seat) { seats = seat; }
    void setEngine(int power) { enginePower = power; }
    void setWheels(string wheel) { wheels = wheel; }
    void setABS() { hasABS = true; }
    void setGPS() { hasGPS = true; }

    void ReadInstruction() {
        cout << "Инструкция к автомобилю:\n";
        cout << "   Сиденья: " << seats << ".\nЕсли вы заметили пятно, постарайтесь удалить его как можно быстрее.\n";
        cout << "Для этого используйте специальные средства, предназначенные для чистки автомобильных тканей или кожи.\n";
        cout << "Всегда заранее проверяйте средство на небольшом участке, чтобы убедиться, что оно не повредит материал.\n";
        cout << "   Двигатель: " << enginePower << " л.с.\n";
        cout << "Регулярное обслуживание двигателя, включая замену масла и проверку состояния свечей зажигания, помогает поддерживать оптимальную производительность.\n";
        cout << "   Колёса: " << wheels << endl;
        cout << "Перед нанесением любых защитных средств поверхность шины необходимо очистить от любых загрязнений.\n";
        cout << "Для этого можно использовать любой щелочной очиститель и щетку.\n";
        cout << "Процесс очистки нужно повторять до тех пор, пока пена образуемая очистителем не перестанет окрашиваться. После очистки обильно сполоснуть водой и просушить.\n";
        cout << "   ABS: " << (hasABS ? "Есть" : "Нет") << endl;
        cout << "   GPS: " << (hasGPS ? "Есть" : "Нет") << endl;
    }
};

class Builder {
public:
    virtual void reset() = 0;
    virtual void setSeats(string comfortLevel) = 0;
    virtual void setEngine(Engine engine) = 0;
    virtual void setABS() = 0;
    virtual void setGPS() = 0;
    virtual void setWheels(string gripQuality) = 0;
};

class CarBuilder : public Builder {
private:
    Car result;

public:
    void reset() override {
        result = Car();
    }

    void setSeats(string comfortLevel) override {
        result.seats.clear();
        result.seats.push_back(Seat(comfortLevel));
    }

    void setEngine(Engine engine) override {
        result.engine = engine;
    }

    void setABS() override {
        result.ABSystem.enable();
    }

    void setGPS() override {
        result.GPSystem.enable();
    }

    void setWheels(string gripQuality) override {
        result.wheels.clear();
        result.wheels.push_back(Wheel(gripQuality));
    }

    Car getResult() {
        return result;
    }
};

class ManualBuilder : public Builder {
private:
    Manual result;

public:
    void reset() override {
        result = Manual();
    }

    void setSeats(string comfortLevel) override {
        result.setSeats(comfortLevel);
    }

    void setEngine(Engine engine) override {
        result.setEngine(engine.getHorsePower());
    }

    void setABS() override {
        result.setABS();
    }

    void setGPS() override {
        result.setGPS();
    }

    void setWheels(string gripQuality) override {
        result.setWheels(gripQuality);
    }

    Manual getResult() {
        return result;
    }
};

class Director {
public:
    void makeSportCar(Builder& builder) {
        builder.reset();
        builder.setSeats("Спортивные");
        builder.setEngine(Engine(200));
        builder.setABS();
        builder.setWheels("Гоночные");
    }

    void makeLimusin(Builder& builder) {
        builder.reset();
        builder.setSeats("Люкс");
        builder.setEngine(Engine(170));
        builder.setGPS();
        builder.setABS();
        builder.setWheels("Комфортные");
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Director director;
    CarBuilder carBuilder;
    ManualBuilder manualBuilder;

    int choiceCar;

    cout << "Выбор типа машины" << endl;
    cout << "1 - Спорткар" << endl;
    cout << "2 - Лимузин" << endl;
    cout << "Ваш выбор: ";
    cin >> choiceCar;

    Car car;
    Manual manual;

    switch (choiceCar) {
    case 1:
        director.makeSportCar(carBuilder);
        director.makeSportCar(manualBuilder);
        cout << "Спорткар готов!" << endl;
        break;

    case 2:
        director.makeLimusin(carBuilder);
        director.makeLimusin(manualBuilder);
        cout << "Лимузин готов!" << endl;
        break;

    default:
        cout << "Неверный выбор!" << endl;
        return 0;
    }

    car = carBuilder.getResult();
    manual = manualBuilder.getResult();

    int speed;
    cout << "Введите скорость: ";
    cin >> speed;

    car.setSpeed(speed);

    cout << "\n--- Данные машины ---\n";
    car.getInfo();

    cout << "\n--- Инструкция ---\n";
    manual.ReadInstruction();

    return 0;
}