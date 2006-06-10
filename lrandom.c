/*
* lrandom.c
* random interface for Lua 5.0
* Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br>
* 09 Jun 2006 21:09:17
* This code is hereby placed in the public domain.
*/

#include <math.h>
#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"

#define MYNAME		"random"
#define MYVERSION	MYNAME " library for " LUA_VERSION " / Jun 2006"
#define MYTYPE		MYNAME " handle"

#define SEED		2004UL
#include "random.c"

static MT *Pget(lua_State *L, int i)
{
 if (luaL_checkudata(L,i,MYTYPE)==NULL) luaL_typerror(L,i,MYTYPE);
 return lua_touserdata(L,i);
}

static MT *Pnew(lua_State *L)
{
 MT *c=lua_newuserdata(L,sizeof(MT));
 luaL_getmetatable(L,MYTYPE);
 lua_setmetatable(L,-2);
 return c;
}

static int Lnew(lua_State *L)			/** new([seed]) */
{
 MT *c=Pnew(L);
 init_genrand(c,luaL_optlong(L,1,SEED));
 return 1;
}

static int Lclone(lua_State *L)			/** clone(c) */
{
 MT *c=Pget(L,1);
 MT *d=Pnew(L);
 *d=*c;
 return 1;
}

static int Lseed(lua_State *L)			/** seed(c,[seed]) */
{
 MT *c=Pget(L,1);
 init_genrand(c,luaL_optlong(L,2,SEED));
 return 0;
}

static int Lvalue(lua_State *L)			/** value(c) */
{
 MT *c=Pget(L,1);
 lua_pushnumber(L,genrand_real1(c));
 return 1;
}

static int Lvaluei(lua_State *L)		/** valuei(c,a,[b]) */
{
 MT *c=Pget(L,1);
 int a,b;
 if (lua_gettop(L)==2)
 {
  a=1;
  b=luaL_checkint(L,2);
 }
 else
 {
  a=luaL_checkint(L,2);
  b=luaL_checkint(L,3);
 }
 lua_pushnumber(L,floor(a+genrand_real2(c)*(b-a+1)));
 return 1;
}

static int Lvaluex(lua_State *L)		/** valuex(c) */
{
 MT *c=Pget(L,1);
 lua_pushnumber(L,genrand_res53(c));
 return 1;
}

static int Ltostring(lua_State *L)		/** tostring(c) */
{
 MT *c=Pget(L,1);
 char s[64];
 sprintf(s,"%s %p",MYTYPE,(void*)c);
 lua_pushstring(L,s);
 return 1;
}

static const luaL_reg R[] =
{
	{ "__tostring",	Ltostring	},
	{ "clone",	Lclone		},
	{ "new",	Lnew		},
	{ "seed",	Lseed		},
	{ "tostring",	Ltostring	},
	{ "value",	Lvalue		},
	{ "valuei",	Lvaluei		},
	{ "valuex",	Lvaluex		},
	{ NULL,		NULL		}
};

LUALIB_API int luaopen_random(lua_State *L)
{
 lua_pushliteral(L,MYNAME);
 luaL_newmetatable(L,MYTYPE);
 luaL_openlib(L,NULL,R,0);
 lua_pushliteral(L,"version");			/** version */
 lua_pushliteral(L,MYVERSION);
 lua_settable(L,-3);
 lua_pushliteral(L,"__index");
 lua_pushvalue(L,-2);
 lua_settable(L,-3);
 lua_rawset(L,LUA_GLOBALSINDEX);
 return 1;
}
