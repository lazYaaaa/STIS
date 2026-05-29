Лабораторная работа 3 — моделирование фрагмента предметной области в SNePS

Выбранный фрагмент: Университет
- Понятия: `Person`, `Student`, `Undergraduate`, `Graduate`, `Professor`, `Course`.
- Связи: `teaches` (преподаёт), `takes` (посещает/записан на курс).
- Иерархия: `Undergraduate` ISA `Student`, `Graduate` ISA `Student`, `Student` ISA `Person`, `Professor` ISA `Person`.

Файлы
- `er_diagram.mmd` — ER-диаграмма.
- `code/sneps_logic.sneps` — пояснительная версия логики.
- `code/sneps_ready.sneps` — SNePS-ready адаптация.
- `tests/tests.sneps` — тесты и примеры запросов.

Инструкция: запуск и тестирование выполняются в контейнере; см. `RUN_ALL.md`.
