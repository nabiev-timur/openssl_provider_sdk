#ifndef OPS_ALGORITHM_H_
#define OPS_ALGORITHM_H_

#include "ops_defines.h"

#include <stddef.h>
#include <openssl/core.h>
#include <openssl/core_dispatch.h>


/**
 * @file ops_algorithm.h
 * @brief Статическое объявление алгоритмов OpenSSL в объектных файлах.
 * @note Для конечного модуля подключите CMake target:
 *     target_link_libraries(target PRIVATE openssl_provider_sdk_registry). Архивы с алгоритмами подключаются через
 *     target_link_libraries(target PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,archive>").
 * @note Поддерживаются Linux ELF с GNU GCC/Clang и Windows MSVC COFF.
 *     Платформенный и сборочный слои обеспечивают плотное размещение записей,
 *     единственный терминатор и сохранение данных и функций при GC/LTO.
 *     Неподдерживаемая платформа должна приводить к ошибке компиляции.
 */

/**
 * @brief Создаёт одну запись таблицы функций OpenSSL.
 * @param id Ненулевой идентификатор OSSL_FUNC_* соответствующей операции.
 * @param fn Имя функции с соответствующей идентификатору сигнатурой.
 * @note Приведение к типу хранения OSSL_DISPATCH не проверяет сигнатуру.
 *     До определения callback объявите его родным типом OpenSSL, например:
 *     static OSSL_FUNC_digest_init_fn example_init;
 *     Это проверяет определение функции; соответствие id и fn выбирает автор.
 */
#define OPS_FUNCTION(id, fn) \
    { (id), (void (*)(void))(fn) }

/**
 * @brief Объявляет цельную static const таблицу OSSL_DISPATCH.
 * @param symbol Имя массива с внутренним связыванием в текущем .c файле.
 * @param ... Одна или несколько записей OPS_FUNCTION, разделённых запятыми.
 * @note Объявляется на уровне файла и завершается вызывающим кодом знаком ;.
 *     После последней переданной записи запятая не ставится. Макрос добавляет
 *     единственный терминатор { 0, NULL }; передавать собственный нельзя.
 *     Идентификаторы должны соответствовать операциям и не дублироваться.
 */
#define OPS_DECLARE_ALGORITHM_DISPATCH(symbol, ...) \
    static const OSSL_DISPATCH symbol[] = { \
        __VA_ARGS__, \
        { 0, NULL } \
    }

/**
 * @brief Объявляет непосредственную const запись OSSL_ALGORITHM
 *     в секции digest текущего модуля.
 * @param symbol Имя записи, уникальное во всём конечном модуле.
 *     Платформа использует внешнее связывание для сохранения записи при линковке;
 *     symbol не является экспортируемым API потребителя.
 * @param names Непустая строка имён и алиасов OpenSSL, разделённых двоеточием.
 *     NULL запрещён: он обозначает конец списка алгоритмов.
 * @param properties Строка определения свойств OpenSSL либо NULL.
 * @param dispatch Статическая таблица функций digest с нулевым терминатором.
 * @param description Строка описания алгоритма либо NULL.
 * @note Все аргументы должны допускать статическую инициализацию; строки,
 *     таблица и функции существуют всё время жизни модуля. Запись объявляется
 *     ровно в одном .c файле на уровне файла, а не в общем заголовке.
 *     Вызов макроса завершается знаком ;. Терминатор списка добавляет платформа,
 *     а не пользователь. Порядок алгоритмов не определён; конфликтующие имена
 *     и свойства автоматически не разрешаются.
 */
#if defined(_MSC_VER) && !defined(__clang__)

#if defined(_M_IX86)
#define OPS_DECLARE_DIGEST(symbol, names, properties, dispatch, description) \
    __pragma(section(".opsdg$m", read)) \
    __pragma(comment(linker, "/include:_" #symbol)) \
    __declspec(allocate(".opsdg$m")) __declspec(align(4)) \
    const OSSL_ALGORITHM symbol = { \
        (names), (properties), (dispatch), (description) \
    }
#elif defined(_M_X64) || defined(_M_ARM64)
#define OPS_DECLARE_DIGEST(symbol, names, properties, dispatch, description) \
    __pragma(section(".opsdg$m", read)) \
    __pragma(comment(linker, "/include:" #symbol)) \
    __declspec(allocate(".opsdg$m")) __declspec(align(8)) \
    const OSSL_ALGORITHM symbol = { \
        (names), (properties), (dispatch), (description) \
    }
#else
#error "Digest sections require MSVC x86, x64, or ARM64"
#endif

#elif defined(__linux__) && defined(__ELF__) && \
    (defined(__GNUC__) || defined(__clang__))

/* Compiler emission and linker retention are separate responsibilities. */
#define OPS_DECLARE_DIGEST(symbol, names, properties, dispatch, description) \
    const OSSL_ALGORITHM symbol \
    __attribute__((section(".ops_digest.entries"), used, \
        aligned(__alignof__(OSSL_ALGORITHM)), visibility("hidden"))) = { \
        (names), (properties), (dispatch), (description) \
    }

#else
#error "Digest sections require Linux ELF GCC/Clang or Windows MSVC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Возвращает неизменяемый список digest-алгоритмов текущего модуля.
 * @return Ненулевой указатель на плотный массив OSSL_ALGORITHM с единственной
 *     завершающей нулевой записью. Пустой список состоит только из терминатора.
 * @note При корректной сборке не выделяет память и не передаёт владение.
 *     Изменять или освобождать список нельзя. Список и связанные с ним данные
 *     действительны до выгрузки модуля. Реестр не является списком алгоритмов
 *     других динамических модулей и не поддерживает динамическую регистрацию.
 */
OPS_API const OSSL_ALGORITHM *ops_digest_algorithms(void);

#ifdef __cplusplus
}
#endif

#endif // !OPS_ALGORITHM_H_
