#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/md5.h>
#include <stdbool.h>
#include "up.h"
#include "login.h"
#include "adduser.h"

int verify_user_root(MYSQL *conn, const char *username)
{
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_BIND result[1]; // 用于接收查询结果：盐和密码哈希
                          // printf("P:%s",password);
    //  查询语句：获取用户名的盐和密码哈希
    const char *query = "SELECT root FROM userpass WHERE username = ?";

    // 初始化预处理语句
    stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query)))
    {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return 0;
    }
    memset(bind, 0, sizeof(bind));
    // 绑定参数：用户名
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bool root = false; // 声明为布尔类型
    memset(result, 0, sizeof(result));

    // 配置结果集
    result[0].buffer_type = MYSQL_TYPE_TINY; // 设置为 TINYINT 类型
    result[0].buffer = &root;                // 将布尔值的地址传入
    result[0].buffer_length = sizeof(root);  // 使用 root 的大小
    // 绑定参数到预处理语句
    if (mysql_stmt_bind_param(stmt, bind) || mysql_stmt_bind_result(stmt, result))
    {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        return 0;
    }

    // 执行查询
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        return 0;
    }

    // 获取查询结果
    int fetch_result = mysql_stmt_fetch(stmt);
    if (fetch_result == 0)
    {
        // 比较数据库中的哈希值与生成的哈希值
        if (root)
        {
            mysql_stmt_close(stmt);
            return 1; // 登录成功
        }
    }
    else
    {
       // fprintf(stderr, "mysql_stmt_fetch failed: %s\n", mysql_error(conn));
    }

    mysql_stmt_close(stmt);
    return 0; // 登录失败
}

