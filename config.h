/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL  "st"
#define TERMCLASS "St"
#define BROWSER   "thorium-browser"
#define OBSIDIAN  "obsidian"
#define BITWIG    "bitwig-studio"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 10;       /* horiz inner gap between windows */
static unsigned int gappiv    = 5;       /* vert inner gap between windows */
static unsigned int gappoh    = 2;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 2;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "TerminessNerdFont:size=10:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"  };

static char normbgcolor[]     = "#000000";
static char normbordercolor[] = "#1a1a1a";
static char normfgcolor[]     = "#d0d0d0";

static char selbgcolor[]      = "#000000";
static char selbordercolor[]  = "#4a4a4a";
static char selfgcolor[]      = "#ffffff";

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
/* class      instance      title          tags mask   isfloating  isterminal  noswallow  monitor */
/*{ "Gimp",     NULL,         NULL,           1 << 8,    0,          0,          0,         -1 },*/
{ TERMCLASS,    NULL,         NULL,           0,         0,          1,          0,         -1 },
{ NULL,         NULL,         "Event Tester", 0,         0,          0,          1,         -1 },
{ TERMCLASS,    "floatterm",  NULL,           0,         1,          1,          0,         -1 },
{ TERMCLASS,    "bg",         NULL,           1 << 7,    0,          1,          0,         -1 },
{ TERMCLASS,    "spterm",     NULL,           SPTAG(0),  1,          1,          0,         -1 },
/*{ TERMCLASS,  "floatyeay",  NULL,           0,         1,          1,          0,         -1 },*/
{ NULL,         NULL,         "pulsemixer",   0,         1,          1,          0,         -1 },
{ NULL,         NULL,         "bluetui",      0,         1,          0,          0,         -1 },
{ NULL,         NULL,         "refresh",      0,         1,          1,          0,         -1 },
{ NULL,         NULL,         "nmtui",        0,         1,          1,          1,         -1 },
{ NULL,         NULL,         "synth",        0,         1,          1,          1,         -1 },
{ NULL,         NULL,         "rmpc",         0,         1,          1,          1,         -1 },
{ NULL,         NULL,         "wiki-tui",     0,         1,          1,          1,         -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ ">M>",	centeredfloatingmaster },       /* Same but master floats */
	{ "[@]",	spiral },               /* Fibonacci spiral */

	{ "[M]",	monocle },              /* All windows on top of eachother */
	{ "[\\]",	dwindle },              /* Decreasing in size right and leftward */

	{ "[]=",	tile },	                /* Default: Master on left, slaves on right */
	{ "[D]",	deck },	                /* Master on left, slaves in monocle-like mode on right */

	{ "|M|",	centeredmaster },       /* Master in middle, slaves on sides */
	{ "TTT",	bstack },               /* Master on top, slaves on bottom */

	{ "><>",	NULL },	                /* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		        STRING,	&normbordercolor },
		{ "color8",		        STRING,	&selbordercolor },
		{ "color0",		        STRING,	&normbgcolor },
		{ "color4",		        STRING,	&normfgcolor },
		{ "color0",		        STRING,	&selfgcolor },
		{ "color4",		        STRING,	&selbgcolor },
		{ "borderpx",		      INTEGER, &borderpx },
		{ "snap",		          INTEGER, &snap },
		{ "showbar",		      INTEGER, &showbar },
		{ "topbar",		        INTEGER, &topbar },
		{ "nmaster",		      INTEGER, &nmaster },
		{ "resizehints",      INTEGER, &resizehints },
		{ "mfact",		        FLOAT,	&mfact },
		{ "gappih",		        INTEGER, &gappih },
		{ "gappiv",		        INTEGER, &gappiv },
		{ "gappoh",		        INTEGER, &gappoh },
		{ "gappov",		        INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",	     	INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("") }, */
	{ MODKEY,			XK_at,	spawn,	{.v = (const char*[]){ "dmenuunicode", NULL } } },
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,		          	XK_BackSpace,	spawn,		{.v = (const char*[]){ "sysact", NULL } } },
  { MODKEY|ShiftMask,			XK_BackSpace,	spawn,		{.v = (const char*[]){ "slock", NULL } } },
	{ MODKEY,			XK_Tab,		view,		{0} },
	/* { MODKEY|ShiftMask,		XK_Tab,		spawn,		SHCMD("") }, */
	{ MODKEY,			        XK_q,		killclient,	{0} },
	{ MODKEY|ShiftMask,		XK_q,		spawn,		SHCMD("sudo systemctl suspend") },
	{ MODKEY|ShiftMask, 	XK_w,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,		          XK_w,		spawn,		{.v = (const char*[]){ TERMINAL, "-f", "monospace:size=16", "-g", "80x24", "-e", "wiki-tui", NULL }} },
 	{ MODKEY|ShiftMask,		XK_n,		spawn,		{.v = (const char*[]){ TERMINAL, "-f", "monospace:size=14.5", "-g", "80x24", "-e", "nmtui", NULL }} },
	{ MODKEY,			        XK_e,		spawn,		{.v = (const char*[]){ OBSIDIAN, NULL } } },
	{ MODKEY|ShiftMask,		XK_e,		spawn,		{.v = (const char*[]){ TERMINAL, "-f", "monospace:size=16", "-g", "80x24", "-e", "calcurse", NULL }} },
	{ MODKEY,		        	XK_r,		spawn,		{.v = (const char*[]){"yeay"} } },
	{ MODKEY|ShiftMask,		XK_r,		spawn,		{.v = (const char*[]){ TERMINAL, "-f", "monospace:size=13", "-e", "htop", NULL }} },
	{ MODKEY,	        		XK_t,                  setlayout,              {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_t,                  setlayout,              {.v = &layouts[1]} },
	{ MODKEY,			        XK_y,                  setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_y,                  setlayout,              {.v = &layouts[3]} },
	{ MODKEY,		         	XK_u,                  setlayout,              {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,		XK_u,                  setlayout,              {.v = &layouts[5]} },
	{ MODKEY,		        	XK_i,                  setlayout,              {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,		XK_i,                  setlayout,              {.v = &layouts[7]} },
	{ MODKEY,	        		XK_o,		               incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,	                 incnmaster,             {.i = -1 } },
	{ MODKEY,			        XK_p,			             spawn,		               {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ MODKEY|ShiftMask,		XK_p,	                 spawn,		               SHCMD("mpc pause; pauseallmpv") },	{ MODKEY,			XK_bracketleft,		spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ MODKEY|ShiftMask,		XK_bracketleft,		     spawn,		               {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
	{ MODKEY,			        XK_bracketright,	     spawn,		               {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ MODKEY|ShiftMask,		XK_bracketright,	     spawn,		               {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
	{ MODKEY,	        		XK_backslash,		       view,	                 {0} },
	/* { MODKEY|ShiftMask,		XK_backslash,		   spawn,		SHCMD("") }, */

	{ MODKEY,			          XK_a,	               togglebar,	             {0} },
  { MODKEY|ShiftMask,		  XK_a,                togglegaps,	           {0} },
	{ MODKEY,	        		  XK_s,		             togglesticky,	         {0} },
	/* { MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("") }, */
	{ MODKEY,	        		  XK_d,	    	         spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,		  XK_d,		             spawn,		               {.v = (const char*[]){ "passmenu", NULL } } },
	{ MODKEY,			          XK_f,		             togglefullscr,	         {0} },
	{ MODKEY|ShiftMask,		  XK_f,		             setlayout,	             {.v = &layouts[8]} },
	{ MODKEY,         		  XK_g,		             shifttag, 	             { .i = -1 } },
 	{ MODKEY,		          	XK_semicolon,	       shifttag, 	             { .i = +1 } },
	{ MODKEY,	          		XK_h,	       	       setmfact, 	             {.f = -0.05} },
	{ MODKEY,			          XK_l,		             setmfact, 	             {.f = +0.05} },
  { MODKEY|ShiftMask,			XK_h,	             	 shiftview,	             { .i = -1 } },
  { MODKEY|ShiftMask,			XK_l,		             shiftview,	             { .i = +1 } },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,		          	XK_Return,	         spawn,	               	 {.v = termcmd } },
	{ MODKEY|ShiftMask,	  	XK_Return,	         togglescratch,	         {.ui = 0} },

	{ MODKEY,			          XK_z,		             incrgaps,	             {.i = +3 } },
	/* { MODKEY|ShiftMask,		XK_z,		spawn,		SHCMD("") }, */
	{ MODKEY,			          XK_x,		             incrgaps,	             {.i = -3 } },
	/* { MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("") }, */
	{ MODKEY,	        		  XK_c,		             spawn,               	 {.v = (const char*[]){ "ex-macchina", NULL } } },
	{ MODKEY|ShiftMask,		  XK_c,		             spawn,		               {.v = (const char*[]){ TERMINAL, "-f", "monospace:size=13", "-g", "80x24", "-e", "synth", NULL }} },
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,		            XK_b,	               spawn,		               SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY|ShiftMask,		  XK_b,		             spawn,		               {.v = (const char*[]){ BITWIG, NULL } } },
	{ MODKEY,               XK_n,                spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "sh", "-c", "cd /home/tetr/brain.exe/ && nvim", NULL } } },
	{ MODKEY,			          XK_m,		             spawn,		               {.v = (const char*[]){ TERMINAL, "-f", "monospace:size=15.5", "-g", "90x20", "-e", "rmpc", NULL }} },
	{ MODKEY|ShiftMask,		XK_m,	               	 spawn,               	 SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			          XK_comma,            spawn,               	 {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY|ShiftMask,		  XK_comma,         	 spawn,               	 {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	{ MODKEY,			          XK_period,	         spawn,		               {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY|ShiftMask,		  XK_period,	         spawn,		               {.v = (const char*[]){ "mpc", "repeat", NULL } } },

	{ MODKEY|ShiftMask,		  XK_j,	               focusmon,	             {.i = -1 } },
	{ MODKEY|ShiftMask,		  XK_k,	               focusmon,	             {.i = +1 } },
	{ MODKEY|ShiftMask,	  	XK_h,	               tagmon,		             {.i = -1 } },
	{ MODKEY|ShiftMask,		  XK_l,	               tagmon,		             {.i = +1 } },

	{ MODKEY,		          	XK_Page_Up,          shiftview,	             { .i = -1 } },
	{ MODKEY|ShiftMask,	  	XK_Page_Up,	         shifttag,	             { .i = -1 } },
	{ MODKEY,		          	XK_Page_Down,	       shiftview,	             { .i = +1 } },
	{ MODKEY|ShiftMask,	  	XK_Page_Down,	       shifttag,	             { .i = +1 } },
	{ MODKEY,			          XK_Insert,	         spawn,		               SHCMD("xdotool type $(grep -v '^#' ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },

	{ MODKEY,         			XK_F1,		           spawn,             	   {.v = (const char*[]){ "pipekill", NULL } } },
	{ MODKEY,			          XK_F2,		           spawn,		               {.v = (const char*[]){ "volume_down", NULL } } },
	{ MODKEY,			          XK_F3,		           spawn,		               {.v = (const char*[]){ "volume_up", NULL } } },
	{ MODKEY,			          XK_F4,		           spawn,		               {.v = (const char*[]){ TERMINAL, "-f", "monospace:size=14.5", "-g", "75x20", "-e", "pulsemixer", NULL }} },
	{ MODKEY,			          XK_F5,		           spawn,	                 {.v = (const char*[]){ "redshift-toggle", NULL } } },
	{ MODKEY,			          XK_F6,		           spawn,	                 {.v = (const char*[]){ "brain-sync", NULL } } },
	{ MODKEY,			          XK_F7,		           spawn,		               {.v = (const char*[]){ "td-vsftpd", NULL } } },
	{ MODKEY,			          XK_F8,		           spawn,		               {.v = (const char*[]){ "td-internet", NULL } } },
	{ MODKEY,			          XK_F9,		           spawn,		               {.v = (const char*[]){ TERMINAL, "-f", "monospace:size=13", "-g", "80x24", "-e", "refresh", NULL }} },
	{ MODKEY,			          XK_F10,		           spawn,		               SHCMD("remapd") },
	{ MODKEY,			          XK_F11,		           spawn,		               {.v = (const char*[]){ "tlps", NULL } } },
	{ MODKEY,			          XK_F12,		           spawn,		               {.v = (const char*[]){ TERMINAL, "-f", "monospace:size=15.5", "-g", "60x18", "-e", "bluetui", NULL }} },
	{ MODKEY,			          XK_space,	           zoom,		               {0} },
	{ MODKEY|ShiftMask,		  XK_space,	           togglefloating,	       {0} },

	{ 0,	      		    	  XK_Print,	           spawn,		               SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,	    		  XK_Print,	           spawn,		               {.v = (const char*[]){ "maimpick", NULL } } },
	{ MODKEY,		        	  XK_Print,	           spawn,		               {.v = (const char*[]){ "dmenurecord", NULL } } },
	{ MODKEY|ShiftMask,		  XK_Print,	           spawn,		               {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	{ MODKEY,		        	  XK_Delete,	         spawn,		               {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	{ MODKEY,			          XK_Scroll_Lock,	     spawn,		               SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,	                     spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	               spawn,		{.v = (const char*[]){ "volume_upp", NULL } } },
	{ 0, XF86XK_AudioLowerVolume,	               spawn,		{.v = (const char*[]){ "volume_downn", NULL } } },
	{ 0, XF86XK_AudioPrev,	                     spawn,		{.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ 0, XF86XK_AudioNext,		                   spawn,		{.v = (const char*[]){ "mpc",  "next", NULL } } },
	{ 0, XF86XK_AudioPause,	                     spawn,		{.v = (const char*[]){ "mpc", "pause", NULL } } },
	{ 0, XF86XK_AudioPlay,		                   spawn,		{.v = (const char*[]){ "mpc", "play", NULL } } },
	{ 0, XF86XK_AudioStop,		                   spawn,		{.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0, XF86XK_AudioRewind,	                   spawn,		{.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0, XF86XK_AudioForward,	                   spawn,		{.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ 0, XF86XK_AudioMedia,		                   spawn,		{.v = (const char*[]){ TERMINAL, "-e", "rmpc", NULL } } },
	{ 0, XF86XK_AudioMicMute,	                   spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	/* { 0, XF86XK_PowerOff,		                 spawn,		{.v = (const char*[]){ "sysact", NULL } } }, */
	{ 0, XF86XK_Calculator,		                   spawn,		{.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,		                       spawn,		{.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_WWW,		                         spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,		                         spawn,		{.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,	                   spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		                     spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ 0, XF86XK_Mail,		                         spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,	                     spawn,		{.v = (const char*[]){ TERMINAL, "-e",  "yazi",  "/", NULL } } },
	/* { 0, XF86XK_Battery,		                   spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		                     spawn,		{.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,	                 spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,    	               spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,		                   spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,	               spawn,		{.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,               spawn,		{.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		      MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		      MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,        		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,	        	0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,	        	0,		Button2,	togglebar,	{0} },
};
