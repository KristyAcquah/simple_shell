#ifndef MAIN_H
#define MAIN_H

#define MAX_INSTRUCTION_ LENGTH(1024)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>
#include <fcntl.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>

void prompt(void);

char *read_line(void);

char **parse_line(char *line);

#endif
