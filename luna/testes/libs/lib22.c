#include "lua.h"
#include "lauxlib.h"

static int id (luna_State *L) {
  luna_pushboolean(L, 1);
  luna_insert(L, 1);
  return luna_gettop(L);
}


static const struct lunaL_Reg funcs[] = {
  {"id", id},
  {NULL, NULL}
};


LUAMOD_API int luaopen_lib2 (luna_State *L) {
  luna_settop(L, 2);
  luna_setglobal(L, "y");  /* y gets 2nd parameter */
  luna_setglobal(L, "x");  /* x gets 1st parameter */
  lunaL_newlib(L, funcs);
  return 1;
}


