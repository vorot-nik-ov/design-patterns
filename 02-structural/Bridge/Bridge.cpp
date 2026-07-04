#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

class IEngine {
public:
    virtual ~IEngine() {}
    virtual void start() = 0;
    virtual void stop() = 0;
};

class ElectricEngine : public IEngine {
public:
    void start() override {
        cout << "Электрический двигатель запущен" << endl;
    }
    void stop() override {
        cout << "Электрический двигатель остановлен" << endl;
    }
};

class GasolineEngine : public IEngine {
public:
    void start() override {
        cout << "Бензиновый двигатель запущен" << endl;
    }
    void stop() override {
        cout << "Бензиновый двигатель остановлен" << endl;
    }
};

class GasEngine : public IEngine {
public:
    void start() override {
        cout << "Газовый двигатель запущен" << endl;
    }
    void stop() override {
        cout << "Газовый двигатель остановлен" << endl;
    }
};

class Vehicle {
protected:
    IEngine* engine;
public:
    Vehicle(IEngine* e) : engine(e) {}
    virtual ~Vehicle() {}
    virtual void drive() = 0;
};

class Car : public Vehicle {
public:
    Car(IEngine* e) : Vehicle(e) {}
    void drive() override {
        engine->start();
        cout << "Автомобиль едет" << endl;
        engine->stop();
        cout << "Автомобиль останавливается" << endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(IEngine* e) : Vehicle(e) {}
    void drive() override {
        engine->start();
        cout << "Мотоцикл едет" << endl;
        engine->stop();
        cout << "Мотоцикл останавливается" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ElectricEngine electric;
    GasolineEngine gasoline;
    GasEngine gas;

    Car car1(&electric);
    Car car2(&gasoline);
    Car car3(&gas);
    Motorcycle bike1(&electric);
    Motorcycle bike2(&gasoline);
    Motorcycle bike3(&gas);

    vector<Vehicle*> vehicles = { &car1, &car2, &car3, &bike1, &bike2, &bike3 };

    for (Vehicle* v : vehicles) {
        v->drive();
        cout << endl;
    }

    return 0;
}