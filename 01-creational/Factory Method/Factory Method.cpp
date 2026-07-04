#include <iostream>
#include <string>
#include <memory>
#include <locale>

using namespace std;

class IFaculty {
public:
    virtual ~IFaculty() = default;
    virtual void showInfo() = 0;
};

class PhysicsFaculty : public IFaculty {
public:
    void showInfo() override {
        cout << "‘изический факультет (300 студентов)" << endl;
    }
};

class EconomicsFaculty : public IFaculty {
public:
    void showInfo() override {
        cout << "Ёкономический факультет (400 студентов)" << endl;
    }
};

class EngineeringFaculty : public IFaculty {
public:
    void showInfo() override {
        cout << "»нженерный факультет (450 студентов)" << endl;
    }
};

class GeologicFaculty : public IFaculty {
public:
    void showInfo() override {
        cout << "√еологический факультет (250 студентов)" << endl;
    }
};

class LawFaculty : public IFaculty {
public:
    void showInfo() override {
        cout << "ёридический факультет (100 студентов)" << endl;
    }
};

class FacultyFactory {
public:
    enum class Type { Physics, Economics, Engineering, Geo,Law };

    static unique_ptr<IFaculty> create(Type type) {
        switch (type) {
        case Type::Physics:     return make_unique<PhysicsFaculty>();
        case Type::Economics:   return make_unique<EconomicsFaculty>();
        case Type::Engineering: return make_unique<EngineeringFaculty>();
        case Type::Geo: return make_unique<GeologicFaculty>();
        case Type::Law:         return make_unique<LawFaculty>();
        default:                return nullptr;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    auto faculty1 = FacultyFactory::create(FacultyFactory::Type::Physics);
    auto faculty2 = FacultyFactory::create(FacultyFactory::Type::Economics);
    auto faculty3 = FacultyFactory::create(FacultyFactory::Type::Law);
    auto faculty4 = FacultyFactory::create(FacultyFactory::Type::Engineering);

    if (faculty1) faculty1->showInfo();
    if (faculty2) faculty2->showInfo();
    if (faculty3) faculty3->showInfo();
    if (faculty4) faculty4->showInfo();

    return 0;
}