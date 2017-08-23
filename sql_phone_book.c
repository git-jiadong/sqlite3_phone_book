#include "head.h"

sqlite3 *init_sql(void)
{
	sqlite3 *db = NULL;
	if(sqlite3_open("contact.db", &db))
	{
		printf("sqlite_open() failed\n");
		exit(1);
	}

	return db;
}
	
void create_table(sqlite3 *db)
{
	char *sql = "create table if not exists contact\
		     (\
		      name TEXT primary key,\
		      phone TEXT,\
		      bell TEXT,\
		      icon TEXT\
		     );";
	char *errmsg;
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite3_exec() failed\n");
		exit(1);
	}
}

int sqlite_insert(sqlite3 *db)
{
	char name[10];
	char phone[12];
	char bell[100];
	char icon[100];

	printf("input the contact name: ");
	bzero(name, sizeof(name));
	scanf("%s", name);

	printf("input the contact phone: ");
	bzero(phone, sizeof(phone));
	scanf("%s", phone);

	printf("set the contact bell will call: ");
	bzero(bell, sizeof(bell));
	scanf("%s", bell);

	printf("set the contact icon: ");
	bzero(icon, sizeof(icon));
	scanf("%s", icon);

	char insert[256];
	char *errmsg = NULL;
	char **result = NULL;
	int nrow_last, nrow_now, ncolumn;
	bzero(insert, sizeof(insert));
	snprintf(insert, sizeof(insert), 
		"insert into contact values('%s', '%s', '%s', '%s');", 
		name, phone, bell, icon);
	if(sqlite3_get_table(db, "select * from contact;", 
			&result, &nrow_last, &ncolumn, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite_get_talble()  failed\n");
		return 1;
	}
	sqlite3_free_table(result);

	if(sqlite3_exec(db, insert, NULL, NULL, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite_exec() insert failed\n");
		return 1;
	}

	if(sqlite3_get_table(db, "select * from contact;", 
			&result, &nrow_now, &ncolumn, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite_get_talble()  failed\n");
		return 1;
	}
	sqlite3_free_table(result);

	if(nrow_last == nrow_now)
		return 1;

	return 0;
}


int sqlite_update(sqlite3 *db)
{
	int id;
	char field[10];
	bzero(field, sizeof(field));
	char value[100];
	bzero(value, sizeof(value));
	char name[10];
	bzero(name, sizeof(name));
	printf("input will update contact name: ");
	scanf("%s", &name);
	printf("input update field: ");
	scanf("%s", field);
	printf("input update vaule: ");
	scanf("%s", value);

	char cmd[256];
	char *errmsg;
	bzero(cmd, sizeof(cmd));
	snprintf(cmd, sizeof(cmd), 
		"update contact set %s='%s' where name='%s';", field, value, name);
	if(sqlite3_exec(db, cmd, NULL, NULL, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite_exec() insert failed\n");
		return 1;
	}

	int nrow, ncolumn;
	char **result;
	bzero(cmd, sizeof(cmd));
	snprintf(cmd, sizeof(cmd), 
		"select * from contact where name='%s' and %s='%s';", name, field, value);
	if(sqlite3_get_table(db, cmd, &result, &nrow, &ncolumn, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite_get_talble()  failed\n");
		return 1;
	}
	sqlite3_free_table(result);
	
	if(nrow != 1)
		return 1;

	return 0;
}

int sqlite_show(sqlite3 *db)
{
	int nrow, ncolumn;
	char **result = NULL;
	char *errmsg = NULL;
	sqlite3_get_table(db, "select * from contact;", 
			&result, &nrow, &ncolumn, &errmsg);
	
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
	if(nrow == 0)
		return 1;

	int i, j;
	for(i=0; i<nrow+1; i++)
	{
		for(j=0; j<ncolumn; j++)
		{
			printf("%s ", result[j + i * ncolumn]);
		}
		printf("\n");
	}

	sqlite3_free_table(result);

	return 0;
}

int sqlite_delete(sqlite3 *db)
{
	char name[10];
	bzero(name, sizeof(name));
	printf("input will delete contact: ");
	scanf("%s", name);

	int nrow_last, nrow_now, ncolumn;
	char **result = NULL;
	char *errmsg = NULL;
	sqlite3_get_table(db, "select * from contact;", 
			&result, &nrow_last, &ncolumn, &errmsg);
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
	sqlite3_free_table(result);

	char delete[100];
	bzero(delete, sizeof(delete));
	snprintf(delete, sizeof(delete), 
		"delete from contact where name='%s';", name);
	if(sqlite3_exec(db, delete, NULL, NULL, &errmsg))
	{
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
		printf("sqlite3_exec() failed\n");
		return 1;
	}

	sqlite3_get_table(db, "select * from contact;", 
			&result, &nrow_now, &ncolumn, &errmsg);
#ifdef DEBUG
		printf("%d\n", __LINE__);
#endif
	sqlite3_free_table(result);

	if(nrow_now == nrow_last)
		return 1;

	return 0;
}

void init_show(void)
{
	struct fb_var_screeninfo vinfo;
	struct image iminfo;
	unsigned char *fbmem = init_lcd(&vinfo);
	unsigned char * phone = load_jpeg("phone.jpg", &iminfo);
	write_lcd(fbmem, &vinfo, phone, &iminfo, 0, 0);
	
	free(phone);
}

