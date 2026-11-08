# Параметры по имени и типу

`ops_params.h` объединяет поиск ключа и родной вызов `OSSL_PARAM_get_*` или
`OSSL_PARAM_set_*`. Доступны числовые типы OpenSSL, строки, octet buffers,
указатели и BIGNUM. Контекст провайдера не требуется.

## Контракт

- Get/set возвращают `1` при успехе и `0` при ошибке найденного параметра.
- Отсутствующий ключ означает успех без изменения выходных аргументов.
- `params == NULL` означает пустой список; `key == NULL` означает ошибку.
- `ops_params_has(params, key)` возвращает `1` только при наличии ключа;
  для NULL-массива или NULL-ключа возвращается `0`.
- Ключи сравниваются точно, с учётом регистра. При дубликатах используется
  первая запись. Массив завершается `OSSL_PARAM_END`.
- Типы преобразуются по правилам OpenSSL, без молчаливого усечения значений.
  Найденный параметр с несовместимым типом или размером приводит к ошибке.
- У setters сохраняется `return_size`, включая запрос размера с `data == NULL`.
  Getters требуют реальные данные; запрос размера не является чтением значения.

## Ответ на get_params

```c
int digest_get_params(OSSL_PARAM params[])
{
    if (!ops_params_set_size_t(params, OSSL_DIGEST_PARAM_SIZE, 32)
        || !ops_params_set_size_t(params, OSSL_DIGEST_PARAM_BLOCK_SIZE, 64)
        || !ops_params_set_int(params, OSSL_DIGEST_PARAM_XOF, 0))
    {
        return 0;
    }
    return 1;
}
```

Get callback записывает ответ через `ops_params_set_*`. Set callback читает
входные значения через `ops_params_get_*`:

```c
unsigned int rounds = ctx->rounds;
size_t output_size = ctx->output_size;

if (!ops_params_has(params, "rounds") /* обязательный ключ */
    || !ops_params_get_uint(params, "rounds", &rounds)
    || !ops_params_get_size_t(params, "output-size", &output_size))
{
    return 0;
}
/* Проверить допустимость значений для алгоритма, затем применить. */
ctx->rounds = rounds;
ctx->output_size = output_size;
```

`||` останавливается на первой ошибке. Ранее выполненные записи не откатываются.
Для целостного изменения состояния используйте промежуточные значения и
применяйте их после всех проверок. Отсутствие ключа сохраняет прежнее значение.

## Буферы и владение

Сохраняются сигнатуры и правила родных OpenSSL helpers. `get_utf8_string` и
`get_octet_string` могут выделять память при `*val == NULL`; её освобождают
через `OPENSSL_free`. BIGNUM освобождается через `BN_free`. Эти функции используют
связанную libcrypto, а не входящий allocator провайдера. Для чтения без выделений
передайте собственный буфер или используйте соответствующий getter указателя.

Возвращённые указатели заимствованы. Их время жизни определяется исходными
данными. Для PTR-параметров `data` указывает на переменную указателя;
`data_size` описывает длину данных, а не размер указателя. Setter обновляет
`return_size`, сохраняя `data_size` и остальные поля дескриптора.

Тесты находятся в `test/params/`. Для выбора: `ctest --test-dir build -L params`.
