static unsigned int borderpx  = 4;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    =  8;       /* horiz inner gap between windows */
static unsigned int gappiv    =  8;       /* vert inner gap between windows */
static unsigned int gappoh    =  8;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    =  8;       /* vert outer gap between windows and screen edge */
static unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing = 2;   /* systray spacing */
static int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static unsigned int systrayiconsize = 32; /* systray icon size in px */
static int showsystray        = 1;        /* 0 means no systray */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static char font[]                  = { "JetBrainsMonoNerdFont:size=16:antialias=true"};
static char font2[]                 = { "NotoColorEmoji:size=14:antialias=true"};
static const char *fonts[]          = { font,font2 };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

#define TERMINAL "st"
#define TERMCLASS "St"

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spterm[]    = {TERMINAL,"-n","spterm", NULL };
// const char *spterm[]    = {TERMINAL,"-n","spterm","-e","tmux","new","-s","sptmux","-A", NULL };
const char *spsound[]   = {TERMINAL,"-n","spsound","-e","pulsemixer", NULL };
const char *spbt[]      = {TERMINAL,"-n","spbt","-e","bluetuith", NULL };
const char *spnotes[]   = {TERMINAL,"-n","spnotes","sh","-c","cd ~/dox/notes && $EDITOR", NULL };
const char *spfiles[]   = {TERMINAL,"-n","spfiles","-e","yazi", NULL };
const char *spsysmon[]  = {TERMINAL,"-n","spsysmon","-e","btop", NULL };
static Sp scratchpads[] = {
	/* name         cmd      */
	{"spterm",      spterm   },
	{"spsound",     spsound  },
	{"spbt",        spbt     },
	{"spnotes",     spnotes  },
	{"spfiles",     spfiles  },
	{"spsysmon",    spsysmon },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* class                         instance       title               tags mask  isfloating  isterminal  noswallow  monitor  borderpx */
    { "Gimp",                        NULL,          NULL,               0,         0,          0,          0,         -1,      -1 },
    { "KeePassXC",                   NULL,          NULL,               1 << 8,    0,          0,          0,          0,      -1 }, // workspace 9, monitor 1
    { "discord",                     NULL,          NULL,               1 << 3,    0,          0,          0,          1,      -1 }, // workspace 4, monitor 2
    { "thunderbird-nightly",         NULL,          NULL,               1 << 2,    0,          0,          0,          0,      -1 }, // workspace 4, monitor 1
    { "Spotify",                     NULL,          NULL,               1 << 1,    0,          0,          0,          1,      -1 }, // workspace 2, monitor 2
    { TERMCLASS,                     NULL,          NULL,               0,         0,          1,          0,         -1,      -1 },
    { "floatingTerm",                NULL,          NULL,               0,         1,          1,          1,         -1,      -1 }, 
    { NULL,                          NULL,          "Event Tester",     0,         0,          0,          1,         -1,      -1 }, /* xev */
    { NULL,                          "spterm",      NULL,               SPTAG(0),  1,          1,          1,         -1,      -1 },
    { NULL,                          "spsound",     NULL,               SPTAG(1),  1,          1,          1,         -1,      -1 },
    { NULL,                          "spbt",        NULL,               SPTAG(2),  1,          1,          1,         -1,      -1 },
    { NULL,                          "spnotes",     NULL,               SPTAG(3),  1,          1,          1,         -1,      -1 },
    { NULL,                          "spfiles",     NULL,               SPTAG(4),  1,          1,          1,         -1,      -1 },
    { NULL,                          "spsysmon",    NULL,               SPTAG(5),  1,          1,          1,         -1,      -1 },
};


/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = { "dmenu_run", NULL };
static const char *termcmd[]         = { TERMINAL, NULL };
static const char *browser[]         = { "firefox-nightly", NULL };
static const char *email[]           = { "thunderbird-nightly", NULL };
static const char *music[]           = { "spotify-launcher", NULL };
static const char *notes[]           = { TERMINAL, "-e", "sh", "-c", "cd ~/dox/notes && $EDITOR", NULL};
static const char *fileManager[]     = { TERMINAL, "-e", "yazi", NULL };
static const char *guiFileManager[]  = { "thunar", NULL };
static const char *upvol[]           = { "/usr/bin/wpctl",   "set-volume", "@DEFAULT_AUDIO_SINK@",      "5%+",      NULL };
static const char *downvol[]         = { "/usr/bin/wpctl",   "set-volume", "@DEFAULT_AUDIO_SINK@",      "5%-",      NULL };
static const char *mutevol[]         = { "/usr/bin/wpctl",   "set-mute",   "@DEFAULT_AUDIO_SINK@",      "toggle",   NULL };
static const char *medplaypausecmd[] = { "playerctl", "play-pause", NULL };
static const char *mednextcmd[]      = { "playerctl", "next", NULL };
static const char *medprevcmd[]      = { "playerctl", "previous", NULL };
static const char *passwords[]       = { "keepassxc", NULL };
// static const char *wallpaper[]       = { "waypaper", NULL };
static const char *communicator[]    = { "discord", NULL };
static const char *lockscreen[]      = { "betterlockscreen", "-l", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
        { "normbgcolor",        STRING,  &normbgcolor },
        { "normbordercolor",    STRING,  &normbordercolor },
        { "normfgcolor",        STRING,  &normfgcolor },
        { "selbgcolor",         STRING,  &selbgcolor },
        { "selbordercolor",     STRING,  &selbordercolor },
        { "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Return, togglescratch,  {.ui = 0 } },
    { MODKEY|ControlMask,           XK_s,      togglescratch,  {.ui = 1 } },
    { MODKEY|ControlMask,           XK_b,      togglescratch,  {.ui = 2 } },
    { MODKEY|ControlMask,           XK_n,      togglescratch,  {.ui = 3 } },
    { MODKEY|ControlMask,           XK_f,      togglescratch,  {.ui = 4 } },
    { MODKEY|ControlMask,           XK_m,      togglescratch,  {.ui = 5 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { 0,                            XF86XK_AudioMute,    spawn,          {.v = mutevol } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
    { 0,                            XF86XK_AudioPlay, spawn,   {.v = medplaypausecmd } },
    { 0,                            XF86XK_AudioNext, spawn,   {.v = mednextcmd } },
    { 0,                            XF86XK_AudioPrev, spawn,   {.v = medprevcmd } },
    { MODKEY,                       XK_Escape, spawn,          {.v = lockscreen } },
    { MODKEY|ShiftMask,             XK_Escape, spawn,          SHCMD("powermenu")},
    { MODKEY,                       XK_w,      spawn,          {.v = browser } },
    { MODKEY,                       XK_e,      spawn,          {.v = email } },
    { MODKEY,                       XK_m,      spawn,          {.v = music } },
    { MODKEY,                       XK_n,      spawn,          {.v = notes } },
    { MODKEY,                       XK_f,      spawn,          {.v = fileManager } },
    { MODKEY,                       XK_c,      spawn,          {.v = communicator } },
    { MODKEY|Mod1Mask,              XK_f,      spawn,          {.v = guiFileManager } },
    { MODKEY,                       XK_p,      spawn,          {.v = passwords } },
    { MODKEY|Mod1Mask,              XK_p,      spawn,          SHCMD("colorpicker") },
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("find $HOME/walls -type f -iname '*.png' | shuf | nsxiv -t -")},
    { MODKEY|ControlMask,           XK_w,      spawn,          SHCMD("wallpaper random") },
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("screenshot") },
    { 0,                            XK_Print,  spawn,          SHCMD("screenshot") },
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

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[13]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

