{
    "targets": [
        {
            "target_name": "lua",
            "sources": [
                "./lua_bd/lua_interface.c",
                "./lua_bd/module.c",
                "./lua_bd/utils.c",
                "./lib/lua/src/lapi.c",
                "./lib/lua/src/lauxlib.c",
                "./lib/lua/src/lbaselib.c",
                "./lib/lua/src/lcode.c",
                "./lib/lua/src/lcorolib.c",
                "./lib/lua/src/lctype.c",
                "./lib/lua/src/ldblib.c",
                "./lib/lua/src/ldebug.c",
                "./lib/lua/src/ldo.c",
                "./lib/lua/src/ldump.c",
                "./lib/lua/src/lfunc.c",
                "./lib/lua/src/lgc.c",
                "./lib/lua/src/linit.c",
                "./lib/lua/src/liolib.c",
                "./lib/lua/src/llex.c",
                "./lib/lua/src/lmathlib.c",
                "./lib/lua/src/lmem.c",
                "./lib/lua/src/loadlib.c",
                "./lib/lua/src/lobject.c",
                "./lib/lua/src/lopcodes.c",
                "./lib/lua/src/loslib.c",
                "./lib/lua/src/lparser.c",
                "./lib/lua/src/lstate.c",
                "./lib/lua/src/lstring.c",
                "./lib/lua/src/lstrlib.c",
                "./lib/lua/src/ltable.c",
                "./lib/lua/src/ltablib.c",
                "./lib/lua/src/ltm.c",
                "./lib/lua/src/lundump.c",
                "./lib/lua/src/lutf8lib.c",
                "./lib/lua/src/lvm.c",
                "./lib/lua/src/lzio.c"
            ],
            "include_dirs": [
                "./lib/lua/src"
            ],
            "defines": [
                "LUA_COMPAT_5_3",
                "LUA_USE_POSIX",
                "LUA_INT_TYPE=LUA_INT_INT"
            ],
        }
    ]
}
