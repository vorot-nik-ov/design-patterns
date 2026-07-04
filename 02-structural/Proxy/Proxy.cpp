#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <locale>

using namespace std;

class Cell {
private:
    string font;
    int size;
    string text;

public:
    Cell(const string& f, int s, const string& t)
        : font(f), size(s), text(t) {
    }

    void display(int row, int col) const {
        cout << "Ячейка (" << row << "," << col << ")"
            << " Текст: '" << text << "'"
            << " (Шрифт: " << font
            << ", Размер: " << size << ")"
            << endl;
    }
};

class CellFactory {
private:
    unordered_map<string, Cell*> pool;

    string createKey(const string& font, int size, const string& text) {
        return font + "_" + to_string(size) + "_" + text;
    }

public:
    ~CellFactory() {
        for (auto& pair : pool) {
            delete pair.second;
        }
        pool.clear();
    }

    Cell* getCell(const string& font, int size, const string& text) {
        string key = createKey(font, size, text);

        if (pool.find(key) != pool.end()) {
            return pool[key];
        }

        cout << ">>Создана новая ячейка для текста '" << text << "'" << endl;
        Cell* cell = new Cell(font, size, text);
        pool[key] = cell;
        return cell;
    }

    size_t getTotalObjectsCreated() const {
        return pool.size();
    }
};

class Table {
private:
    struct CellPosition {
        Cell* cell;
        int row;
        int col;
    };

    vector<CellPosition> cells;
    CellFactory factory;

public:
    void addCell(const string& font, int size, const string& text, int row, int col) {
        Cell* cell = factory.getCell(font, size, text);
        cells.push_back({ cell, row, col });
    }

    void render() {
        cout << "\nТаблица" << endl;
        for (const auto& cp : cells) {
            cp.cell->display(cp.row, cp.col);
        }
        cout << "Всего ячеек в таблице: " << cells.size() << endl;
        cout << "Всего объектов в памяти: " << factory.getTotalObjectsCreated() << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Table table;

    
    table.addCell("Times New Roman", 14, "Имя", 0, 0);
    table.addCell("Times New Roman", 14, "Возраст", 0, 1);
    table.addCell("Times New Roman", 14, "Город", 0, 2);

    
    table.addCell("Times New Roman", 12, "Иван", 1, 0);
    table.addCell("Times New Roman", 12, "25", 1, 1);
    table.addCell("Times New Roman", 12, "Саратов", 1, 2);

 
    table.addCell("Times New Roman", 12, "Елена", 2, 0);
    table.addCell("Times New Roman", 12, "30", 2, 1);
    table.addCell("Times New Roman", 12, "Маркс", 2, 2);

  
    table.addCell("Times New Roman", 12, "Петр", 3, 0);
    table.addCell("Times New Roman", 12, "22", 3, 1);
    table.addCell("Times New Roman", 12, "Вольск", 3, 2);

   
    table.addCell("Times New Roman", 14, "Итого: 3 человека", 4, 0);

    table.render();

    return 0;
}