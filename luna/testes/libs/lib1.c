#include "lua.h"
#include "lauxlib.h"

static int id (luna_State *L) {
  return luna_gettop(L);
}


static const struct lunaL_Reg funcs[] = {
  {"id", id},
  {NULL, NULL}
};


/* function used by lib11.c */
LUAMOD_API int lib1_export (luna_State *L) {
  luna_pushstring(L, "exported");
  return 1;
}


LUAMOD_API int onefunction (luna_State *L) {
  lunaL_checkversion(L);
  luna_settop(L, 2);
  luna_pushvalue(L, 1);
  return 2;
}


LUAMOD_API int anotherfunc (luna_State *L) {
  lunaL_checkversion(L);
  luna_pushfstring(L, "%d%%%d\n", (int)luna_tointeger(L, 1),
                                 (int)luna_tointeger(L, 2));
  return 1;
} 


LUAMOD_API int luaopen_lib1_sub (luna_State *L) {
  luna_setglobal(L, "y");  /* 2nd arg: extra value (file name) */
  luna_setglobal(L, "x");  /* 1st arg: module name */
  lunaL_newlib(L, funcs);
  return 1;
}

