#include <stdio.h>
#include <mysql.h>
#define QUER "select user,host,Select_priv from user"
int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	
	if(!mysql_real_connect(conn,"localhost","xiao","1125","mysql",0,NULL,0))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		return 1;
	}
	
	if(mysql_query(conn,QUER))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
                return 1;
	}

	res = mysql_use_result(conn);
	
	while((row = mysql_fetch_row(res)) != NULL)
	{
		printf("%15s %10s %2s\n",row[0],row[1],row[2]);
	}

	mysql_free_result(res);

	mysql_close(conn);

	return 0;
}
