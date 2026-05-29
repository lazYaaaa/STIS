# Отчёт по лабораторной работе 2

## Цель
Построить фрагмент предметной области в SNePS: выбрать набор понятий, задать иерархию ISA, реализовать `instance-of`, проверить транзитивность и показать работу отношений на примере модели «Библиотека».

## Что сделано
- Выбрана предметная область «Библиотека».
- Определены понятия: `Person`, `Reader`, `AdultReader`, `ChildReader`, `Librarian`, `Book`.
- Добавлены отношения `borrows` и `recommends`, а также иерархия `ISA`.
- Подготовлены две формы представления: псевдокод для пояснения модели и Java-реализация для запуска.
- Добавлена тестовая часть и схема предметной области.

## Как это работает
- Псевдокод показывает структуру понятий и правил без привязки к синтаксису конкретной среды.
- Java-реализация формирует знания и запросы через SNePS API.
- `ISA(AdultReader, Reader)` и `ISA(Reader, Person)` задают цепочку наследования.
- `ISA(ChildReader, Reader)` показывает альтернативную ветку для читателей.
- `instance-of` переносится вверх по иерархии.
- Связи `borrows` и `recommends` проверяются по типам объектов.

## Проверка
В контейнере запускался симулятор логики (`tools/sneps_sim.pl`), который подтвердил:
- `instance_of_trans(alice, person)` — `true`
- `instance_of_trans(bob, person)` — `true`
- `instance_of_trans(elena, person)` — `true`
- `instance_of_trans(book1, item)` — `true`
- `borrows(alice, book1)` — `true`
- `borrows(bob, book1)` — `true`
- `recommends(elena, book1)` — `true`
- `rel_instance(borrows(alice,book1), borrows_reader)` — `true`
- `rel_instance(recommends(elena,book1), recommends_librarian)` — `true`

## Вывод
Модель предметной области для ЛР2 собрана и проверена. Псевдокод и Java-часть согласованы, а иерархия понятий, вывод по `ISA`, перенос `instance-of` и проверка отношений работают корректно.
