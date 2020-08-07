#include "utils.h"

napi_status get_utf8_string(napi_env env, napi_value src, char **dest, size_t *size)
{
    size_t len = 0;
    size_t len2 = 0;
    char *cstr = NULL;
    napi_status res;

    if (dest == NULL) {
        return napi_invalid_arg;
    }

    /* Retrieve size first */
    res = napi_get_value_string_utf8(env, src, NULL, 0, &len);
    if (res != napi_ok) {
        return res;
    }

    cstr = malloc(len + 1);
    if (!cstr) {
        return napi_generic_failure;
    }

    /* Store value */
    res = napi_get_value_string_utf8(env, src, cstr, len + 1, &len2);
    if (res != napi_ok) {
        free(cstr);
        return napi_generic_failure;
    }

    cstr[len] = '\0';
    *dest = cstr;

    if (size) {
        *size = len;
    }
    return napi_ok;
}
