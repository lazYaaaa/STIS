# Псевдокод ЛР3: университет

Предметная область: университет.

Понятия:
- Person
- Student
- Undergraduate
- Graduate
- Professor
- Course

Иерархия:
- Undergraduate -> Student -> Person
- Graduate -> Student -> Person
- Professor -> Person

Связи и правила:
- если объект является Student и второй объект является Course, то действует связь takes;
- если объект является Professor и второй объект является Course, то действует связь teaches;
- instance-of поднимается вверх по ISA-цепочке;
- проверки выводов должны показывать принадлежность студентов и преподавателей к Person.

Тестовые объекты:
- alice — Undergraduate
- bob — Graduate
- dr_smith — Professor
- cs101 — Course

Проверяемые выводы:
- alice и bob должны быть Student и Person;
- dr_smith должен быть Person;
- takes(alice, cs101) и takes(bob, cs101) должны быть истинными;
- teaches(dr_smith, cs101) должно быть истинным.