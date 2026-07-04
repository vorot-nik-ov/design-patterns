#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

class IPaymentStrategy {
public:
    virtual ~IPaymentStrategy() {}
    virtual void pay(double amount) = 0;
    virtual string getMethodName() = 0;
};

class CardPayment : public IPaymentStrategy {
private:
    string cardNumber;
public:
    CardPayment(const string& card) : cardNumber(card) {}

    void pay(double amount) override {
        cout << "Оплата картой " << cardNumber << " на сумму " << amount << " руб." << endl;
        cout << "Списание средств... Успешно!" << endl;
    }

    string getMethodName() override {
        return "Банковская карта";
    }
};

class CashPayment : public IPaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Оплата наличными на сумму " << amount << " руб." << endl;
        cout << "Внесение средств... Успешно!" << endl;
    }

    string getMethodName() override {
        return "Наличные";
    }
};

class CryptoPayment : public IPaymentStrategy {
private:
    string wallet;
public:
    CryptoPayment(const string& w) : wallet(w) {}

    void pay(double amount) override {
        cout << "Оплата криптовалютой (кошелек: " << wallet << ") на сумму " << amount << " руб." << endl;
        cout << "Транзакция в блокчейне... Успешно!" << endl;
    }

    string getMethodName() override {
        return "Криптовалюта";
    }
};

class SberPayPayment : public IPaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Оплата через Sber Pay на сумму " << amount << " руб." << endl;
        cout << "Подтверждение Face ID... Успешно!" << endl;
    }

    string getMethodName() override {
        return "Sber Pay";
    }
};

class PaymentProcessor {
private:
    IPaymentStrategy* strategy;
    string customerName;
public:
    PaymentProcessor(const string& name) : customerName(name), strategy(NULL) {}

    ~PaymentProcessor() {
        if (strategy != NULL) {
            delete strategy;
        }
    }

    void setStrategy(IPaymentStrategy* newStrategy) {
        if (strategy != NULL) {
            delete strategy;
        }
        strategy = newStrategy;
    }

    void processPayment(double amount) {
        if (strategy == NULL) {
            cout << "Ошибка: Способ оплаты не выбран!" << endl;
            return;
        }

        cout << "\nПлатеж" << endl;
        cout << "Клиент: " << customerName << endl;
        cout << "Способ: " << strategy->getMethodName() << endl;
        strategy->pay(amount);
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    PaymentProcessor processor("Олег Сикорский");

    processor.setStrategy(new CardPayment("**** **** **** ****"));
    processor.processPayment(1799.99);

    processor.setStrategy(new CashPayment());
    processor.processPayment(450.00);

    processor.setStrategy(new CryptoPayment("0x7a2b1c4d5e9f"));
    processor.processPayment(1000.00);

    processor.setStrategy(new SberPayPayment());
    processor.processPayment(2500.00);

    return 0;
}