# MMORPG

[![Version](https://img.shields.io/badge/version-4.0.0-green.svg)](https://github.com/aqcbb/mmorpg/releases)
[![C++](https://img.shields.io/badge/C%2B%2B-14-blue.svg)]()

Лабораторная работа по ООП

**Язык:** C++14. **Сборка:** Visual Studio 2022

## Архитектура и UML

Система построена на ключевых паттернах проектирования:
1. **Фасад (Facade)** — `GameFacade` предоставляет единый интерфейс для пользователя.
2. **Посредник (Mediator)** — `GameMediator` координирует взаимодействие между `Base`, `UnitManager`, `BuildingManager` и `CombatSystem`.
3. **Команда (Command)** — Действия пользователя оформлены как классы (например, `CreateUnitCommand`, `MoveUnitCommand`).
4. **Цепочка обязанностей (Chain of Responsibility)** — Обработка текстового ввода идет по цепочке хендлеров (`CreateHandler` -> `MoveHandler` -> ... -> `StatsHandler`).
5. **Адаптер (Adapter)** — `ILogFormatter` и его реализации (`TextFormatter`, `JsonFormatter`, `CsvFormatter`) преобразуют события в нужный формат.
6. **Прокси (Proxy)** — `LoggingProxy` управляет текущим логгером и форматом, позволяя менять их на лету.
7. **RAII** — `FileLogger` открывает файл в конструкторе и закрывает в деструкторе.

```mermaid
classDiagram
    class GameFacade {
        -GameMediator mediator_
        -LoggingProxy logger_
        -Handler handlerChain_
        +processInput(string)
        +executeCommand(Command)
    }
    class GameMediator {
        -Base base_
        -UnitManager unitManager_
        -BuildingManager buildingManager_
        -CombatSystem combatSystem_
    }
    class LoggingProxy {
        -currentLogger_
        -formatter_
        +log(LogEvent)
        +setLogger(ILogger)
        +setFormatter(ILogFormatter)
    }
    class ILogger {
        <<interface>>
        +log(LogEvent)
    }
    class ILogFormatter {
        <<interface>>
        +format(LogEvent)
    }
    
    GameFacade --> GameMediator
    GameFacade --> LoggingProxy
    GameFacade --> Handler
    LoggingProxy --> ILogger
    LoggingProxy --> ILogFormatter
    Handler --> Command
    Command --> GameMediator
```

## Предметная область

* **Base** — управляет юнитами, ресурсами и зданиями. Реализует `IObserver`.
* **Unit** — базовый класс юнитов (`Infantry`, `Scout`, `Tank`, `Worker`, `Medic`, `Archer`, `Mage`).
* **Building** — базовый класс зданий (`Barracks`, `PowerPlant`, `Laboratory`, `Warehouse`, `Hospital`).
* **Terrain** — ландшафт (`Plains`, `Forest`, `Swamp`, `Mountains`), влияющий на проходимость.
* **NeutralObject** — нейтральные объекты (`TreasureChest`, `Trap`, `Altar`, `EnergySource`).
* **UnitManager** — хранит всех юнитов, умеет перемещать и удалять.
* **BuildingManager** — управляет постройкой зданий и производством.
* **CombatSystem** — рассчитывает урон с учетом атаки и брони.

## Команды

* `create unit <type> at <x>,<y>` — создание юнита.
* `move unit <id> to <x>,<y>` — перемещение.
* `attack unit <id> target <id>` — атака.
* `collect unit <id> at <x>,<y>` — сбор ресурсов.
* `build <type> at <x>,<y>` — постройка здания.
* `produce <type> in <buildingId>` — производство юнита в здании.
* `spawn_object <type> at <x>,<y>` — создание нейтрального объекта.
* `stats` — статистика.
* `set_logger <console|file|null>` — смена логгера.
* `set_format <text|json|csv>` — смена формата.
* `map` — отрисовка карты.
* `exit` — выход.

## Демонстрационные сценарии (Логирование)

1. **Логирование в консоль (Text):**
![Сценарий 1](https://www.upload.ee/image/19987802/scenario1.gif)
2. **Логирование в файл (JSON):**
![Сценарий 2](https://www.upload.ee/image/19987818/scenario2.gif)
3. **Отключение логирования (Null):**
![Сценарий 3](https://www.upload.ee/image/19987821/scenario3.gif)
4. **Смена формата (CSV):**
![Сценарий 4](https://www.upload.ee/image/19987823/scenario4.gif)