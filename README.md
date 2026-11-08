# OpenSSL Provider SDK

C11 SDK для провайдеров OpenSSL 3: стандартная точка входа, статический реестр
алгоритмов, доступ к входящим core-функциям, пользовательский lifecycle и
типизированная работа с параметрами по имени.

Сейчас реестр поддерживает **digest**. Общая регистрация остальных операций и
внешний источник таблиц ещё не реализованы; статус решений описан в
[политике алгоритмов](docs/algorithm-policy.md).

## Структура

- `include/openssl_provider_sdk/` — публичные заголовки.
- `src/` — реализация; `src/platform/` — Linux ELF и Windows MSVC COFF.
- `cmake/` — настройки targets, платформы, линковка и установка.
- `example/digest/` — учебный dummy hash; общий модуль `ops_example`.
- `test/` — проверки SDK, lifecycle, параметров и загрузки через OpenSSL.
- `docker/` — самодостаточный образ инструментов сборки Ubuntu 26.04.

## Сборка и проверка

Нужны CMake 3.24+, C11-компилятор и OpenSSL 3.0+ development files.
При включённых тестах также нужна утилита `openssl`.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DOPS_WARNINGS_AS_ERRORS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Текущие проверки включают настоящий OpenSSL CLI, два независимых экземпляра
провайдера, strong/default hooks, включение архивов, параметры и linker GC/LTO.
Проверено на Linux с GCC 15.2 и OpenSSL 3.5.5. Windows/MSVC backend реализован,
но пока не проверен сборкой. macOS backend отсутствует.

Для Visual Studio используйте генератор `"Visual Studio 17 2022" -A x64`,
затем `cmake --build build --config Debug` и `ctest --test-dir build -C Debug`.
Каталоги модулей у такого генератора включают имя конфигурации.

Для сборки только библиотеки:

```sh
cmake -S . -B build -DBUILD_TESTING=OFF -DOPS_BUILD_EXAMPLES=OFF
cmake --build build --parallel
```

`OPS_BUILD_EXAMPLES` по умолчанию включён для самостоятельной сборки SDK.
Команды Docker и Release/LTO: [docker-build.md](docs/docker-build.md).

## Создание провайдера

В проекте потребителя подключите SDK и определите модуль:

```cmake
add_subdirectory(path/to/openssl_provider_sdk ops-sdk)
add_library(my_provider MODULE my_digest.c my_hooks.c)
target_link_libraries(my_provider PRIVATE openssl_provider_sdk_provider)
```

SDK предоставляет `OSSL_provider_init`; пользователь пишет callbacks алгоритма
и объявления `OPS_DECLARE_ALGORITHM_DISPATCH` и `OPS_DECLARE_DIGEST`.
Подключение архива с алгоритмами требует `WHOLE_ARCHIVE`.
Подробный пример: [digest-registration.md](docs/digest-registration.md).

Для пользовательского состояния достаточно обычных определений
`ops_provider_user_init` и `ops_provider_user_cleanup` из `ops_provider.h`.
Доступ из callback алгоритма — `ops_provider_get_user_data(provctx)`.
Контракт отказа и правила линковки: [provider-lifecycle.md](docs/provider-lifecycle.md).

Два других targets доступны отдельно: `openssl_provider_sdk_static` предоставляет
утилиты, а `openssl_provider_sdk_registry` добавляет линковку реестра.

## Запуск примера

После обычной Linux-сборки:

```sh
printf abc > build/abc.txt
openssl dgst -provider-path build/example -provider ops_example -propquery provider=ops-example -OPS-DUMMY-HASH build/abc.txt
```

Результат — `00000126`. Dummy hash вычисляет сумму байт по модулю 2^32 и
**не является криптографическим хешем**. Сценарии общего примера:
[examples.md](docs/examples.md).

## Установка

```sh
cmake --install build --prefix ./out/ops-sdk --config Debug
```

Потребитель установленного SDK использует:

```cmake
find_package(openssl_provider_sdk 1 CONFIG REQUIRED)
target_link_libraries(my_provider PRIVATE openssl_provider_sdk_provider)
```

Передайте абсолютный путь к prefix через `CMAKE_PREFIX_PATH`. Устанавливаются
статическая библиотека, публичные заголовки и CMake package; тестовые и учебные
провайдеры автоматически не устанавливаются.

## Документация

- [Сервисы core: память, BIO и контекст](docs/core-services.md).
- [Параметры по имени и типу](docs/params.md).
- [Пользовательское состояние и hooks](docs/provider-lifecycle.md).

## Лицензия

[MIT](LICENSE).
