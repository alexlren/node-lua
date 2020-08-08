const lua = require('../build/Release/lua.node');

interface LuaError {
    token: string;
    msg: string;
    line?: number;
};

interface LuaResult {
    luaError?: string;
    error?: LuaError;
    bytecode?: Buffer;
}

function compile(sources: string): LuaResult {
    const res: LuaResult = lua.compile(sources);

    if (res.luaError) {
        const match = res.luaError.match(/^\[([^\]]+)\]:(\d+)?:? (.+)$/);

        if (match) {
            res.error = {
                token: match[1] || '',
                line: parseInt(match[2]),
                msg: match[3] || res.luaError,
            };
        }
    }
    return res;
}

export {
    compile,
    LuaError,
    LuaResult,
};
