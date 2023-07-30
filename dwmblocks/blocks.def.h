//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/						/*Update Interval*/	/*Update Signal*/
	{ "",   "~/.config/dwm/dwmblocks/scripts/volume.sh",	0,      10},
	{ "", 	"~/.config/dwm/dwmblocks/scripts/updates.sh",	120,    40},
	{ "",    "~/.config/dwm/dwmblocks/scripts/weather.sh",	12,     90},
	{ "💻 ", "~/.config/dwm/dwmblocks/scripts/cpu.sh",		3,      0 },
	{ "🔥 ", "~/.config/dwm/dwmblocks/scripts/cpuh.sh",		5,      0 },
	{ "🧠 ", "~/.config/dwm/dwmblocks/scripts/ram.sh",		5,      0 },
	{ "", "~/.config/dwm/dwmblocks/scripts/date.sh",		5,		20 },
	{ "", 	 "~/.config/dwm/dwmblocks/scripts/time.sh",	    1,		30 },
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
/* static char delim[] = " ┊ "; */
static char delim[] = " | ";
static unsigned int delimLen = 5;
