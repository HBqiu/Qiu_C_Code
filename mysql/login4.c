#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/md5.h>

#define MAX_INPUT_LEN 255  // 最大用户名长度
#define PASSWORD_LEN 16    // MD5 哈希值长度

// 打印二进制数据为十六进制
void print_binary(unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// 计算密码和盐的 MD5 哈希
void calculate_md5(const char *password, const char *salt, unsigned char *hash) {
//printf("p:%s s:%s\n",password,salt);
    MD5_CTX ctx;
    MD5_Init(&ctx);
MD5_Update(&ctx, salt, strlen(salt));
    MD5_Update(&ctx, password, strlen(password));
    
    MD5_Final(hash, &ctx);
}

// 登录验证函数
int login_user(MYSQL *conn, const char *username, const char *password) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_BIND result_bind[2];
    const char *query = "SELECT salt, password FROM userpass WHERE username = ?";
    char salt[17] = {0};                      // 数据库中存储的盐
    unsigned char stored_hash[PASSWORD_LEN];  // 数据库中存储的密码哈希
    unsigned char computed_hash[PASSWORD_LEN];

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
    result_bind[1].buffer = (char *)stored_hash;
    result_bind[1].buffer_length = sizeof(stored_hash);

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
    if (fetch_result == MYSQL_NO_DATA) {
//        printf("账号不存在。\n");
        mysql_stmt_close(stmt);
        return 0;
    } else if (fetch_result != 0) {
        fprintf(stderr, "mysql_stmt_fetch failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return 0;
    }

//printf("p:%s s:%s\n",password,salt);    
// 计算输入密码和盐的哈希值
    calculate_md5(password, salt, computed_hash);
//	print_binary(stored_hash,16);
//	printf("%s\n",salt);
//	print_binary(computed_hash,16);
    // 验证哈希值
    if (memcmp(stored_hash, computed_hash, PASSWORD_LEN) == 0) {
        printf("登录成功！\n");
    } else {
  //      printf("密码错误。\n");
	mysql_stmt_close(stmt);
return 0;
    }

    // 关闭预处理语句
    mysql_stmt_close(stmt);
    return 1;
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

    // 获取用户名和密码
    char username[MAX_INPUT_LEN];
    char password[MAX_INPUT_LEN];
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

    // 关闭 MySQL 连接
    mysql_close(conn);

    return 0;
}

