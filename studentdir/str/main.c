#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>
#include <time.h>
#include "adduser.h"
#include "login.h"
#include "up.h"
#include "std.h"

// 常量定义
// #define MAX_INPUT_LEN 255
// #define SALT_LEN 16

// 函数声明
MYSQL *connect_to_db();
MYSQL *connect_to_stu();
int handle_login(MYSQL *conn);
void handle_register(MYSQL *conn);
void handle_password_change(MYSQL *conn);

int main()
{
    int choice;
    MYSQL *conn = connect_to_db();

    if (!conn)
    {
        printf("数据库连接失败，程序退出。\n");
        return EXIT_FAILURE;
    }

    printf("请选择操作：\n1. 登录\n2. 注册\n3. 修改密码\n请输入你的选择: ");
    scanf("%d", &choice);
    getchar(); // 清除缓冲区的换行符

    switch (choice)
    {
    case 1:
        if (handle_login(conn))
        {
            MYSQL *connstu = connect_to_stu();
            int choice;
            int student_id, age, grade;
            char class[MAX_COLUMN_NAME_LENGTH], name[MAX_COLUMN_NAME_LENGTH];
            while (1)
            {
                display_menu();
                printf("请输入你的选择：");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    // 插入新学生
                    printf("请输入学生ID: ");
                    scanf("%d", &student_id);
                    printf("请输入年级: ");
                    scanf("%d", &age);
                    printf("请输入班级: ");
                    scanf("%s", class);
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    insert_student(connstu, student_id, age, class, name);
                    break;

                case 2:
                    // 查询指定学号的学生
                    printf("请输入学生ID: ");
                    scanf("%d", &student_id);
                    select_student_by_id(connstu, student_id);
                    break;

                case 3:
                    // 查询指定年级的所有学生
                    printf("请输入年级: ");
                    scanf("%d", &grade);
                    select_students_by_grade(connstu, grade);
                    break;

                case 4:
                    // 查询指定年级和班级的所有学生
                    printf("请输入年级: ");
                    scanf("%d", &grade);
                    printf("请输入班级: ");
                    scanf("%s", class);
                    select_students_by_grade_class(connstu, grade, class);
                    break;

                case 5:
                    // 查看所有学生信息
                    select_all_students(connstu);
                    break;

                case 6:
                    // 更新学生信息
                    printf("请输入学生ID: ");
                    scanf("%d", &student_id);

                    // 检查学生是否存在
                    if (!student_exists(connstu, student_id))
                    {
                        printf("未找到学号为 %d 的学生，更新失败。\n", student_id);
                        break;
                    }

                    printf("请输入新的年级: ");
                    scanf("%d", &age);
                    printf("请输入新的班级: ");
                    scanf("%s", class);
                    printf("请输入新的姓名: ");
                    scanf("%s", name);
                    update_student(connstu, student_id, age, class, name);
                    break;

                case 7:
                    // 删除学生信息
                    printf("请输入学生ID: ");
                    scanf("%d", &student_id);

                    // 检查学生是否存在
                    if (!student_exists(connstu, student_id))
                    {
                        printf("未找到学号为 %d 的学生，删除失败。\n", student_id);
                        break;
                    }

                    delete_student(connstu, student_id);
                    break;

                case 8:
                    // 退出
                    printf("退出程序。\n");
                    mysql_close(connstu); // 关闭数据库连接
                    exit(0);

                default:
                    printf("无效的选项，请重新选择。\n");
                    break;
                }
            }
        }
        break;
    case 2:
        handle_register(conn);
        break;
    case 3:
	srand((unsigned int)time(NULL));
        handle_password_change(conn);
        break;
    default:
        printf("无效的选择。\n");
    }

    // 关闭数据库连接
    mysql_close(conn);
    return 0;
}

MYSQL *connect_to_stu()
{
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init failed: %s\n", mysql_error(conn));
        return NULL;
    }

    if (mysql_real_connect(conn, "localhost", "xiao", "1125", "stu", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    return conn;
}
// 连接到 MySQL 数据库
MYSQL *connect_to_db()
{
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init failed: %s\n", mysql_error(conn));
        return NULL;
    }

    if (mysql_real_connect(conn, "localhost", "xiao", "1125", "user", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

// 登录处理
int handle_login(MYSQL *conn)
{
    char username[MAX_INPUT_LEN];
    char password[MAX_INPUT_LEN];

    printf("请输入用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // 移除换行符

    printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // 移除换行符

    if (verify_user_login(conn, username, password))
    {
        printf("登录成功！进入学生管理系统\n");
        return 1;
    }
    else
    {
        printf("登录失败，请检查用户名和密码。\n");
        return 0;
    }
}

// 注册处理
void handle_register(MYSQL *conn)
{
//	print_all_records(conn);
    char username[MAX_INPUT_LEN];
    char password[MAX_INPUT_LEN];
    char salt[SALT_LEN + 1] = {0};
    unsigned char hashed_password[MD5_DIGEST_LENGTH];

    printf("请输入用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // 移除换行符

    printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // 移除换行符

    generate_salt(salt, SALT_LEN);

/*    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, salt, strlen(salt));
    MD5_Update(&md5_ctx, password, strlen(password));
    MD5_Final(hashed_password, &md5_ctx);
*/
generate_md5_hash(password,salt,hashed_password);
    insert_user_to_db(conn, username, hashed_password, salt);
}

// 修改密码处理
void handle_password_change(MYSQL *conn)
{
    int choice;
    printf("请选择操作：\n1. 修改密码\n2. 重置密码（仅root用户）\n");
    scanf("%d", &choice);
    getchar(); // 清除缓冲区的换行符

    if (choice == 1)
    {
        char username[MAX_INPUT_LEN], old_password[MAX_INPUT_LEN], new_password[MAX_INPUT_LEN];

        printf("请输入用户名: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("请输入当前密码: ");
        fgets(old_password, sizeof(old_password), stdin);
        old_password[strcspn(old_password, "\n")] = '\0';

        printf("请输入新密码: ");
        fgets(new_password, sizeof(new_password), stdin);
        new_password[strcspn(new_password, "\n")] = '\0';

        if (change_password(conn, username, old_password, new_password))
        {
            printf("密码修改成功！\n");
        }
        else
        {
            printf("密码修改失败，请检查输入。\n");
        }
    }
    else if (choice == 2)
    {
        char root_password[MAX_INPUT_LEN];
        printf("请输入root用户密码: ");
        fgets(root_password, sizeof(root_password), stdin);
        root_password[strcspn(root_password, "\n")] = '\0';

        if (verify_user_login(conn, "root", root_password))
        {
            char username[MAX_INPUT_LEN];
            printf("请输入要重置密码的用户名: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = '\0';

            if (reset_password(conn, username))
            {
                printf("密码重置成功！\n");
            }
            else
            {
                printf("密码重置失败。\n");
            }
        }
        else
        {
            printf("root密码错误，无法进行操作。\n");
        }
    }
    else
    {
        printf("无效的选择。\n");
    }
}

