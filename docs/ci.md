# GitHub Actions

Workflow находится в `.github/workflows/ci.yml` и запускается при push,
pull request или вручную через Actions. Новая проверка той же ветки отменяет
предыдущую незавершённую. Workflow использует только чтение репозитория;
публикации образов, релизов и пакетов в нём нет.

GitHub предоставляет Linux runner с Docker. Сам проект собирается внутри
нашего Ubuntu 26.04 образа из `docker/Dockerfile.openssl_provider_sdk.ubuntu26.04`.
Образ создаётся без файлового build context, а checkout подключается только
при запуске контейнера, для чтения.

## Проверки

- `debug`: SDK, примеры и все CTest, включая штатный OpenSSL CLI.
- `release`: тот же набор с LTO и удалением неиспользуемых секций.
- `sanitize`: C-тесты с AddressSanitizer и UBSan. CLI-тесты исключены, поскольку
  системный executable `openssl` не собран с ASan; они выполняются в других режимах.
- `package`: сборка только SDK, установка в staging prefix, перемещение prefix
  и исходного build tree, затем сборка независимого потребителя через
  `find_package`. Проверяются пользовательские hooks и результат dummy hash.

Команды перечислены непосредственно в workflow. Отдельных shell/Python-скриптов
для их диспетчеризации нет. Debug использует стандартную команду Dockerfile;
остальные шаги вызывают CMake и CTest напрямую.

Проверка установленного пакета — самостоятельный CMake-проект в `test/package/`.
Его можно запустить после установки SDK:

```sh
cmake -S test/package -B build-consumer -DCMAKE_PREFIX_PATH=/absolute/sdk/prefix
cmake --build build-consumer --parallel
ctest --test-dir build-consumer --output-on-failure
```

Для Debug в том же образе:

```sh
docker build -t ops-sdk-ci:ubuntu26.04 - < docker/Dockerfile.openssl_provider_sdk.ubuntu26.04
docker run --rm --mount "type=bind,source=$(pwd),target=/workspace,readonly" ops-sdk-ci:ubuntu26.04
```

Команды Release/LTO также приведены в [docker-build.md](docker-build.md).
Каждый шаг CI использует новый контейнер; checkout подключён для чтения.
Потребители установленного SDK используют реальные исходники примера и fixture,
а не подставные зависимости.

## Результаты на GitHub

После push результаты появятся во вкладке Actions и в проверках pull request.
Секреты и registry credentials для этого workflow не нужны. Если Actions
отключён настройками репозитория или организации, его потребуется включить.
Обязательное прохождение CI перед merge настраивается отдельно в правилах ветки.

Это Linux CI. Native Windows/MSVC сборка пока остаётся непроверенной.
