#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <locale>

using namespace std;

class Furniture {
protected:
    string material;
    string color;
    int width;
    int height;
    int price;

public:
    Furniture(string material, string color, int width, int height, int price)
        : material(material), color(color), width(width), height(height), price(price) {
    }

    virtual ~Furniture() = default;

    virtual unique_ptr<Furniture> clone() const = 0;

    virtual void info() const = 0;

    void setPrice(int newPrice) {
        price = newPrice;
    }

    void setColor(string newColor) {
        color = newColor;
    }
};

class Table : public Furniture {
public:
    Table(string material, string color, int width, int height, int price)
        : Furniture(material, color, width, height, price) {
    }

    unique_ptr<Furniture> clone() const override {
        return make_unique<Table>(*this);
    }

    void info() const override {
        cout << "Стол (Материал: " << material << ", цвет: " << color
            << ", размер: " << width << "x" << height
            << ", цена: " << price << " руб.)" << endl;
    }
};

class Chair : public Furniture {
public:
    Chair(string material, string color, int width, int height, int price)
        : Furniture(material, color, width, height, price) {
    }

    unique_ptr<Furniture> clone() const override {
        return make_unique<Chair>(*this);
    }

    void info() const override {
        cout << "Стул [Материал: " << material << ", цвет: " << color
            << ", размер: " << width << "x" << height
            << ", цена: " << price << " руб.]" << endl;
    }
};

class Sofa : public Furniture {
public:
    Sofa(string material, string color, int width, int height, int price)
        : Furniture(material, color, width, height, price) {
    }

    unique_ptr<Furniture> clone() const override {
        return make_unique<Sofa>(*this);
    }

    void info() const override {
        cout << "Диван [Материал: " << material << ", цвет: " << color
            << ", размер: " << width << "x" << height
            << ", цена: " << price << " руб.]" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    vector<unique_ptr<Furniture>> furniture;

    furniture.push_back(make_unique<Table>("Дуб", "Коричневый", 120, 70, 15000));
    furniture.push_back(make_unique<Chair>("Бук", "Белый", 40, 45, 5000));
    furniture.push_back(make_unique<Sofa>("Ткань", "Серый", 200, 80, 45000));

    const Furniture& prototype = *furniture[0];
    auto clone = prototype.clone();

    clone->setColor("Черный");
    clone->setPrice(12000);

    furniture.push_back(move(clone));

    cout << "Мебельный магазин" << endl;
    for (const auto& item : furniture) {
        item->info();
    }

    return 0;
}