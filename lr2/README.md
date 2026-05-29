Лабораторная работа 2 — моделирование фрагмента предметной области в SNePS

Предметная область
- Библиотека.
- Понятия: `Person`, `Reader`, `AdultReader`, `ChildReader`, `Librarian`, `Book`.
- Связи: `borrows` и `recommends`.
- Иерархия: `AdultReader` ISA `Reader`, `ChildReader` ISA `Reader`, `Reader` ISA `Person`, `Librarian` ISA `Person`, `Book` ISA `Item`.

Файлы в папке
- [lr2/er_diagram.mmd](lr2/er_diagram.mmd)
- [lr2/code/sneps_logic.sneps](lr2/code/sneps_logic.sneps)
- [lr2/code/sneps_ready.sneps](lr2/code/sneps_ready.sneps)
- [lr2/tests/tests.sneps](lr2/tests/tests.sneps)

Содержимое папки
- Пояснительная версия оформлена как псевдокод.
- Исполняемая часть написана на Java.
- Примеры фактов и запросов находятся в тестовой части лабораторной.
