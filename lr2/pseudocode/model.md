# Псевдокод ЛР2: библиотека

Предметная область: библиотека.

Понятия:
- Person
- Reader
- AdultReader
- ChildReader
- Librarian
- Book
- Item

Иерархия:
- AdultReader -> Reader -> Person
- ChildReader -> Reader -> Person
- Librarian -> Person
- Book -> Item

Связи и правила:
- если объект является Reader и второй объект является Book, то действует связь borrows;
- если объект является Librarian и второй объект является Book, то действует связь recommends;
- если типы связей связаны по иерархии, то вывод переносится вверх по этой иерархии;
- instance-of поднимается по ISA-цепочке.

Тестовые объекты:
- alice — AdultReader
- bob — ChildReader
- elena — Librarian
- book1 — Book

Проверяемые выводы:
- alice и bob должны наследовать Person через Reader;
- book1 должен наследовать Item;
- borrows(alice, book1) и borrows(bob, book1) должны быть истинными;
- recommends(elena, book1) должно быть истинным.