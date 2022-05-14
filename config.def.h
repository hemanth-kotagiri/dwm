// ███████   ██       ██ ████     ████
//░██░░░░██ ░██      ░██░██░██   ██░██
//░██    ░██░██   █  ░██░██░░██ ██ ░██
//░██    ░██░██  ███ ░██░██ ░░███  ░██
//░██    ░██░██ ██░██░██░██  ░░█   ░██
//░██    ██ ░████ ░░████░██   ░    ░██
//░███████  ░██░   ░░░██░██        ░██
//░░░░░░░   ░░       ░░ ░░         ░░ 


/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;        /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* vert outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* horiz outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Jetbrains Mono:size=11", "JoyPixels:pixelsize=15:antialias=true:autohint=true"};
static const char dmenufont[]       = "Jetbrains Mono:size=11";
//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
//static const char col_urgborder[]   = "#ff0000";
//static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	//[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	//[SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder  },
//};
#include "/home/hemanth/.cache/wal/colors-wal-dwm.h"

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "floating",NULL,     NULL,           0,         1,          1,           0,        -1 },
	{ "st-256color", NULL, NULL,           0,         0,          1,           0,        -1 },
	{ "ranger",  NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
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
	{ "H[]",      deck },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon , "-fn", dmenufont};
static const char *termcmd[]  = { "st", NULL };
static const char *brave[]  = { "brave", NULL };
static const char *emoji_launcher[]  = { "rofi", "-show", "emoji", NULL };
static const char *rofi_window[]  = { "rofi", "-show", "window", NULL };
static const char *naut[]  = { "nautilus", NULL };
static const char *shutdown_menu[]  = { "shutdown_menu", NULL };
static const char *whatsapp[]  = { "whatsapp-nativefier", NULL };
static const char *notion[]  = { "notion-app-enhanced", NULL };
static const char *signal_app[]  = { "signal-desktop", NULL };
static const char *auto_launch_script[] = {"auto", NULL};

/* Volume control */
static const char *upvol[]   = { "amixer", "-D", "pulse",  "sset","Master", "5%+",     NULL };
static const char *downvol[] = { "amixer", "-D", "pulse",  "sset","Master", "5%-",     NULL };
static const char *mutevol[] = { "amixer", "-D", "pulse",  "sset","Master", "1+", "toggle",     NULL };
static const char *pause_audio[] = { "playerctl", "pause", NULL };
static const char *play_audio[] = { "playerctl", "play", NULL };
static const char *audio_toggle[] = {"playerctl", "play-pause", NULL};

// tdrop
static const char *books[] = { "tdrop", "-am", "-w", "70%", "-h", "70%", "-y", "15%", "-x", "15%", "-n", "0", "st", "-c", "floating", "-e", "ranger", "/media/data/Education/Books", NULL };
static const char *btech[] = { "tdrop", "-am", "-w", "70%", "-h", "70%", "-y", "15%", "-x", "15%", "-n", "1", "st", "-c", "floating", "-e", "ranger", "/media/volume/B.Tech-Docs", NULL};
static const char *downl[] = { "tdrop", "-am", "-w", "70%", "-h", "70%", "-y", "15%", "-x", "15%", "-n", "2", "st", "-c", "floating", "-e", "ranger", "/home/hemanth/Downloads/", NULL};
static const char *docs[] = { "tdrop", "-am", "-w", "70%", "-h", "70%", "-y", "15%", "-x", "15%", "-n", "3", "st", "-c", "floating", "-e", "ranger", "/home/hemanth/Documents/", NULL};

//tdrop -am -w 70% -h 70% -y 15% -x 15% -n 0 st -c "floating" -e ranger/media/volume/B.Tech\ Docs  


#include "patches/shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	// Personal
	{ MODKEY,                       XK_e,      spawn,          {.v = emoji_launcher } },
  // scratchpads with tdrop
	{ Mod1Mask,                     XK_b,      spawn,          {.v = books } },
	{ Mod1Mask|ShiftMask,           XK_b,      spawn,          {.v = btech } },
	{ Mod1Mask,                     XK_d,      spawn,          {.v = downl } },
	{ Mod1Mask|ShiftMask,           XK_d,      spawn,          {.v = docs } },
  
	{ ControlMask|Mod1Mask,         XK_Delete, spawn,          {.v = shutdown_menu } },
  
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = naut } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = whatsapp } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = signal_app } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = notion } },
	{ Mod1Mask|MODKEY,              XK_a,      spawn,          {.v = auto_launch_script } },
	{ MODKEY,                       XK_w,      spawn,          {.v = rofi_window } },
	// DEFAULTS
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = -1 }},
	{ MODKEY,                       XK_p,      shiftview,      {.i = +1 }},
	{ MODKEY,                       XK_b,      spawn,          {.v = brave }},
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ Mod1Mask|MODKEY,              XK_u,      incrgaps,       {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_i,      incrigaps,      {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_o,      incrogaps,      {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_6,      incrihgaps,     {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_7,      incrivgaps,     {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_8,      incrohgaps,     {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_9,      incrovgaps,     {.i = +1 } },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ Mod1Mask|MODKEY,              XK_0,      togglegaps,     {0} },
	{ Mod1Mask|MODKEY|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	//{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      layoutscroll,   {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      layoutscroll,   {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	// Volume Control Keys
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute,        spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioPause,       spawn, {.v = pause_audio   } },
	{ 0,                       XF86XK_AudioPlay,        spawn, {.v = play_audio   } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	// Volume Control
	{ ClkLtSymbol,          0,              Button4,        spawn,          {.v = upvol} },
	{ ClkLtSymbol,          0,              Button1,        spawn,      {.v = audio_toggle} },
	{ ClkLtSymbol,          0,              Button5,        spawn,          {.v = downvol} },

	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,     {.i=-1} },
	{ ClkTagBar,            0,              Button5,        shiftview,     {.i=+1} },
};
