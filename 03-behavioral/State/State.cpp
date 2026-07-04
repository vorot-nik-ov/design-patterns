#include <iostream>
#include <string>
#include <locale>

using namespace std;

class CoffeeMachine;

class IState {
public:
    virtual ~IState() {}
    virtual void insertCoin(CoffeeMachine* machine) = 0;
    virtual void selectDrink(CoffeeMachine* machine) = 0;
    virtual void dispense(CoffeeMachine* machine) = 0;
    virtual string getStateName() const = 0;
};

class IdleState : public IState {
public:
    void insertCoin(CoffeeMachine* machine) override;
    void selectDrink(CoffeeMachine* machine) override;
    void dispense(CoffeeMachine* machine) override;
    string getStateName() const override;
};

class SelectionState : public IState {
public:
    void insertCoin(CoffeeMachine* machine) override;
    void selectDrink(CoffeeMachine* machine) override;
    void dispense(CoffeeMachine* machine) override;
    string getStateName() const override;
};

class InsufficientFundsState : public IState {
public:
    void insertCoin(CoffeeMachine* machine) override;
    void selectDrink(CoffeeMachine* machine) override;
    void dispense(CoffeeMachine* machine) override;
    string getStateName() const override;
};

class PreparationState : public IState {
public:
    void insertCoin(CoffeeMachine* machine) override;
    void selectDrink(CoffeeMachine* machine) override;
    void dispense(CoffeeMachine* machine) override;
    string getStateName() const override;
};

class CoffeeMachine {
private:
    IState* state;
    int coins;
    string selectedDrink;

public:
    CoffeeMachine() : state(nullptr), coins(0), selectedDrink("") {
        state = new IdleState();
    }

    ~CoffeeMachine() {
        if (state != nullptr) {
            delete state;
            state = nullptr;
        }
    }

    void setState(IState* newState) {
        if (state != nullptr) {
            delete state;
        }
        state = newState;
    }

    void addCoin(int amount) {
        coins += amount;
        cout << "(Машина): Внесено " << amount << " руб. Всего: " << coins << " руб." << endl;
    }

    int getCoins() const {
        return coins;
    }

    void resetCoins() {
        coins = 0;
    }

    void setSelectedDrink(const string& drink) {
        selectedDrink = drink;
    }

    string getSelectedDrink() const {
        return selectedDrink;
    }

    void insertCoin() {
        state->insertCoin(this);
    }

    void selectDrink() {
        state->selectDrink(this);
    }

    void dispense() {
        state->dispense(this);
    }

    string getStateName() const {
        return state->getStateName();
    }
};


void IdleState::insertCoin(CoffeeMachine* machine) {
    cout << "(Ожидание): Монета принята." << endl;
    machine->addCoin(50);
    machine->setState(new SelectionState());
}

void IdleState::selectDrink(CoffeeMachine* machine) {
    cout << "(Ошибка): Сначала внесите монету!" << endl;
}

void IdleState::dispense(CoffeeMachine* machine) {
    cout << "(Ошибка): Сначала внесите монету и выберите напиток!" << endl;
}

string IdleState::getStateName() const {
    return "Ожидание монеты";
}

void SelectionState::insertCoin(CoffeeMachine* machine) {
    cout << "(Выбор): Монета принята." << endl;
    machine->addCoin(50);
}

void SelectionState::selectDrink(CoffeeMachine* machine) {
    cout << "(Выбор): Доступные напитки:" << endl;
    cout << "1. Эспрессо" << endl;
    cout << "2. Капучино" << endl;
    cout << "3. Латте" << endl;
    cout << "Выберите напиток (введите номер): ";

    int choice;
    cin >> choice;

    string drink;
    switch (choice) {
    case 1:
        drink = "Эспрессо";
        break;
    case 2:
        drink = "Капучино";
        break;
    case 3:
        drink = "Латте";
        break;
    default:
        cout << "(Ошибка): Неверный номер! Попробуйте снова." << endl;
        return;
    }

    machine->setSelectedDrink(drink);
    cout << "(Выбор): Выбран напиток '" << drink << "'." << endl;

    if (machine->getCoins() >= 100) {
        cout << "(Выбор): Достаточно средств. Начинаю приготовление." << endl;
        machine->setState(new PreparationState());
    }
    else {
        cout << "(Выбор): Недостаточно средств! Внесите ещё монет." << endl;
        cout << "Нужно: 100 руб. Внесено: " << machine->getCoins() << " руб." << endl;
        machine->setState(new InsufficientFundsState());
    }
}

void SelectionState::dispense(CoffeeMachine* machine) {
    cout << "(Ошибка): Сначала выберите напиток!" << endl;
}

string SelectionState::getStateName() const {
    return "Выбор напитка";
}

void InsufficientFundsState::insertCoin(CoffeeMachine* machine) {
    cout << "(Недостаточно средств): Монета принята." << endl;
    machine->addCoin(50);

    if (machine->getCoins() >= 100) {
        cout << "(Недостаточно средств): Теперь достаточно средств." << endl;
        machine->setState(new PreparationState());
    }
    else {
        cout << "(Недостаточно средств): Всё ещё недостаточно. Нужно 100 руб." << endl;
    }
}

void InsufficientFundsState::selectDrink(CoffeeMachine* machine) {
    cout << "(Ошибка): Дождитесь внесения полной суммы!" << endl;
}

void InsufficientFundsState::dispense(CoffeeMachine* machine) {
    cout << "(Ошибка): Недостаточно средств для приготовления!" << endl;
}

string InsufficientFundsState::getStateName() const {
    return "Недостаточно средств";
}

void PreparationState::insertCoin(CoffeeMachine* machine) {
    cout << "(Ошибка): Идёт приготовление. Подождите!" << endl;
}

void PreparationState::selectDrink(CoffeeMachine* machine) {
    cout << "(Ошибка): Идёт приготовление. Подождите!" << endl;
}

void PreparationState::dispense(CoffeeMachine* machine) {
    cout << "(Приготовление): Начинаю приготовление " << machine->getSelectedDrink() << "..." << endl;
    cout << "  - Нагрев воды..." << endl;
    cout << "  - Заваривание кофе..." << endl;
    cout << "  - Наливание в чашку..." << endl;
    cout << "(Приготовление): " << machine->getSelectedDrink() << " готов! Приятного аппетита!" << endl;

    machine->resetCoins();
    machine->setSelectedDrink("");
    machine->setState(new IdleState());
}

string PreparationState::getStateName() const {
    return "Приготовление";
}

int main() {
    setlocale(LC_ALL, "Russian");

    CoffeeMachine machine;

    cout << "Кофемашина" << endl;
    cout << "Цена напитка: 100 руб." << endl;
    cout << "Монета: 50 руб." << endl;

    cout << "Попытка выбрать напиток без монеты" << endl;
    machine.selectDrink();

    cout << "\nВнесение монеты" << endl;
    machine.insertCoin();

    cout << "\nВыбор напитка" << endl;
    machine.selectDrink();

    cout << "\nВнесение ещё одной монеты (если нужно)" << endl;
    machine.insertCoin();

    cout << "\nПолучение напитка" << endl;
    machine.dispense();

    cout << "\nСостояноие кофемашины" << endl;
    cout << "Текущее состояние: " << machine.getStateName() << endl;

    return 0;
}