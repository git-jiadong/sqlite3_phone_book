#ifndef __HEAD_H
#define __HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <linux/input.h>
#include "jpeg.h"
#include "sqlite3.h"


sqlite3 *init_sql(void);
void create_table(sqlite3 *db);
int sqlite_insert(sqlite3 *db);
int sqlite_update(sqlite3 *db);
int sqlite_show(sqlite3 *db);
int sqlite_delete(sqlite3 *db);
void init_show(void);


#endif
