/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Regular Nerd Font Complete:size=12" };
static const char dmenufont[]       = "Hack Regular Nerd Font Complete:size=12";
static const char col_gray1[]       = "#1E1E1E";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* tagging */
static const char *tags[] = { " 1 ", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "./patches/vanitygaps.c"

/* #include "./patches/fibonacci.c" */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

#include "./patches/shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} }, 
	{ MODKEY,			            XK_w,      spawn,		   SHCMD("$BROWSER") },
	{ MODKEY,			            XK_r,      spawn,		   SHCMD("kitty -e ranger") },
	{ MODKEY,			            XK_y,      spawn,		   SHCMD("flameshot gui -p ~/Pictures/screenshots") },
	{ MODKEY|ShiftMask,			    XK_y,      spawn,		   SHCMD("flameshot full -p ~/Pictures/screenshots") },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_p,      shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} }, // float
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monocle
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[4]} }, // dwindle
+	{ MODKEY,                       XK_g,      togglegaps,     {0} },
+	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
	/* { MODKEY|ShiftMask,			    XK_t,      spawn,		   SHCMD("kitty -e ytop") }, */
    /* { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} }, // spiral */
	/* { MODKEY,                       XK_semicolon,      shiftview,      {.i = 1 } }, */
	/* { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, */
	/* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
	/* { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* # Pulse Audio controls */
/* bindsym XF86AudioRaiseVolume exec --no-startup-id pactl set-sink-volume @DEFAULT_SINK@ +10% #increase sound volume */
/* bindsym XF86AudioLowerVolume exec --no-startup-id pactl set-sink-volume @DEFAULT_SINK@ -10% #decrease sound volume */
/* bindsym XF86AudioMute        exec --no-startup-id pactl set-sink-mute @DEFAULT_SINK@ toggle # mute sound */

/* bindsym $mod+F1		        restart */
/* bindsym $mod+F2		        exec --no-startup-id screenkey -s small --scr 1 -p fixed -g 600x100+2573+1330 --opacity .9 --font-color white */
/* bindsym $mod+F3	          exec --no-startup-id killall screenkey */
/* bindsym $mod+F12	        exec $term -e nmtui */

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

