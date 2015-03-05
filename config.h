/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
	{ "Opera",    NULL,       NULL,       1,            False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]      = { "roxterm", NULL };
static const char *snotescmd[]    =  { "snotes",    NULL };
static const char *browsercmd[]   =  { "$BROWSER",  NULL };
static const char *lockcmd[]      =  { "slock",     NULL };
/* media commands */
//static const char *volupcmd[]     =  { "amixer", "set", "Master", "5%+", NULL };
//static const char *voldowncmd[]   =  { "amixer", "set", "Master", "5%-", NULL };
static const char *volupcmd[]     =  { "amixer", "set", "PCH", "5%+", NULL }; // for headset
static const char *voldowncmd[]   =  { "amixer", "set", "PCH", "5%-", NULL }; // for headset
static const char *mpcvolupcmd[]  =  { "mpc", "volume", "+5", NULL };
static const char *mpcvoldowncmd[]=  { "mpc", "volume", "-5", NULL };
static const char *playpausecmd[] =  { "mpc", "toggle", NULL };
//static const char *stopcmd[]      =  { "mpc", "stop", NULL };
static const char *prevcmd[]      =  { "mpc", "prev", NULL };
static const char *nextcmd[]      =  { "mpc", "next", NULL };
/* screen commands */
static const char *invertcmd[]    =  { "xcalib", "-invert", "-alter", NULL };
static const char *screenshotcmd[]=  { "scrot", NULL };
/* net commands */
//static const char *wifiupcmd[] =    { "sudo",  "/etc/init.d/net.wlan0", "start", NULL};
//static const char *wifidowncmd[] =  { "sudo", "/etc/init.d/net.wlan0", "stop", NULL};
//static const char *etherupcmd[] =   { "sudo", "/etc/init.d/net.eth0", "start", NULL};
//static const char *etherdowncmd[] = { "sudo", "/etc/init.d/net.eth0", "stop", NULL};

#include "keepfloatingposition.c"
static Key keys[] = {
	/* modifier             key         function    argument */
	/* Multimedia -- keycodes for my wired apple keyboard */
	{ 0,                    0x1008ff16, spawn,      {.v = prevcmd } },
	{ 0,                    0x1008ff14, spawn,      {.v = playpausecmd } },
	{ 0,                    0x1008ff17, spawn,      {.v = nextcmd } },
	{ 0,                    0x1008ff11, spawn,      {.v = voldowncmd } },
	{ 0,                    0x1008ff13, spawn,      {.v = volupcmd } },
	{ ShiftMask,            0x1008ff11, spawn,      {.v = mpcvoldowncmd } },
	{ ShiftMask,            0x1008ff13, spawn,      {.v = mpcvolupcmd } },
	{ 0,                    0x1008ff2c, spawn,      {.v = screenshotcmd } },

	/* Launchers & misc */
	{ MODKEY,               XK_i,       spawn,      {.v = invertcmd } },
	{ MODKEY,               XK_p,       spawn,      {.v = dmenucmd} }, 
	{ MODKEY,               XK_r,       spawn,      {.v = dmenucmd} }, 
	{ MODKEY,               XK_n,       spawn,      {.v = snotescmd} }, 
	{ MODKEY,               XK_Return,  spawn,      {.v = termcmd } },
	{ MODKEY,               XK_o,       spawn,      {.v = browsercmd } },
	{ MODKEY,               XK_Escape,  spawn,      {.v = lockcmd } },
	//{ MODKEY,               XK_u,       spawn,      {.v = wifiupcmd } },
	//{ MODKEY,               XK_d,       spawn,      {.v = wifidowncmd } },
	//{ MODKEY|ShiftMask,     XK_u,       spawn,      {.v = etherupcmd } },
	//{ MODKEY|ShiftMask,     XK_d,       spawn,      {.v = etherdowncmd } },

	/* Layout */
	{ MODKEY,               XK_h,       setmfact,   {.f = -0.05} },
	{ MODKEY,               XK_l,       setmfact,   {.f = +0.05} },
	{ MODKEY,               XK_d,       setlayout,  {.v = &layouts[0]} },
	{ MODKEY,               XK_t,       setlayout,  {.v = &layouts[1]} },
	{ MODKEY,               XK_m,       setlayout,  {.v = &layouts[2]} },
	//{ MODKEY,               XK_s,       setlayout,  {.v = &layouts[3]} },
	//{ MODKEY,               XK_f,       setlayout,  {.v = &layouts[4]} },

	/* Stack */
	{ MODKEY,               XK_Tab,     focusstack, {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_Tab,     focusstack, {.i = +1 } },
	{ MODKEY,               XK_j,       focusstack, {.i = -1 } },
	{ MODKEY,               XK_k,       focusstack, {.i = +1 } },
	{ MODKEY|ControlMask,   XK_j,       incnmaster, {.i = -1 } },
	{ MODKEY|ControlMask,   XK_k,       incnmaster, {.i = +1 } },
	{ MODKEY,               XK_z,       zoom,       {0} },
	{ MODKEY,               XK_space,   zoom,       {0} },

	/* Monitors */
	{ MODKEY,               XK_comma,   focusmon,   {.i = -1 } },
	{ MODKEY,               XK_period,  focusmon,   {.i = +1 } },
	// TODO: with single taglist, this just crashes.
	// Could I look up the tag on the other monitor & move to that tag instead?
	//{ MODKEY|ShiftMask,     XK_comma,   tagmon,     {.i = -1 } },
	//{ MODKEY|ShiftMask,     XK_period,  tagmon,     {.i = +1 } }, //

	/* Commands */
	{ MODKEY|ShiftMask,     XK_c,       killclient, {0} },
	{ MODKEY|ShiftMask,     XK_q,       quit,       {0} },
	{ MODKEY|ControlMask,   XK_r,       quit,       {0} },

	/* Tags */
	{ MODKEY,               XK_b,       togglebar,  {0} },
	{ MODKEY,               XK_0,       view,       {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,       tag,        {.ui = ~0 } },
	TAGKEYS(                XK_1,       0)
	TAGKEYS(                XK_2,       1)
	TAGKEYS(                XK_3,       2)
	TAGKEYS(                XK_4,       3)
	TAGKEYS(                XK_5,       4)
	TAGKEYS(                XK_6,       5)
	TAGKEYS(                XK_7,       6)
	TAGKEYS(                XK_8,       7)
	TAGKEYS(                XK_9,       8)

};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = playpausecmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = mpcvolupcmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = mpcvoldowncmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

