#ifndef ADDUSER_H
#define ADDUSER_H

#ifndef SALT_LEN
#define SALT_LEN 16  // 盐的长度
#endif

#ifndef CHARSET
#define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"  // 可用字符集
#endif

// 生成随机盐
void generate_salt(char *salt, size_t length);
// 打印二进制数据（用于调试）
void print_binary(unsigned char *data, size_t length) ;
// 将用户信息插入数据库
void insert_user_to_db(MYSQL *conn, const char *username, unsigned char *hashed_password, const char *salt) ;


#endif