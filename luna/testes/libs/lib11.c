#include "lua.h"

/* function from lib1.c */
int lib1_export (luna_State *L);

LUAMOD_API int luaopen_lib11 (luna_State *L) {
  return lib1_export(L);
}


