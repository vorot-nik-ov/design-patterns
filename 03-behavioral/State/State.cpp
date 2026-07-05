#include <iostream>
#include <memory>
#include <string>

using namespace std;

class CoffeeMachine;

class State
{
public:
    virtual ~State() = default;
    virtual void InsertCoin() = 0;
    virtual void SelectDrink() = 0;
    virtual void Dispense() = 0;
};

class NoCoinState : public State
{
private:
    CoffeeMachine* machine;
public:
    NoCoinState(CoffeeMachine* _machine) : machine(_machine) {}

    void InsertCoin() override;
    void SelectDrink() override;
    void Dispense() override;
};

class HasCoinState : public State
{
private:
    CoffeeMachine* machine;
public:
    HasCoinState(CoffeeMachine* _machine) : machine(_machine) {}

    void InsertCoin() override;
    void SelectDrink() override;
    void Dispense() override;
};

class DispensingState : public State
{
private:
    CoffeeMachine* machine;
public:
    DispensingState(CoffeeMachine* _machine) : machine(_machine) {}

    void InsertCoin() override;
    void SelectDrink() override;
    void Dispense() override;
};

class CoffeeMachine
{
private:
    shared_ptr<State> noCoinState;
    shared_ptr<State> hasCoinState;
    shared_ptr<State> dispensingState;
    shared_ptr<State> currentState;

    int drinkCount;
    string selectedDrink;

public:
    CoffeeMachine(int initialDrink = 5) : drinkCount(initialDrink)
    {
        noCoinState = make_shared<NoCoinState>(this);
        hasCoinState = make_shared<HasCoinState>(this);
        dispensingState = make_shared<DispensingState>(this);
        currentState = noCoinState;
    }

    void SetState(shared_ptr<State> state)
    {
        currentState = state;
    }

    void InsertCoin()
    {
        currentState->InsertCoin();
    }

    void SelectDrink()
    {
        currentState->SelectDrink();
    }

    void Dispense()
    {
        currentState->Dispense();
    }
    void Refill(int amount)
    {
        drinkCount += amount;
        cout << "Кофемашина щаправлена. Текущее количество напитков: " << drinkCount << endl;
    }

    shared_ptr<State> GetNoCoinState() { return noCoinState; }
    shared_ptr<State> GetHasCoinState() { return hasCoinState; }
    shared_ptr<State> GetDispensingState() { return dispensingState; }

    int GetDrinkCount() { return drinkCount; }
    void SetDrinkCount(int count) { drinkCount = count; }

    void SetSelectedDrink(string drink) { selectedDrink = drink; }
    string GetSelectedDrink() { return selectedDrink; }
};

void NoCoinState::InsertCoin()
{
    cout << "Монета принята. Выберите напиток.\n";
    machine->SetState(machine->GetHasCoinState());
}

void NoCoinState::SelectDrink()
{
    cout << "Сначала бросьте монету\n";
}

void NoCoinState::Dispense()
{
    cout << "Нечего выдавать. Добавьте монету и выберите напиток\n";
}

void HasCoinState::InsertCoin()
{
    cout << "Монета уже вставлена.\n";
}

void HasCoinState::SelectDrink()
{
    int choice;
    cout << "Выберите напиток:\n1 - Эспрессо\n2 - Капучино\n3 - Латте\n";
    cin >> choice;

    switch (choice)
    {
    case 1: machine->SetSelectedDrink("Эспрессо"); break;
    case 2: machine->SetSelectedDrink("Капучино"); break;
    case 3: machine->SetSelectedDrink("Латте"); break;
    default:
        cout << "Неверный выбор\n";
        return;
    }

    cout << "Вы выбрали: " << machine->GetSelectedDrink() << endl;
    machine->SetState(machine->GetDispensingState());
}

void HasCoinState::Dispense()
{
    cout << "Сначала выберите напиток.\n";
}

void DispensingState::InsertCoin()
{
    cout << "Подождите, идет приготовление напитка.\n";
}

void DispensingState::SelectDrink()
{
    cout << "Напиток уже готовится.\n";
}

void DispensingState::Dispense()
{
    if (machine->GetDrinkCount() > 0)
    {
        cout << "Готовим " << machine->GetSelectedDrink() << "...\n";
        machine->SetDrinkCount(machine->GetDrinkCount() - 1);
        cout << "Ваш " << machine->GetSelectedDrink() << " готов!\n";
    }
    else
    {
        cout << "Напитки закончились\n";
    }
    machine->SetState(machine->GetNoCoinState());
}

int main()
{
    setlocale(LC_ALL, "Rus");

    CoffeeMachine machine(3);

    while (true)
    {
        cout << "\n1 - Вставить монету\n2 - Выбрать напиток\n3 - Получить напиток\n4 - Заправить кофемашину\n0 - Выход\n";
        int cmd;
        cin >> cmd;

        switch (cmd)
        {
        case 1: machine.InsertCoin(); break;
        case 2: machine.SelectDrink(); break;
        case 3: machine.Dispense(); break;
        case 4: int amount;
            cout << "Введите количество добавляемых напитков: ";
            cin >> amount;
            machine.Refill(amount); break;
        case 0: (cmd == 0); break;
        default: cout << "Ошибка ввода\n";
        }
    }

    return 0;
}