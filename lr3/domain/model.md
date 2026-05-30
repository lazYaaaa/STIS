# Модель предметной области: университет

Автор: Лазарев Ярослав Б23-514

## Понятия
- Person
- Student
- Undergraduate
- Graduate
- Professor
- Course

## Иерархия
- Undergraduate → Student → Person
- Graduate → Student → Person
- Professor → Person

## Связи и правила
- Если объект — Student, а второй объект — Course, то действует связь takes
- Если объект — Professor, а второй объект — Course, то действует связь teaches
- instance-of поднимается вверх по ISA-цепочке
- Проверки выводов должны показывать принадлежность студентов и преподавателей к Person

## Тестовые объекты
- alice — Undergraduate
- bob — Graduate
- dr_smith — Professor
- cs101 — Course
