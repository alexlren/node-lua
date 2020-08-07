#include "lua_interface.h"

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lstate.h>
#include <lundump.h>
#include <lprefix.h>

#define toproto(L, i) getproto(s2v(L->top + (i)))

static int sync_writer(lua_State *vm, const void *result, size_t size, void *out)
{
    struct c_buffer *buf = out;

    if (buf->len == 0) {
        buf->data = malloc(size);
    } else {
        buf->data = realloc(buf->data, buf->len + size);
    }

    if (!buf->data) {
        return -ENOMEM;
    }
    memcpy(buf->data + buf->len, result, size);
    buf->len += size;

    return 0;
}

int lua_compile(const char *sources, struct lua_result *result)
{
    lua_State* vm = luaL_newstate();
    const Proto* f_proto;
    int res;

    res = luaL_loadstring(vm, sources);
    if (res != LUA_OK) {
        const char *error = lua_tostring(vm, -1);
        size_t errlen = strlen(error);

        if (!errlen) {
            return res;
        }
        result->error = malloc((errlen + 1) * sizeof(char));
        if (!result->error) {
            return -ENOMEM;
        }
        strncpy(result->error, error, errlen + 1);
        return res;
    }
    f_proto = toproto(vm, -1);
    lua_lock(vm);
    res = luaU_dump(vm, f_proto, sync_writer, &result->bytecode, 1);
    lua_unlock(vm);

    lua_close(vm);
    return res;
}
