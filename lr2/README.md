Лабораторная работа 2 — моделирование фрагмента предметной области в SNePS

Автор: Лазарев Ярослав Б23-514

Предметная область
- Библиотека.
- Понятия: `Person`, `Reader`, `AdultReader`, `ChildReader`, `Librarian`, `Book`.
- Связи: `borrows` и `recommends`.
- Иерархия: `AdultReader` ISA `Reader`, `ChildReader` ISA `Reader`, `Reader` ISA `Person`, `Librarian` ISA `Person`, `Book` ISA `Item`.

Файлы в папке
- [lr2/er_diagram.mmd](lr2/er_diagram.mmd)
- [lr2/domain/model.md](lr2/domain/model.md)
- [lr2/domain/ERD.png](lr2/domain/ERD.png)
- [lr2/tests/tests.sneps](lr2/tests/tests.sneps)

Содержимое папки
- Пояснительная версия оформлена как описание предметной области.
- Исполняемая часть написана на Java.
- Примеры фактов и запросов находятся в тестовой части лабораторной.
