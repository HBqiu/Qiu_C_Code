#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>
#include "login.h"
#include "adduser.h"
// 生成 MD5 哈希
void generate_md5_hash(const char *password, const char *salt, unsigned char *output_hash) {
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, salt, strlen(salt));  // 更新盐
    MD5_Update(&md5_ctx, password, strlen(password));  // 更新密码
    MD5_Final(output_hash, &md5_ctx);  // 获取哈希值
}


// 打印数据库中的所有记录
void print_all_records(MYSQL *conn) {
    MYSQL_RES *result;
    MYSQL_ROW row;

    // 查询所有记录
    const char *query = "SELECT username, password, salt FROM userpass";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query failed: %s\n", mysql_error(conn));
        return;
    }

    // 获取查询结果
    result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "MySQL store result failed: %s\n", mysql_error(conn));
        return;
    }

    // 打印表头
    printf("用户名\t密码\t\t\t\t盐\n");

    // 打印每一行数据
    while ((row = mysql_fetch_row(result))) {
        printf("%s\t", row[0]);
        print_binary((unsigned char *)row[1], 16);  // 打印密码的二进制值
        printf("\t%s\n", row[2]);
    }

    // 释放结果集
    mysql_free_result(result);
}

// 从数据库中查找用户并验证密码
