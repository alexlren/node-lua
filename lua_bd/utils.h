#ifndef UTILS_H
# define UTILS_H

# include <node_api.h>
# include <stdlib.h>

napi_status get_utf8_string(napi_env env, napi_value src, char **dest, size_t *size);

#endif /* !UTILS_H */
