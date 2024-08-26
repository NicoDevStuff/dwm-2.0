/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */

static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { 
	"JetBrainsMono:size=12", 
	"Noto Color Emoji:style=Regular:size=12:antialias=true",
	"FontAwesome:size=12:antialias=true"
};
/* static const char *fonts[]          = { */ 
/* 	"JetBrainsMono:size=10", */ 
/* 	"Noto Color Emoji:style=Regular:size=10:antialias=true", */
/* 	"FontAwesome:size=10:antialias=true" */
/* }; */

static const char dmenufont[]       = "JetBrains Mono:size=12";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#3c3836";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#83a598";
static const char col_blue[]        = "#2588BE";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_cyan  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,      SHCMD("kitty") },
	{ MODKEY,                       XK_m,      spawn,      SHCMD("emacs") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,      SHCMD("rofi -show drun") },
	{ MODKEY,                       XK_Tab,    spawn,      SHCMD("rofi -show") },
	{ MODKEY,                       XK_c,      spawn,      SHCMD("rofi -show calc -modi calc -no-show-match -no-sort") },
	{ MODKEY,                       XK_e,      spawn,      SHCMD("rofimoji") },
	{ MODKEY,             			XK_s,      spawn,      SHCMD("signal-desktop") },
	{ MODKEY,                       XK_b,      spawn,      SHCMD("brave") },
	{ MODKEY|ShiftMask,             XK_e,      spawn,      SHCMD("thunderbird") },
	{ MODKEY,             			XK_f,      spawn,      SHCMD("pcmanfm") },

	{ MODKEY,    					XK_w,      setlayout,  {.v = &layouts[0]} },
	{ MODKEY,    					XK_a,      setlayout,  {.v = &layouts[1]} },

	{ MODKEY|ControlMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ControlMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ControlMask,             XK_o,      setcfact,       {.f =  0.00} },
	
	{ MODKEY, 						XK_m,  	   spawn,      SHCMD("killall dwmblocks && dwmblocks") },
	{ MODKEY, 						XK_w,  	   spawn,      SHCMD("kill - 124 $(pidof dwmblocks)") },

	{ 0, 			   XF86XK_AudioPrev,  	   spawn,      SHCMD("playerctl previous") },
	{ 0, 			   XF86XK_AudioNext,  	   spawn,      SHCMD("playerctl next") },
	{ 0, 			   XF86XK_AudioPlay,  	   spawn,      SHCMD("playerctl play-pause") },
	{ 0, 		       XF86XK_AudioLowerVolume,spawn,      SHCMD("~/.config/dwm/scripts/volume.sh down && kill -44 $(pidof dwmblocks)") },
	{ 0, 		       XF86XK_AudioRaiseVolume,spawn,      SHCMD("~/.config/dwm/scripts/volume.sh up && kill -44 $(pidof dwmblocks)") },
	{ 0, 		       XF86XK_AudioMute       ,spawn,      SHCMD("~/.config/dwm/scripts/volume.sh mute && kill -44 $(pidof dwmblocks)") },
	{ 0, 		       XF86XK_AudioMicMute    ,spawn,      SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, 		       XF86XK_MonBrightnessUp ,spawn,      SHCMD("brightnessctl set +5%") },
	{ 0, 		       XF86XK_MonBrightnessDown,spawn,     SHCMD("brightnessctl set 5%-") },
	{ 0, 		       XK_Print           	  ,spawn, 	   SHCMD("ksnip") },


	{ MODKEY,                       XK_q,      killclient,     {0} },

	{ MODKEY|ShiftMask,             XK_l,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_h,      pushup,         {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglemonocle,  { } },

	{ MODKEY|ShiftMask,    			XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,  	   {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,	   {.f = +0.05} },

	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    view,           {0} },

	{ MODKEY|ShiftMask, 			XK_f,  	   togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask,             XK_x,      quit,		   {0} },
	{ MODKEY|ShiftMask, 			XK_r,      quit,           {1} }, };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("kitty") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

