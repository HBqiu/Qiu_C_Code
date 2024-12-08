#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/md5.h>

#define MAX_INPUT_LEN 255  // 用户名最大长度

void print_binary(const unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// 用户登录验证函数
int login_user(MYSQL *conn, const char *username, const char *password) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1], result_bind[2];
    char salt[17] = {0};
    unsigned char stored_password_hash[16];
    unsigned char calculated_hash[16];

    // 查询语句
    const char *query = "SELECT salt, password FROM userpass WHERE username = ?";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 绑定输入参数（用户名）
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 绑定输出参数（盐值和密码哈希）
    memset(result_bind, 0, sizeof(result_bind));
    result_bind[0].buffer_type = MYSQL_TYPE_STRING;
    result_bind[0].buffer = salt;
    result_bind[0].buffer_length = sizeof(salt) - 1;

    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = stored_password_hash;
    result_bind[1].buffer_length = sizeof(stored_password_hash);

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result failed: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 执行查询
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return 0;
    }

    // 获取查询结果
    if (mysql_stmt_fetch(stmt) == 0) {
        // 打印调试信息
        printf("调试信息：\n");
        printf("用户名: %s\n", username);
        printf("数据库盐值: %s\n", salt);
        printf("数据库密码哈希: ");
        print_binary(stored_password_hash, 16);

        // 使用盐值和密码计算哈希
        MD5_CTX md5_ctx;
        MD5_Init(&md5_ctx);
        MD5_Update(&md5_ctx, salt, strlen(salt));
        MD5_Update(&md5_ctx, password, strlen(password));
        MD5_Final(calculated_hash, &md5_ctx);

        printf("计算出的密码哈希: ");
        print_binary(calculated_hash, 16);

        // 比较哈希值
        if (memcmp(stored_password_hash, calculated_hash, 16) == 0) {
            printf("登录成功\n");
            mysql_stmt_close(stmt);
            return 1;
        } else {
            printf("密码错误\n");
        }
    } else {
        printf("用户不存在\n");
    }

    mysql_stmt_close(stmt);
    return 0;
}

int main() {
    MYSQL *conn;

    // 初始化 MySQL 连接
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init failed\n");
        exit(1);
    }

    // 连接数据库
    if (!mysql_real_connect(conn, "localhost", "xiao", "1125", "user", 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // 获取用户输入的用户名和密码
    char username[MAX_INPUT_LEN], password[MAX_INPUT_LEN];
    printf("请输入用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // 移除换行符

    printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // 移除换行符

    // 调用登录验证函数
    if (!login_user(conn, username, password)) {
        printf("登录失败\n");
    }

    // 关闭数据库连接
    mysql_close(conn);

    return 0;
}

