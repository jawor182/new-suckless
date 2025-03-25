//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/*{"Mem:", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	30,		0},*/

	/*{"", "date '+%b %d (%a) %I:%M%p'",					5,		0},*/
    { "",       "sb-date",                                  60,      10},
    { "",       "sb-volume",                                1,       11},
    { "",       "sb-battery",                               60,      12},
    { "",       "sb-internet",                              60,      13},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ";
static unsigned int delimLen = 5;
