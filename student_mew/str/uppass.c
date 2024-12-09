#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/md5.h>
#include "up.h"
#include "login.h"
#include "adduser.h"


// 用户登录验证
int verify_user_login(MYSQL *conn, const char *username, const char *password) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_BIND result[2];  // 用于接收查询结果：盐和密码哈希
//printf("P:%s",password);
    // 查询语句：获取用户名的盐和密码哈希
    const char *query = "SELECT salt, password FROM userpass WHERE username = ?";

    // 初始化预处理语句
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return 0;
    }
memset(bind, 0, sizeof(bind));
    // 绑定参数：用户名
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    // 绑定结果：盐和密码哈希
    char salt[SALT_LEN + 1 ] = {0};  // 确保盐的大小是 16 字节
    unsigned char stored_password_hash[16];  // 用于存储密码的哈希
memset(result, 0, sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_STRING;  // 盐是字符型数据（CHAR(16)）
    result[0].buffer = salt;  // 将盐的内容存储到该位置
    result[0].buffer_length = 16;  // 盐的长度是 16 字节

    result[1].buffer_type = MYSQL_TYPE_BLOB;  // 密码哈希使用 BLOB 类型（二进制数据）
    result[1].buffer = stored_password_hash;  // 将密码哈希存储到该位置
    result[1].buffer_length = SALT_LEN;  // MD5 哈希值长度是 16 字节

    // 绑定参数到预处理语句
    if (mysql_stmt_bind_param(stmt, bind) || mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        return 0;
    }

    // 执行查询
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        return 0;
    }

    // 获取查询结果
    int fetch_result = mysql_stmt_fetch(stmt);
    if (fetch_result == 0) {

        // 生成用户输入密码的哈希值
        unsigned char input_password_hash[16];
        generate_md5_hash(password, salt, input_password_hash);

        // 比较数据库中的哈希值与生成的哈希值
        if (memcmp(stored_password_hash, input_password_hash, 16) == 0) {
            printf("登录成功\n");
            mysql_stmt_close(stmt);
            return 1;  // 登录成功
        }
    } else if (fetch_result == MYSQL_NO_DATA) {
        printf("用户不存在，请检查用户名。\n");
    } else {
        fprintf(stderr, "mysql_stmt_fetch failed: %s\n", mysql_error(conn));
    }

    mysql_stmt_close(stmt);
    return 0;  // 登录失败
}

// 更改密码
int change_password(MYSQL *conn, const char *username, const char *old_password, const char *new_password) {
    // 1. 验证当前密码是否正确
    if (!verify_user_login(conn, username, old_password)) {
        printf("当前密码错误\n");
        return 0;  // 当前密码不正确
    }

    // 2. 生成新密码的哈希值
    char salt[SALT_LEN + 1] = {0};  // 可以使用自定义盐
generate_salt(salt,SALT_LEN);
    unsigned char new_password_hash[16];
    generate_md5_hash(new_password, salt, new_password_hash);

    // 3. 更新密码和盐
    MYSQL_STMT *stmt;
    const char *update_query = "UPDATE userpass SET password = ?, salt = ? WHERE username = ?";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, update_query, strlen(update_query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = new_password_hash;
    bind[0].buffer_length = 16;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = salt;
    bind[1].buffer_length = SALT_LEN;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)username;
    bind[2].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        return 0;
    }

    printf("密码更改成功\n");
    mysql_stmt_close(stmt);
    return 1;
}

// 重置密码（只有root能重置任何用户的密码）
int reset_password(MYSQL *conn, const char *username) {
    const char *default_password = "0000";  // 默认密码
    const char *default_salt = "0000000000000000";  // 默认盐

    // 生成默认密码的哈希
    unsigned char default_password_hash[16];
    generate_md5_hash(default_password, default_salt, default_password_hash);

    // 更新密码和盐
    MYSQL_STMT *stmt;
    const char *update_query = "UPDATE userpass SET password = ?, salt = ? WHERE username = ?";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, update_query, strlen(update_query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_BLOB;
    bind[0].buffer = default_password_hash;
    bind[0].buffer_length = 16;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)default_salt;
    bind[1].buffer_length = SALT_LEN;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)username;
    bind[2].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        return 0;
    }

    printf("密码重置成功，已恢复为默认密码\n");
    mysql_stmt_close(stmt);
    return 1;
}
