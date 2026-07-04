# Builder (Строитель)
Строитель — это порождающий паттерн проектирования, который позволяет поэтапно создавать сложные объекты с помощью одного и того же процесса сборки.

## Проблема:
создание сложного объекта (например, автомобиля) требует инициализации множества полей, частей и подсистем. Создавать огромный конструктор с десятком параметров неудобно. Кроме того, иногда нужно создавать разные представления одного и того же объекта (например, саму машину и инструкцию к ней), используя один и тот же процесс сборки.

## Решение:
разделить алгоритм создания сложного объекта от его представления. Выделить класс Director, который будет задавать порядок шагов сборки, и абстрактный класс Builder, который определяет эти шаги. Конкретные строители (CarBuilder, ManualBuilder) реализуют шаги по-своему и возвращают разные конечные продукты.

## UML Схема класса
``` flowchart TD
subgraph top [ ]
direction LR
Builder["<b>Builder</b><hr>+ reset() void
+ setSeats() void
+ setEngine() void
+ setABS() void
+ setGPS() void
+ setWheels() void"]
Director["<b>Director</b><hr>+ makeSportCar()
+ makeLimusinCar()"]
end

subgraph middle [ ]
direction LR
CarBuilder["<b>CarBuilder</b><hr>- result : Car<br>+ reset() void<br>+ setSeats() void<br>+ getResult() Car"]
ManualBuilder["<b>ManualBuilder</b><hr>- result : Manual<br>+ reset() void<br>+ setSeats() void<br>+ getResult() Manual"]
end

subgraph bottom [ ]
direction LR
subgraph left_side [ ]
direction TB
Car["<b>Car</b><hr>+ seats : vector<br>+ wheels : vector<br>+ engine : Engine<br>+ ABSystem : ABS<br>+ GPSystem : GPS<br>+ speed : int"]
subgraph car_det [ ]
direction LR
Seat1["<b>Seat</b><hr>- comfortLevel"]
Engine1["<b>Engine</b><hr>- horsepower"]
Wheel1["<b>Wheel</b><hr>- gripQuality"]
ABS1["<b>ABS</b><hr>- enabled"]
GPS1["<b>GPS</b><hr>- enabled"]
end
Car --> Seat1 & Engine1 & Wheel1 & ABS1 & GPS1
end

subgraph right_side [ ]
direction TB
Manual["<b>Manual</b><hr>- seats : string<br>- enginePower : int<br>- wheels : vector<br>- hasABS : bool<br>+ hasGPS : bool"]
subgraph man_det [ ]
direction LR
Seat2["<b>Seat</b>"]
Engine2["<b>Engine</b>"]
Wheel2["<b>Wheel</b>"]
ABS2["<b>ABS</b>"]
GPS2["<b>GPS</b>"]
end
Manual --> Seat2 & Engine2 & Wheel2 & ABS2 & GPS2
end
end

Director --> Builder
CarBuilder ==>|реализует| Builder
ManualBuilder ==>|реализует| Builder
CarBuilder -.->|создает| Car
ManualBuilder -.->|создает| Manual

%% Скрытие рамок групп
style top fill:transparent,stroke:transparent
style middle fill:transparent,stroke:transparent
style bottom fill:transparent,stroke:transparent
style left_side fill:transparent,stroke:transparent
style right_side fill:transparent,stroke:transparent
style car_det fill:transparent,stroke:transparent
style man_det fill:transparent,stroke:transparent

%% Черный стиль без заливок и курсива
style Builder fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Director fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style CarBuilder fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style ManualBuilder fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Car fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Manual fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Seat1 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Engine1 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Wheel1 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style ABS1 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style GPS1 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Seat2 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Engine2 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style Wheel2 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style ABS2 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
style GPS2 fill:transparent,stroke:#000,color:#000,font-style:normal,font-weight:normal
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
