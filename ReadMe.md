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

На всех платформах для запуска требуется наличие cmake 3.1, или выше.
Требуется компилятор с поддержкой C++11 (gcc 4.9.4 и выше, или )

## на виндоус

* запустить powershell в корне репозитория
* запустить команду для генерации солюшена `.\make.ps1 -gen`, она должна отработать успешно.
* запустить команду сборки `.\make.ps1 -build`, она должна отработать успешно.
* можно запустить тесты `.\make.ps1 -test`, команда в конце должна вывести `[ALL OK]` если тесты прошли успешно.
* запустить пример можно набрав `.\make.ps1 -run`

## на виндоус (альтернативный вариант)

* запустить VS2017 или VS2019 (на других студиях всё не так просто, ибо про существование cmake они не знают), выбрать пункт "Открыть папку", указать путь к репозиторию.
* выбрать таргетом `example`
* дождаться пока cmake сделает свои грязные делишки по генерации солюшена
* собрать
* запустить

## на линукс/мак

* открыть консоль в корне репозитория
* запустить команду для генерации солюшена `./make.sh -gen`, она должна отработать успешно.
* запустить команду сборки `./make.sh -build`, она должна отработать успешно.
* можно запустить тесты `./make.sh -test`, команда в конце должна вывести `[ALL OK]` если тесты прошли успешно.
* запустить пример можно набрав `./make.sh -run`

### дебажная сборка, проверка памяти, проверка старым gcc и cmake
```
cd docker-tests
docker-compose up
```

# как пользоваться программой-примером

Программа работает используя интерфейс командной строки.
Она ожидает на входе строки из `stdin` разделённые между собой переносом строки (`\n`, либо `\r\n`).
Когда ввод строк завершён, программа ожидает что будет конец ввода (так называемый EOF), либо на вход будет подана непустая строка.

*Примечание*
Для правильной работы программы-примера необходимо подавать на вход только ASCII строки.
Строки в других кадировках программа может воспринимать неверно.
