#ifndef LOGIN_H
#define LOGIN_H

#ifndef SALT_LEN
#define SALT_LEN 16  // 盐的长度
#endif

#ifndef MAX_INPUT_LEN
#define MAX_INPUT_LEN 255  // 最大输入长度
#endif

// 生成 MD5 哈希
void generate_md5_hash(const char *password, const char *salt, unsigned char *output_hash);
// 打印二进制数据（用于调试）
void print_binary(unsigned char *data, size_t length);
// 打印数据库中的所有记录
void print_all_records(MYSQL *conn);
// 从数据库中查找用户并验证密码
//int verify_user_login(MYSQL *conn, const char *username, const char *password);


#endif