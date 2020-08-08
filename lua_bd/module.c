#define NAPI_VERSION 3

#include "lua_interface.h"
#include "utils.h"

#include <node_api.h>
#include <errno.h>
#include <string.h>

static napi_value compile_to_bytecode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    int err = 0;
    char *sources = NULL;
    size_t str_len = 0;
    struct lua_result result = {
        .error = NULL,
        .bytecode = {
            .data = NULL,
            .len = 0
        }
    };
    napi_status jsres;
    napi_value jssources;
    napi_value jsresult;
    napi_value jsbuf;
    napi_value jserror;

    jsres = napi_get_cb_info(env, info, &argc, &jssources, NULL, NULL);
    if (jsres != napi_ok) {
        napi_throw_error(env, "EINVAL", "Call to napi_get_cb_info failed");
        return NULL;
    }
    if (argc < 1) {
        napi_throw_error(env, "EINVAL", "Expected 1 argument");
        return NULL;
    }

    jsres = get_utf8_string(env, jssources, &sources, &str_len);
    if (jsres != napi_ok) {
        goto err;
    }

    jsres = napi_create_object(env, &jsresult);
    if (jsres != napi_ok) {
        goto err;
    }

    err = lua_compile(sources, &result);
    if (err != 0) {
        if (result.error) {
            jsres = napi_create_string_utf8(env, result.error,
                                            NAPI_AUTO_LENGTH, &jserror);
            if (jsres != napi_ok) {
                goto err;
            }
            jsres = napi_set_named_property(env, jsresult, "luaError", jserror);
        } else {
            goto err;
        }
    } else if (result.bytecode.len > 0) {
        void *jsbuf_memory = malloc(result.bytecode.len);

        if (!jsbuf_memory) {
            err = -ENOMEM;
            goto err;
        }

        jsres = napi_create_buffer_copy(env, result.bytecode.len,
                                        (void *)result.bytecode.data,
                                        &jsbuf_memory, &jsbuf);

        if (jsres != napi_ok) {
            goto err;
        }
        jsres = napi_set_named_property(env, jsresult, "bytecode", jsbuf);
    }

    if (jsres != napi_ok) {
        goto err;
    }

    if (sources) {
        free(sources);
    }
    if (result.bytecode.data) {
        free(result.bytecode.data);
    }
    return jsresult;

err:
    if (err < 0) {
        napi_throw_error(env, "EINVAL", strerror(-err));
    } else {
        const napi_extended_error_info *errinfo = NULL;

        napi_get_last_error_info(env, &errinfo);
        napi_throw_error(env, "EINVAL", errinfo->error_message);
    }
    if (sources) {
        free(sources);
    }
    if (result.bytecode.data) {
        free(result.bytecode.data);
    }
    return NULL;
}

napi_value module_init(napi_env env, napi_value exports)
{
    napi_value fn;
    napi_status err;

    /* Map C function `compile_to_bytecode` to JS function `fn` */
    err = napi_create_function(env, NULL, 0, compile_to_bytecode, NULL, &fn);
    if (err != napi_ok) {
        napi_throw_error(env, "EINVAL", "Cannot create function");
        return NULL;
    }

    /* module.exports.compile = fn; */
    err = napi_set_named_property(env, exports, "compile", fn);
    if (err != napi_ok) {
        napi_throw_error(env, "EINVAL", "Cannot set named property");
        return NULL;
    }

    return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, module_init)
