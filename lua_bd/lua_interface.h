#ifndef LUA_INTERFACE_H
# define LUA_INTERFACE_H

# include <stdlib.h>

struct c_buffer {
    unsigned char *data;
    size_t len;
};

struct lua_result {
    char *error;
    struct c_buffer bytecode;
};

int lua_compile(const char *sources, struct lua_result *result);

#endif /* !LUA_INTERFACE_H */
