#include "lua.h"


int luaopen_lib2 (luna_State *L);

LUAMOD_API int luaopen_lib21 (luna_State *L) {
  return luaopen_lib2(L);
}


