# node-lua

Lua bindings for node.js

## Installation

```
$ yarn add @willo/node-lua
```

## API

### `compile(sources)`

This compiles lua source code to a bytecode buffer

- `sources`: string - the lua source code
- returns a LuaResult object:

```typescript
{
    luaError?: string, // The error as retrieved from lua
    error?: LuaError, // An error object
    bytecode?: Buffer
}
```

## Example

```js
const lua = require('@willo/node-lua');

try {
    const result = lua.compile("print('2 + 10 * 4')");
    if (result.error) {
        // Handle lua error
    }
    console.log(result.bytecode);
    /* <Buffer 1b 4c 75 61 54 ...> */
} catch (err) {
    // Handle global error (memory or unexpected library errors)
    console.error('Something wrong happened:', err);
}
```
