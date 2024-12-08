#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/md5.h>

#define MAX_INPUT_LEN 255
#define PASSWORD_LEN 16
#define SALT_LEN 16

// 打印二进制数据
void print_binary(unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// 生成 MD5 哈希
void generate_md5_hash(const char *password, const char *salt, unsigned char *output_hash) {
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, salt, strlen(salt));  // 更新盐
    MD5_Update(&md5_ctx, password, strlen(password));  // 更新密码
    MD5_Final(output_hash, &md5_ctx);  // 获取哈希值
}

// 用户登录验证
int verify_user_login(MYSQL *conn, const char *username, const char *password) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_BIND result[2];  // 用于接收查询结果：盐和密码哈希

    const char *query = "SELECT salt, password FROM userpass WHERE username = ?";

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init failed\n");
        return 0;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
        return 0;
    }
	memset(bind,0,sizeof(bind));
    // 绑定参数：用户名
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    // 绑定结果：盐和密码哈希
    char salt[SALT_LEN + 1] = {0};  // 确保盐的大小是 16 字节
    unsigned char stored_password_hash[16];  // 用于存储密码的哈希
memset(result,0,sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_STRING;  // 盐是字符型数据（CHAR(16)）
    result[0].buffer = salt;  // 将盐的内容存储到该位置
    result[0].buffer_length = SALT_LEN;  // 盐的长度是 16 字节

    result[1].buffer_type = MYSQL_TYPE_BLOB;  // 密码哈希使用 BLOB 类型（二进制数据）
    result[1].buffer = stored_password_hash;  // 将密码哈希存储到该位置
    result[1].buffer_length = 16;  // MD5 哈希值长度是 16 字节

    if (mysql_stmt_bind_param(stmt, bind) || mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "mysql_stmt_bind_param failed: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        return 0;
    }

    int fetch_result = mysql_stmt_fetch(stmt);
    if (fetch_result == 0) {
        // 生成用户输入密码的哈希值
        unsigned char input_password_hash[16];
        generate_md5_hash(password, salt, input_password_hash);
printf("P:%s S:%s",password,salt);
        // 比较哈希值
        if (memcmp(stored_password_hash, input_password_hash, 16) == 0) {
            mysql_stmt_close(stmt);
            return 1;  // 登录成功
        } else {
            printf("密码错误\n");
        }
    } else {
        printf("用户不存在\n");
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
    char salt[SALT_LEN + 1] = "defaultSalt";  // 可以使用自定义盐
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

int main() {
    MYSQL *conn;

    // 连接数据库
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init failed: %s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "xiao", "1125", "user", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // 用户输入选择
    int choice;
    printf("请选择操作：\n1. 更改密码\n2. 重置密码 (仅root用户)\n选择操作: ");
    scanf("%d", &choice);
    getchar();  // 清除换行符

    if (choice == 1) {
        // 更改密码
        char username[MAX_INPUT_LEN], old_password[MAX_INPUT_LEN], new_password[MAX_INPUT_LEN];
        printf("请输入用户名: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';  // 移除换行符

        printf("请输入当前密码: ");
        fgets(old_password, sizeof(old_password), stdin);
        old_password[strcspn(old_password, "\n")] = '\0';  // 移除换行符

        printf("请输入新密码: ");
        fgets(new_password, sizeof(new_password), stdin);
        new_password[strcspn(new_password, "\n")] = '\0';  // 移除换行符

        if (change_password(conn, username, old_password, new_password)) {
            printf("密码更改成功\n");
        } else {
            printf("密码更改失败\n");
        }

    } else if (choice == 2) {
        // 重置密码（只有root用户可以进行此操作）
        char root_password[MAX_INPUT_LEN];
        printf("请输入root用户密码: ");
        fgets(root_password, sizeof(root_password), stdin);
        root_password[strcspn(root_password, "\n")] = '\0';  // 移除换行符

        if (verify_user_login(conn, "root", root_password)) {
            char username[MAX_INPUT_LEN];
            printf("请输入要重置密码的用户名: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = '\0';  // 移除换行符

            if (reset_password(conn, username)) {
                printf("密码重置成功，恢复为默认密码\n");
            } else {
                printf("密码重置失败\n");
            }
        } else {
            printf("root用户密码错误，无法重置密码\n");
        }

    } else {
        printf("无效的选择\n");
    }

    // 关闭数据库连接
    mysql_close(conn);
    return 0;
}


