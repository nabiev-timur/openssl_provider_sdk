# Демонстрационный провайдер

`example/` содержит реализации, сгруппированные по классам алгоритмов.
Сейчас есть `digest/dummy_hash.c`: сумма байт по модулю 2^32, представленная
четырьмя байтами в big-endian порядке. Это учебный алгоритм, не криптографический хеш.

Все классы подключаются к одному модулю `ops_example`. Для нового класса
добавляйте каталог с локальным `CMakeLists.txt` и подключайте его target в
`example/CMakeLists.txt`. Инициализацию и core dispatch предоставляет SDK.
Пока регистрация в SDK реализована только для digest; другие классы потребуют
согласованного общего реестра операций.

## Сборка и запуск

```sh
cmake -S . -B build -DOPS_BUILD_EXAMPLES=ON -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build -L example --output-on-failure
openssl list -provider-path build/example -provider ops_example -digest-algorithms
openssl dgst -provider-path build/example -provider ops_example -propquery provider=ops-example -OPS-DUMMY-HASH input.txt
```

В Visual Studio укажите каталог модуля соответствующей конфигурации.
`OPS_BUILD_EXAMPLES` включён по умолчанию для самостоятельной сборки SDK,
а при подключении SDK через `add_subdirectory` выключен. Установка библиотеки
не устанавливает учебный провайдер автоматически.

## Общая интеграционная проверка

`test/example/` собирает один host-процесс `ops_example_test`, который загружает
модуль через OpenSSL. Сейчас он проверяет параметры и принадлежность digest
провайдеру, потоковый ввод, пустой ввод, повторную инициализацию, бинарные данные
и переполнение суммы. Два дополнительных CTest запускают штатный OpenSSL CLI.

С добавлением классов алгоритмов расширяйте сценарии общего host-теста отдельными
исходниками по классам. Независимые проверки SDK в остальных каталогах `test/`
сохраняют свои небольшие цели; пример демонстрирует совместную работу частей.
