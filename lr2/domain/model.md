# Модель предметной области: библиотека

## Понятия
- Person
- Reader
- AdultReader
- ChildReader
- Librarian
- Book
- Item

## Иерархия
- AdultReader → Reader → Person
- ChildReader → Reader → Person
- Librarian → Person
- Book → Item

## Связи и правила
- Если объект — Reader, а второй объект — Book, то действует связь borrows
- Если объект — Librarian, а второй объект — Book, то действует связь recommends
- Если типы связей связаны по иерархии, то вывод переносится вверх по этой иерархии
- instance-of поднимается по ISA-цепочке

## Тестовые объекты
- alice — AdultReader
- bob — ChildReader
- elena — Librarian
- book1 — Book
