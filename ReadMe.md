targem task
===========

# задача

Реализовать класс динамических строк, который:

1. Написан на C++11 без каких либо сторонних библиотек. Не использует в своей основе 
какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.

2. Имеет конструктор копирования, оператор присваивания и поддерживает move-сематнику.
У класса есть "внешний" оператор сложения двух строк.

3. Поддерживает строки произвольного размера, используя базовые операции работы с 
динамическим хипом (функции malloc()/free() или операторы new/delete).

Написать пример с использованием этого класса строк и какого-либо контейнера STL. 
Программа должна принимать список строк, затем выдавать его в порядке, обратном
лексикографическому без учета регистра.

Программа-пример работает из командной строки.

# как собирать и запускать

## на виндоус

* запустить powershell в корне репозитория
* запустить команду для генерации солюшена `.\make.ps1 -gen`, она должна отработать успешно.
* запустить команду сборки `.\make.ps1 -build`, она должна отработать успешно.
* можно запустить тесты `.\make.ps1 -test`, команда в конце должна вывести `[ALL OK]` если тесты прошли успешно.

### альтернативный вариант

* запустить VS2017 или VS2019, выбрать пункт "Открыть папку", указать путь к репозиторию.  
* выбрать таргетом `example`
* собрать

## на линукс/мак

* открыть консоль в корне репозитория
* выполнить команды
```
mkdir obj
cmake -H. -Bobj -DCMAKE_BUILD_TYPE=Release
cmake --build obj
```

### дебажная сборка и проверка памяти
```
mkdir obj
cmake -H. -Bobj -DCMAKE_BUILD_TYPE=Debug
cmake --build obj --clean-first -- VERBOSE=1
valgrind --track-origins=yes ./obj/example
```