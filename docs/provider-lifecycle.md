# Пользовательское состояние провайдера

В `ops_provider.h` объявлены функции `ops_provider_user_init`,
`ops_provider_user_cleanup` и getter `ops_provider_get_user_data(provctx)`.
Пользователь определяет собственную структуру, выделяет и освобождает её;
SDK хранит только указатель.
Публичного типа внутреннего контекста SDK нет.

```c
#include "openssl_provider_sdk/ops_crt.h"
#include "openssl_provider_sdk/ops_provider.h"

typedef struct my_state
{
    unsigned int setting;
} my_state;

int ops_provider_user_init(void *provctx, void **user_data)
{
    my_state *state = ops_malloc(provctx, sizeof *state);
    if (state == NULL)
    {
        return 0;
    }

    state->setting = 42;
    *user_data = state;
    return 1;
}

void ops_provider_user_cleanup(void *provctx, void *user_data)
{
    ops_free(provctx, user_data);
}
```

В callback алгоритма указатель получается без знания представления `provctx`:

```c
my_state *state = ops_provider_get_user_data(provctx);
```

## Порядок вызовов

1. SDK разбирает входящий core dispatch и создаёт внутренний контекст.
2. Вызывает user init с готовыми core-обёртками и `*user_data == NULL`.
3. После возврата `1` публикует провайдер OpenSSL.
4. При teardown вызывает user cleanup с тем же указателем и рабочими core-обёртками.
5. После возврата из cleanup освобождает внутренний контекст SDK.

После успешного init cleanup вызывается ровно один раз, даже если пользователь
оставил указатель NULL. При отказе init cleanup не вызывается: init обязан сам
закрыть частично открытые ресурсы. SDK освобождает только свой контекст и
возвращает отказ инициализации с выходными указателями NULL.

Getter доступен и во время init: пока `*user_data` не присвоено значение,
он возвращает NULL. Во время cleanup он возвращает пользовательский указатель.
После teardown `provctx` недействителен. Пользователь отвечает за синхронизацию
изменяемого состояния и освобождение его ресурсов.

## Обычные определения пользователя

Включите `ops_provider.h` и определите функции с указанными именами в своём
исходнике. Это обычные внешние определения: без `static`, weak-атрибутов или
макроса регистрации. Заголовок содержит обычные объявления внутри `extern "C"`
для C++; ключевое слово `extern` перед C-объявлением функции необязательно.
Объявления проверяют сигнатуры, но сами не создают реализации.

В заголовке публичные функции отмечены `OPS_API`, а заменяемые hooks
дополнительно отмечены `OPS_WEAK`:

```c
OPS_API OPS_WEAK int ops_provider_user_init(void *provctx, void **user_data);
OPS_API OPS_WEAK void ops_provider_user_cleanup(void *provctx, void *user_data);
```

Обе аннотации пустые и определены в `ops_defines.h`. `OPS_API` обозначает
публичный интерфейс без изменения visibility или calling convention.
`OPS_WEAK` подчёркивает возможность заменить SDK default, но не меняет linkage.
Пользовательские определения остаются обычными strong-функциями. Реальный
weak-атрибут применяется только к default-определениям внутри SDK; переносить
его в публичный заголовок нельзя, иначе он затронет определения пользователя.

```cmake
add_library(my_provider MODULE my_algorithms.c my_hooks.c)
target_link_libraries(my_provider PRIVATE openssl_provider_sdk_provider)
```

SDK прямо вызывает init и cleanup. На Linux SDK предоставляет weak-определения:
init устанавливает `*user_data = NULL` и возвращает `1`, cleanup ничего не делает.
Strong-определения пользователя заменяют их при окончательной линковке модуля.
На Windows аналогичное поведение обеспечивает MSVC `/alternatename`, связывая
отсутствующие имена hooks с default-функциями SDK. Механизмы изолированы в
`src/platform/linux.c` и `src/platform/windows.c`.

Оба hooks имеют реализации по умолчанию и могут переопределяться независимо.
Если init выделяет ресурсы, пользователь обязан также определить подходящий
cleanup. Проверять указатели hooks на NULL не требуется. Повторные strong-
определения одного hook в модуле приводят к ошибке линковки.
Пользовательские данные отдельны для каждого экземпляра, включая загрузки
одного модуля в разные `OSSL_LIB_CTX`.

## Hooks в отдельном статическом архиве

Основной вариант — непосредственно включить `my_hooks.c` в provider target.
Его объект участвует в линковке, поэтому пользовательское strong-определение
побеждает weak-default независимо от порядка обычных `.o` файлов.

Если `my_hooks.c` находится в другом `.a`, линкер может не извлечь его объект:
ссылка уже удовлетворена weak-default из SDK. Наличие strong-символа в таблице
архива ещё не означает участие его объекта в линковке. Это касается архива
с пользовательскими hooks; само подключение SDK как `.a` не мешает обычному
переопределению функциями из исходников модуля.

Для такого размещения явно включите пользовательский архив:

```cmake
add_library(my_hooks STATIC my_hooks.c)
set_target_properties(my_hooks PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(my_hooks PRIVATE openssl_provider_sdk_static)

target_link_libraries(my_provider PRIVATE
    "$<LINK_LIBRARY:WHOLE_ARCHIVE,my_hooks>")
```

Не полагайтесь на случайный порядок поиска архивов. В тесте `lifecycle_archive`
проверяется наличие пользовательского состояния у модуля с hooks из архива.

Обычные определения и defaults, отказы init, время жизни getter и доступность
core-функций во время cleanup проверяются тестами `test/lifecycle/`.
