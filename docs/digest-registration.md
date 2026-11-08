# Статическое объявление digest-алгоритмов

Эта страница описывает текущую реализацию. Согласованное развитие общего
интерфейса и внешнего источника таблиц описано в
[политике алгоритмов](algorithm-policy.md); эти расширения ещё не реализованы.

SDK собирает объявления из разных `.c` файлов в непосредственный список
`OSSL_ALGORITHM`, завершённый нулевой записью. Динамической регистрации,
таблицы указателей и дополнительной структуры callbacks нет.

## Объявления

Подключите `openssl_provider_sdk/ops_algorithm.h`. Ниже фрагмент регистрации,
соответствующий тестовому алгоритму A; это **не самостоятельная реализация
SHA256**. Определения callbacks находятся в
[`test_digest_helpers.c`](../test/fixtures/test_digest_helpers.c), а их объявления — в
[`test_digest_helpers.h`](../test/fixtures/test_digest_helpers.h).

```c
#include "openssl_provider_sdk/ops_algorithm.h"

OSSL_FUNC_digest_newctx_fn ops_test_digest_newctx;
OSSL_FUNC_digest_freectx_fn ops_test_digest_freectx;
OSSL_FUNC_digest_init_fn ops_test_digest_init;
OSSL_FUNC_digest_update_fn ops_test_digest_update;
OSSL_FUNC_digest_final_fn ops_test_digest_final;
OSSL_FUNC_digest_get_params_fn ops_test_digest_get_params;
OSSL_FUNC_digest_gettable_params_fn ops_test_digest_gettable_params;

OPS_DECLARE_ALGORITHM_DISPATCH(ops_test_alpha_dispatch,
    OPS_FUNCTION(OSSL_FUNC_DIGEST_NEWCTX, ops_test_digest_newctx),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_FREECTX, ops_test_digest_freectx),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_INIT, ops_test_digest_init),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_UPDATE, ops_test_digest_update),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_FINAL, ops_test_digest_final),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_GET_PARAMS, ops_test_digest_get_params),
    OPS_FUNCTION(OSSL_FUNC_DIGEST_GETTABLE_PARAMS, ops_test_digest_gettable_params)
);

OPS_DECLARE_DIGEST(ops_test_alpha_algorithm,
    "OPS-TEST-SHA256-A",
    "provider=ops-test",
    ops_test_alpha_dispatch,
    "Test SHA256 forwarding implementation A"
);
```

Нативные typedef OpenSSL проверяют соответствие определений callbacks их
объявлениям. Cast внутри `OPS_FUNCTION` лишь преобразует указатель для хранения:
правильность пары идентификатор/функция выбирает автор. Не дублируйте ID.

Dispatch содержит хотя бы одну запись; собственный терминатор и запятая после
последней переданной записи запрещены. Макрос добавляет `{ 0, NULL }` сам.
Терминатор общего списка digest добавляет SDK, а не каждый алгоритм.

`OPS_DECLARE_DIGEST` применяется на уровне файла, ровно в одном `.c`, не в общем
заголовке. `symbol` записи должен быть уникален во всём конечном модуле: для
сохранения записи используется внешнее связывание. Dispatch остаётся
`static const`. Порядок алгоритмов не определён; конфликты имён и свойств
автоматически не разрешаются.

`names` — непустая строка имён/алиасов через двоеточие; `NULL` запрещён.
`properties` и `description` могут быть `NULL`. Все аргументы должны допускать
статическую инициализацию. Строки, таблица и callbacks живут до выгрузки модуля.

## Подключение через CMake

Требуются C11, CMake 3.24+ и OpenSSL 3.0+ development files.
Для модуля со стандартной точкой входа SDK подключите target провайдера:

```cmake
add_subdirectory("${OPS_SDK_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/ops-sdk")
target_link_libraries(my_provider PRIVATE openssl_provider_sdk_provider)
```

Target передаёт SDK, платформенные требования линковки и обеспечивает включение
`OSSL_provider_init` из статического архива. Эта функция реализована в
[`ops_provider.c`](../src/ops_provider.c); модулю достаточно исходников
алгоритмов. Исходники и object libraries добавляются обычными средствами CMake. Архивы с алгоритмами
нужно включать целиком, поскольку на отдельные записи нет внешних ссылок:

```cmake
target_link_libraries(my_provider PRIVATE
    "$<LINK_LIBRARY:WHOLE_ARCHIVE,my_algorithms>")
```

Сам архив должен иметь доступ к заголовкам и корректные compile settings.
Терминатор и getter поступают из SDK единственным экземпляром.
Для доступа к реестру без стандартной точки входа существует
`openssl_provider_sdk_registry`; утилиты SDK доступны через
`openssl_provider_sdk_static`.

### Установленный SDK

```sh
cmake --install build --prefix ./out/ops-sdk --config Debug
```

Вместо `add_subdirectory` используйте:

```cmake
find_package(openssl_provider_sdk 1 CONFIG REQUIRED)
target_link_libraries(my_provider PRIVATE openssl_provider_sdk_provider)
```

Передайте абсолютный путь к prefix через `CMAKE_PREFIX_PATH`.
Package config импортирует SDK и target реестра, находит OpenSSL Crypto
и подключает установленный linker script без ссылок на исходный checkout.

## Получение списка

Стандартный query callback библиотеки возвращает `ops_digest_algorithms()`
для `OSSL_OP_DIGEST`, устанавливает `no_store = 0` и возвращает `NULL` для
остальных операций. Каждая инициализация создаёт собственный приватный контекст с core handle
и входящей таблицей функций. OpenSSL передаёт его алгоритмам через `void *provctx`; этот указатель
передаётся обёрткам без преобразования.
Контекст выделяется и освобождается входящими `CRYPTO_malloc`/`CRYPTO_free`;
при отсутствии этих функций или отказе выделения init возвращает отказ.
Пользовательские init/cleanup и getter состояния описаны в
[контракте lifecycle](provider-lifecycle.md).
Подробнее: [сервисы core](core-services.md).
Пример модуля без собственного entry point —
[`test/provider/CMakeLists.txt`](../test/provider/CMakeLists.txt).

Getter возвращает неизменяемую память текущего модуля без передачи владения.
Список нельзя освобождать или менять во время выполнения. После выгрузки модуля
указатель недействителен. Пустой список содержит одну нулевую запись и не равен
`NULL`. Алгоритмы других динамических модулей сюда не объединяются.

## Проверка и ограничения

Для чтения и записи `OSSL_PARAM` по ключу используйте
[типизированные помощники](params.md). Тестовый digest применяет их в
`get_params` через цепочку `||`.

Из корня этого репозитория:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Зарегистрированы `digest_registry` (две записи, включая запись из архива),
`digest_empty` (пустой список), `digest_fetch` (реальная загрузка провайдера,
fetch обоих алгоритмов и проверка SHA256). Для последнего нужен OpenSSL provider
`default`: тестовые callbacks используют его для вычислений. Эти тесты проверяют
регистрацию и подключение, а не новую криптографическую реализацию.

Проверенная среда: Linux GNU ELF, GCC 11 и OpenSSL 3.0.2. Три теста прошли
в Debug и Release; Release проверен с IPO/LTO, function/data sections
и linker garbage collection.
Backend Windows MSVC реализован, но исполнение тестов на Windows не проверено.

Поддержка ограничена Linux ELF GCC/Clang с GNU-совместимым линкером и Windows
MSVC (x86, x64, ARM64). clang-cl, macOS и другие комбинации не поддержаны;
неподдерживаемые платформы завершают конфигурацию или компиляцию ошибкой.
Секционный список использует расширения toolchain, а не гарантию ISO C о
слиянии независимых объектов в массив. Layout, единственный терминатор,
выравнивание и сохранение GC/LTO обеспечиваются платформенным/build слоем:
обходить helpers нельзя.
