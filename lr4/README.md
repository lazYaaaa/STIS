Лабораторная работа №4 — `LazySequence` и потоки (Streams)

Реализация на C++ с использованием CMake и Catch2 для тестов.

Структура папки `lr4`:
- `domain/` — описание предметной области и ER-диаграмма
- `cpp/` — C++ проект (заголовки в `include/`, исходники в `src/`, тесты в `tests/`)
- `report.md` — отчёт по работе (цель, описание предметной области, тесты, выводы)

Что реализовано в проекте `cpp`:
- `Sequence<T>` — базовый АТД для последовательностей (включая материализованные и ленивые реализации)
- `LazySequence<T>` — ленивый источник с мемоизацией, операции `Map`, `Zip`, `Append`, `GetSubsequence`
- `Event<T>` — тип события с временной меткой
- `ReadOnlyStream<T>` / `WriteOnlyStream<T>` — простые реализации потоков
- `SynchronizeStreams` — вспомогательная функция для синхронизации временных потоков по опорному потоку
- Тесты на Catch2 покрывают основные операции и сценарий синхронизации
- CLI: `cpp/src/main.cpp` — интерактивная программа для демонстрации и ручного тестирования

Сборка и запуск тестов:

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
ctest -C Release --output-on-failure
```

Запуск CLI (после сборки):

```bash
cd build/src/Release
lr4_cli.exe
```

Дальнейшие шаги: доработать оптимизацию синхронизации, добавить более продвинутые сценарии и GUI/визуализацию при необходимости.

Быстрая сборка
 - На Windows (PowerShell): запустите `build.ps1` из папки `lr4`:

```powershell
cd lr4
.\build.ps1 Release
```

 - На Unix-подобных системах:

```bash
cd lr4
./build.sh Release
```

Можно также сконфигурировать вручную и собрать:

```powershell
cd lr4
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```