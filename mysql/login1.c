#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>

#define SALT_LEN 16  // 盐的长度
#define MAX_INPUT_LEN 16  // 最大输入长度

// 生成 MD5 哈希
void generate_md5_hash(const char *password, const char *salt, unsigned char *output_hash) {
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, salt, strlen(salt));  // 更新盐
    MD5_Update(&md5_ctx, password, strlen(password));  // 更新密码
    MD5_Final(output_hash, &md5_ctx);  // 获取哈希值
}

// 打印二进制数据（用于调试）
void print_binary(unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);  // 打印每个字节的十六进制值
    }
    printf("\n");
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

        // 打印调试信息：用户输入的密码和盐
        printf("用户输入的密码: %s\n", password);
        printf("生成的盐: %s\n", salt);

        // 生成用户输入密码的哈希值
        unsigned char input_password_hash[16];
        generate_md5_hash(password, salt, input_password_hash);

        // 打印用户输入密码的哈希值
        printf("用户输入密码的哈希值: ");
        print_binary(input_password_hash, 16);

        // 打印数据库中提取出来的盐和哈希值
        printf("数据库中提取的盐: %s\n", salt);
        printf("数据库中提取的密码哈希值: ");
        print_binary(stored_password_hash, 16);

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

    printf("登录失败\n");
    mysql_stmt_close(stmt);
    return 0;  // 登录失败
}

int main() {
    MYSQL *conn;
    char username[MAX_INPUT_LEN] ;
    char password[MAX_INPUT_LEN] ;

    // 连接到 MySQL 数据库
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init failed: %s\n", mysql_error(conn));
        exit(1);
    }

    // 连接到数据库
    if (mysql_real_connect(conn, "localhost", "xiao", "1125", "user", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // 打印数据库中表的所有记录
   // printf("正在打印 userpass 表中的所有记录：\n");
   // print_all_records(conn);

    // 提示用户输入用户名和密码
    printf("请输入用户名: ");
       fgets(username, sizeof(username), stdin);
      username[strcspn(username, "\n")] = '\0';  // 移除换行符
   // printf("%s",username);
      printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
   // printf("%s %s\n",username,password);
    password[strcspn(password, "\n")] = '\0';  // 移除换行符

    // 验证用户登录
    if (!verify_user_login(conn, username, password)) {
        printf("登录失败，请检查用户名和密码是否正确。\n");
    }

    // 关闭 MySQL 连接
    mysql_close(conn);

    return 0;
}

