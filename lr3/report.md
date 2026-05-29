# Отчёт по лабораторной работе 3

## Цель
Построить фрагмент предметной области в SNePS для сценария «Университет»: задать иерархию ISA, определить экземпляры и проверить выводы по отношениям `takes` и `teaches`.

## Что сделано
- Выбрана предметная область «Университет».
- Определены понятия: `Person`, `Student`, `Undergraduate`, `Graduate`, `Professor`, `Course`.
- Добавлены отношения `takes` и `teaches`.
- Подготовлены два варианта представления:
  - [lr3/code/sneps_logic.sneps](lr3/code/sneps_logic.sneps) — пояснительная версия;
  - [lr3/code/sneps_ready.sneps](lr3/code/sneps_ready.sneps) — версия для загрузки в SNePS.
  - Подготовлены тесты в [lr3/tests/tests.sneps](lr3/tests/tests.sneps).
  - Построена ER-диаграмма в [lr3/er_diagram.mmd](lr3/er_diagram.mmd).

## Как это работает
- `Undergraduate -> Student -> Person` и `Graduate -> Student -> Person` задают наследование.
- `Professor -> Person` добавляет отдельную ветку иерархии.
- `instance-of` позволяет задавать экземпляры для студентов, преподавателей и курса.
- На основе этих фактов проверяются связи `takes` и `teaches`.

## Проверка
В контейнере и через JavaSnepsAPI запускались тесты, которые подтвердили:
- `instance_of_trans(alice, person)` — `true`
- `takes(alice, cs101)` — `true`
- `teaches(dr_smith, cs101)` — `true`
- `instance_of_trans(alice, student)` — `true`
- `instance_of_trans(dr_smith, person)` — `true`

## Вывод
Модель предметной области для ЛР3 собрана и проверена. Иерархия ISA и проверки по отношениям `takes`/`teaches` работают корректно, а демонстрация через JavaSnepsAPI позволяет запускать сценарий из локальной папки без ручной настройки консоли.