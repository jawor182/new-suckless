#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER " "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)                     \
    X("", "sb-mpd",         1, 3)     \
    X("", "sb-date",       10, 10)    \
    X("", "sb-volume",      1, 9)     \
    X("", "sb-cpu",        30, 6)     \
    X("", "sb-memory",     30, 5)     \
    X("", "sb-battery",     5, 8)     \
    X("", "sb-internet",    5, 7)     \

#endif  // CONFIG_H
