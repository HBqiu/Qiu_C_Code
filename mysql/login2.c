#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_INPUT_LEN 16  // 最大输入长度

// 打印二进制数据为十六进制
void print_binary(unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// 查询数据库，获取指定用户名的盐和密码哈希
int query_user(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_BIND result_bind[2];
    const char *query = "SELECT salt, password FROM userpass WHERE username = ?";
    char salt[17] = {0};  // 16 字节盐 + 空终止符
    unsigned char stored_password_hash[16] = {0};

    // 初始化预处理语句
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 绑定输入参数
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 绑定输出结果
    memset(result_bind, 0, sizeof(result_bind));
    result_bind[0].buffer_type = MYSQL_TYPE_STRING;
    result_bind[0].buffer = salt;
    result_bind[0].buffer_length = sizeof(salt) - 1;

    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = (char *)stored_password_hash;
    result_bind[1].buffer_length = sizeof(stored_password_hash);

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 执行查询
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 获取查询结果
    int fetch_result = mysql_stmt_fetch(stmt);
    if (fetch_result == 0) {
        // 打印查询到的盐和密码哈希值
        printf("查询结果：\n");
        printf("用户名: %s\n", username);
        printf("盐: %s\n", salt);
        printf("密码哈希: ");
        print_binary(stored_password_hash, sizeof(stored_password_hash));
    } else if (fetch_result == MYSQL_NO_DATA) {
        printf("没有找到该用户名的记录。\n");
    } else {
        fprintf(stderr, "mysql_stmt_fetch failed: %s\n", mysql_stmt_error(stmt));
    }

    // 关闭预处理语句
    mysql_stmt_close(stmt);
    return 1;  // 成功完成查询
}

int main() {
    MYSQL *conn;

    // 初始化 MySQL 连接
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

    // 获取用户名
    char username[MAX_INPUT_LEN];
    printf("请输入用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // 移除换行符

    // 调用查询函数
    if (!query_user(conn, username)) {
        printf("查询失败\n");
    }

    // 关闭 MySQL 连接
    mysql_close(conn);

    return 0;
}

