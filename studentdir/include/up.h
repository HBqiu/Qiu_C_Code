#ifndef UP_H
#define UP_H

//#define MAX_INPUT_LEN 255
#ifndef PASSWORD_LEN 
#define PASSWORD_LEN 16
#endif
//#define SALT_LEN 16

// 用户登录验证
int verify_user_login(MYSQL *conn, const char *username, const char *password);
// 更改密码
int change_password(MYSQL *conn, const char *username, const char *old_password, const char *new_password);
// 重置密码（只有root能重置任何用户的密码）
int reset_password(MYSQL *conn, const char *username);

#endif