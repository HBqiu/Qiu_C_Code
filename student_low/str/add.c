#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>
#include "adduser.h"

// 生成随机盐
void generate_salt(char *salt, size_t length) {
    size_t charset_len = strlen(CHARSET);  // 获取字符集长度
    for (size_t i = 0; i < length; i++) {
        salt[i] = CHARSET[rand() % charset_len];  // 从字符集中随机选取字符
    }
    salt[length] = '\0';  // 确保盐是一个以 '\0' 结尾的字符串
}

// 打印二进制数据（用于调试）
void print_binary(unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);  // 打印每个字节的十六进制值
    }
    printf("\n");
}

// 将用户信息插入数据库
void insert_user_to_db(MYSQL *conn, const char *username, unsigned char *hashed_password, const char *salt) {
    const char *query = "INSERT INTO userpass (username, password, salt, root) VALUES (?, ?, ?, ?)";

    // 初始化预处理语句
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return;
    }

    // 绑定参数
    MYSQL_BIND bind[4];
memset(bind,0,sizeof(bind));
    // 绑定用户名参数（VARCHAR）
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    // 绑定密码参数（VARBINARY），加密后的 MD5 哈希
    bind[1].buffer_type = MYSQL_TYPE_BLOB;  // 使用 BLOB 来存储二进制数据
    bind[1].buffer = (char *)hashed_password;  // MD5 哈希（16 字节）
    bind[1].buffer_length = MD5_DIGEST_LENGTH;  // 16 字节

    // 绑定盐参数（CHAR），盐是一个 16 字符的字符串
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)salt;
    bind[2].buffer_length = SALT_LEN;  // 盐的长度，16 字符

    // 绑定 root 参数（TINYINT）
    int root = 0;  // 默认为 0
    bind[3].buffer_type = MYSQL_TYPE_TINY;
    bind[3].buffer = (void *)&root;

    // 绑定参数到预处理语句
    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        return;
    }

    // 执行插入语句
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        return;
    }

    printf("用户 '%s' 添加成功！\n", username);

    // 关闭语句
    mysql_stmt_close(stmt);
}
