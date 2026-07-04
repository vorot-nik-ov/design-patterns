# Builder (Строитель)
Строитель — это порождающий паттерн проектирования, который позволяет поэтапно создавать сложные объекты с помощью одного и того же процесса сборки.

## Проблема:
создание сложного объекта (например, автомобиля) требует инициализации множества полей, частей и подсистем. Создавать огромный конструктор с десятком параметров неудобно. Кроме того, иногда нужно создавать разные представления одного и того же объекта (например, саму машину и инструкцию к ней), используя один и тот же процесс сборки.

## Решение:
разделить алгоритм создания сложного объекта от его представления. Выделить класс Director, который будет задавать порядок шагов сборки, и абстрактный класс Builder, который определяет эти шаги. Конкретные строители (CarBuilder, ManualBuilder) реализуют шаги по-своему и возвращают разные конечные продукты.

## UML Схема класса
``` mermaid
classDiagram
class Director {
+makeSportCar
+makeLimusinCar
}
class Builder {
<<interface>>
+reset() virtual void
+setSeats(quantity) virtual void
+setEngine(horsepower) virtual void
+setABS() virtual void
+setGPS() virtual void
+setWheels(quantity) virtual void
}
class CarBuilder {
-result : Car
+reset() void
+setSeats(quantity) void
+setEngine(horsepower) void
+setABS() void
+setGPS() void
+setWheels(quantity) void
+getResult() Car
}
class ManualBuilder {
-result : Manual
+reset() void
+setSeats(quantity) void
+setEngine(horsepower) void
+setABS() void
+setGPS() void
+setWheels(quantity) void
+getResult() Manual
}
class Car {
+seats : vector
+wheels : vector
+engine : Engine
+ABSystem : ABS
+GPSystem : GPS
+speed : int
+setSpeed() void
+Drive() void
+getInfo() void
}
class Manual {
-seats : string
-enginePower : int
-wheels : vector
-hasABS : bool
+hasGPS : bool
+setSeats(seat) void
+setEngine(power) void
+setWheels(wheel) void
+setABS() void
+setGPS() void
+ReadInstruction() string
}
class Seat {
-comfortLevel : string
+Seat(comfortLevel)
+getComfort() string
}
class Engine {
-horsepower : int
+Engine(horsepower)
+getHorsePower() int
}
class Wheel {
-gripQuality : string
+Wheel(gripQuality)
+getGrip() string
}
class ABS {
-enabled : bool
+ABS(enabled)
+enable() void
+getStatus() string
}
class GPS {
-enabled : bool
+GPS(enabled)
+enable() void
+getStatus() string
}

Director --> Builder : использует
CarBuilder --|> Builder : реализует
ManualBuilder --|> Builder : реализует
CarBuilder ..> Car : создает
ManualBuilder ..> Manual : создает

Car *-- Seat
Car *-- Engine
Car *-- ABS
Car *-- GPS
Car *-- Wheel

Manual *-- Seat
Manual *-- Engine
Manual *-- ABS
Manual *-- GPS
Manual *-- Wheel

style Director fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Builder fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style CarBuilder fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style ManualBuilder fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Car fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Manual fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Seat fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Engine fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Wheel fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style ABS fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style GPS fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
```

## Особенности реализации на C++
### Абстрактный класс:
используется класс Builder с чисто виртуальными методами (= 0), что заставляет наследников реализовать все шаги сборки.
### Разные продукты:
возвращаемые типы методов getResult() в наследниках разные (Car и Manual), что допустимо в C++, так как они не являются переопределениями виртуальных функций базового класса (базовый класс не знает о конечном продукте).
### Агрегация деталей:
конечный продукт (Car) содержит в себе другие объекты (Engine, ABS, GPS), что демонстрирует работу с составными частями сложного объекта.
## Плюсы
Позволяет шаг за шагом создавать сложные объекты.
Изолирует код сборки от бизнес-логики конечного продукта.
Дает возможность использовать один и тот же код сборки для создания разных представлений.
Реализует принцип открытости/закрытости (легко добавить нового строителя без изменения директора).
## Минусы
Усложняет код программы за счет добавления новых классов.
Клиент привязан к конкретным классам строителей (в данном примере в main жестко задано создание CarBuilder и ManualBuilder).
## Пример реализации
Весь код, включая абстрактный строителя, конкретных строителей, директора и пример использования, находится в одном файле:

Builder.cpp
