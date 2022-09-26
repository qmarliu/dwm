/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int overviewgappi      = 24;        /* overview时 窗口与边缘 缝隙大小 */
static const int overviewgappo      = 60;        /* overview时 窗口与窗口 缝隙大小 */
static const char *fonts[]          = { "WenQuanYi Zen Hei Mono:size=10" };
static const char dmenufont[]       = "WenQuanYi Zen Hei Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*                    fg         bg         border   */
	[SchemeNorm]      = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]       = { col_gray4, "#775544", "#DDA0DD"  },
	[SchemeHid]       = { col_cyan,  col_gray1, col_gray2  },
	[SchemeText]      = { col_gray3, col_gray1, col_gray2  },
	[SchemeUnderline] = { "#7799AA", "#7799AA", "#7799AA" },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeHid]  = { OPAQUE, baralpha, borderalpha },
	[SchemeText]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖","", "ﱘ", "", "", "", "", "" };

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

static const char *overviewtag = "OVERVIEW";
static const Layout overviewlayout = { "",  overview };

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      magicgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG,CMD) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG, .v = CMD} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_m,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ControlMask,           XK_k,      focusstackhid,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_r,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ControlMask,           XK_Tab,    toggleviewtab,  {0} },
  { MODKEY|ShiftMask,             XK_Tab,    tagtab,         {0} },
  { MODKEY|ControlMask|ShiftMask, XK_Tab,    toggletagtab,   {0} },
	{ MODKEY,                       XK_n,      viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_n,      viewtoleft,     {0} },
	{ MODKEY,                       XK_grave,  toggleoverview, {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_a,      setlayout,      {0} },
	{ MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_o,      hideother,      {0} },
	{ MODKEY|ShiftMask,             XK_o,      showother,      {0} },
	{ MODKEY,                       XK_s,      hide,           {0} },
	{ MODKEY|ShiftMask,             XK_s,      show,           {0} },
	{ MODKEY,                       XK_Up,     movewin,        {.ui = UP} },              /* super ctrl up      |  移动窗口 */
	{ MODKEY,                       XK_Down,   movewin,        {.ui = DOWN} },            /* super ctrl down    |  移动窗口 */
	{ MODKEY,                       XK_Left,   movewin,        {.ui = LEFT} },            /* super ctrl left    |  移动窗口 */
	{ MODKEY,                       XK_Right,  movewin,        {.ui = RIGHT} },           /* super ctrl right   |  移动窗口 */
	{ MODKEY|ShiftMask,             XK_Up,     resizewin,      {.ui = V_REDUCE} },        /* super ctrl up      |  调整窗口 */
	{ MODKEY|ShiftMask,             XK_Down,   resizewin,      {.ui = V_EXPAND} },        /* super ctrl down    |  调整窗口 */
	{ MODKEY|ShiftMask,             XK_Left,   resizewin,      {.ui = H_REDUCE} },        /* super ctrl left    |  调整窗口 */
	{ MODKEY|ShiftMask,             XK_Right,  resizewin,      {.ui = H_EXPAND} },        /* super ctrl right   |  调整窗口 */
	TAGKEYS(XK_1,      0,           0)
	TAGKEYS(XK_2,      1,           0)
	TAGKEYS(XK_3,      2,           0)
	TAGKEYS(XK_4,      3,           0)
	TAGKEYS(XK_5,      4,           0)
	TAGKEYS(XK_6,      5,           0)
	TAGKEYS(XK_7,      6,           0)
	TAGKEYS(XK_8,      7,           0)
	TAGKEYS(XK_9,      8,           0)
	TAGKEYS(XK_c,      9,           "~/scripts/app-starter.sh chrome")
	TAGKEYS(XK_y,      10,          "~/scripts/app-starter.sh music")
	TAGKEYS(XK_d,      11,          "~/scripts/app-starter.sh dingtalk")
	TAGKEYS(XK_x,      12,          "~/scripts/app-starter.sh wechat")
	TAGKEYS(XK_q,      13,          "~/scripts/app-starter.sh qq")
	TAGKEYS(XK_i,      14,          "~/scripts/app-starter.sh dbeaver")
	TAGKEYS(XK_z,      15,          "~/scripts/app-starter.sh keepassxc")
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ MODKEY,                       XK_Return, spawn,          SHCMD("~/scripts/app-starter.sh alacritty") },
	{ MODKEY|ControlMask,           XK_n,      spawn,          SHCMD("~/scripts/app-starter.sh st") },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("~/scripts/app-starter.sh killw") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("~/scripts/app-starter.sh filemanager") },
	{ MODKEY,                       XK_space,  spawn,          SHCMD("~/scripts/app-starter.sh rofi_drun") },
	{ MODKEY|ShiftMask,             XK_space,  spawn,          SHCMD("~/scripts/app-starter.sh rofi_run") },
	{ MODKEY|ControlMask,           XK_space,  spawn,          SHCMD("~/scripts/app-starter.sh rofi_menu") },
	{ MODKEY|ControlMask,           XK_l,      spawn,          SHCMD("~/scripts/app-starter.sh xlock") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD("~/scripts/app-starter.sh chrome") },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("~/scripts/app-starter.sh flameshot") },
	{ MODKEY|ControlMask|ShiftMask, XK_a,      spawn,          SHCMD("~/scripts/app-starter.sh open_last_screenshot") },
	{ MODKEY,                       XK_v,      spawn,          SHCMD("~/scripts/app-starter.sh set_vol up &") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("~/scripts/app-starter.sh set_vol down &") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("~/scripts/app-starter.sh change_wallpaper") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("~/scripts/app-starter.sh alacritty") },
	{ ClkClientWin,         ControlMask,    Button3,        toggleoverview, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkRootWin,           MODKEY,         Button4,        toggleoverview, {0} },
	{ ClkRootWin,           MODKEY,         Button5,        toggleoverview, {0} },
	{ ClkClientWin,         MODKEY,         Button4,        toggleoverview, {0} },
	{ ClkClientWin,         MODKEY,         Button5,        toggleoverview, {0} },
	{ ClkRootWin,           0,              Button6,        viewtoright,    {0} },
	{ ClkRootWin,           0,              Button7,        viewtoleft,     {0} },
	{ ClkClientWin,         0,              Button6,        viewtoright,    {0} },
	{ ClkClientWin,         0,              Button7,        viewtoleft,     {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
