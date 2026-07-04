#include <iostream>
#include <string>
#include <locale>

using namespace std;

class IBuckwheat {
public:
    virtual ~IBuckwheat() {}
    virtual string getDescription() const = 0;
    virtual double getPrice() const = 0;
};

class Buckwheat : public IBuckwheat {
public:
    string getDescription() const override {
        return "Гречневая каша";
    }

    double getPrice() const override {
        return 80.0;  // базовая цена
    }
};

class SauceDecorator : public IBuckwheat {
protected:
    IBuckwheat* buckwheat;
public:
    SauceDecorator(IBuckwheat* b) : buckwheat(b) {}

    virtual ~SauceDecorator() {
        delete buckwheat;
    }
};

class CheeseSauce : public SauceDecorator {
public:
    CheeseSauce(IBuckwheat* b) : SauceDecorator(b) {}

    string getDescription() const override {
        return buckwheat->getDescription() + " + Сырный соус";
    }

    double getPrice() const override {
        return buckwheat->getPrice() + 30.0;
    }
};

class MushroomSauce : public SauceDecorator {
public:
    MushroomSauce(IBuckwheat* b) : SauceDecorator(b) {}

    string getDescription() const override {
        return buckwheat->getDescription() + " + Грибной соус";
    }

    double getPrice() const override {
        return buckwheat->getPrice() + 40.0;
    }
};

class TomatoSauce : public SauceDecorator {
public:
    TomatoSauce(IBuckwheat* b) : SauceDecorator(b) {}

    string getDescription() const override {
        return buckwheat->getDescription() + " + Кетчуп";
    }

    double getPrice() const override {
        return buckwheat->getPrice() + 25.0;
    }
};

class GarlicSauce : public SauceDecorator {
public:
    GarlicSauce(IBuckwheat* b) : SauceDecorator(b) {}

    string getDescription() const override {
        return buckwheat->getDescription() + " + Чесночный соус";
    }

    double getPrice() const override {
        return buckwheat->getPrice() + 20.0;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Меню" << endl;
    cout << "Базовая каша: 80 руб." << endl;
    cout << "Сырный соус: +30 руб." << endl;
    cout << "Грибной соус: +40 руб." << endl;
    cout << "Томатный соус: +25 руб." << endl;
    cout << "Чесночный соус: +20 руб." << endl;
   
   
    IBuckwheat* order1 = new Buckwheat();
    cout << "Заказ 1: " << order1->getDescription() << " = " << order1->getPrice() << " руб." << endl;

    IBuckwheat* order2 = new CheeseSauce(new Buckwheat());
    cout << "Заказ 2: " << order2->getDescription() << " = " << order2->getPrice() << " руб." << endl;

    IBuckwheat* order3 = new MushroomSauce(new Buckwheat());
    cout << "Заказ 3: " << order3->getDescription() << " = " << order3->getPrice() << " руб." << endl;

    IBuckwheat* order4 = new CheeseSauce(new MushroomSauce(new Buckwheat()));
    cout << "Заказ 4: " << order4->getDescription() << " = " << order4->getPrice() << " руб." << endl;

    IBuckwheat* order5 = new GarlicSauce(new TomatoSauce(new CheeseSauce(new Buckwheat())));
    cout << "Заказ 5: " << order5->getDescription() << " = " << order5->getPrice() << " руб." << endl;

    delete order1;
    delete order2;
    delete order3;
    delete order4;
    delete order5;

    return 0;
}