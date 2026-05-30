Лабораторная работа 3 — моделирование фрагмента предметной области в SNePS

Автор: Лазарев Ярослав Б23-514

Выбранный фрагмент: Университет
- Понятия: `Person`, `Student`, `Undergraduate`, `Graduate`, `Professor`, `Course`.
- Связи: `teaches` (преподаёт), `takes` (посещает/записан на курс).
- Иерархия: `Undergraduate` ISA `Student`, `Graduate` ISA `Student`, `Student` ISA `Person`, `Professor` ISA `Person`.

Файлы
- `er_diagram.mmd` — ER-диаграмма.
- `domain/model.md` — описание предметной области.
- `domain/ERD.png` — ER-диаграмма.
- `tests/tests.sneps` — тесты и примеры запросов.

Содержимое папки
- Пояснительная версия оформлена как описание предметной области.
- Исполняемая часть написана на Java.
- Есть схема предметной области и тестовая часть.
