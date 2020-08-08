const lua = require('../build/Release/lua.node');

interface LuaResult {
    error?: string;
    bytecode?: Buffer;
}

function compile(sources: string): LuaResult {
    return lua.compile(sources);
}

export {
    compile,
    LuaResult,
};
