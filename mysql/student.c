#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY_LENGTH 1024
#define MAX_COLUMN_NAME_LENGTH 100  // 定义列名的最大长度

// 数据库连接信息
const char *host = "localhost"; // MySQL主机
const char *user = "xiao";      // MySQL用户名
const char *password = "1125";  // MySQL密码
const char *dbname = "stu";     // MySQL数据库名

// MySQL连接函数
MYSQL *connect_mysql() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    conn = mysql_real_connect(conn, host, user, password, dbname, 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

// 执行SQL查询
int execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "QUERY FAILED: %s\n", mysql_error(conn));
        return 0;
    }
    return 1;
}

// 检查学生是否存在
int student_exists(MYSQL *conn, int student_id) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "SELECT 1 FROM student WHERE student_id = %d LIMIT 1", student_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "QUERY FAILED: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    mysql_free_result(res);

    return row != NULL;
}

// 插入新学生
void insert_student(MYSQL *conn, int student_id, int age, const char *class_name, const char *name) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "INSERT INTO student (student_id, age, class, name) VALUES (%d, %d, '%s', '%s')",
             student_id, age, class_name, name);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "INSERT FAILED: %s\n", mysql_error(conn));
        return;
    }
    printf("学生 ID %d 插入成功。\n", student_id);
}

// 查询指定学号的学生
void select_student_by_id(MYSQL *conn, int student_id) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "SELECT * FROM student WHERE student_id = %d", student_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "QUERY FAILED: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("\n学号: %-10s | 年级: %-5s | 班级: %-15s | 姓名: %-20s\n",
               row[0] ? row[0] : "NULL", row[1] ? row[1] : "NULL",
               row[2] ? row[2] : "NULL", row[3] ? row[3] : "NULL");
    } else {
        printf("未找到学号为 %d 的学生信息。\n", student_id);
    }

    mysql_free_result(res);
}

// 查询指定年级的所有学生
void select_students_by_grade(MYSQL *conn, int grade) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "SELECT * FROM student WHERE age = %d", grade);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "QUERY FAILED: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row;
    printf("\n年级 %d 的学生信息：\n", grade);
    printf("学号        | 年级 | 班级            | 姓名\n");
    printf("-----------------------------------------------\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%-12s | %-5s | %-15s | %-20s\n",
               row[0] ? row[0] : "NULL", row[1] ? row[1] : "NULL",
               row[2] ? row[2] : "NULL", row[3] ? row[3] : "NULL");
    }

    mysql_free_result(res);
}

// 查询指定年级和班级的所有学生
void select_students_by_grade_class(MYSQL *conn, int grade, const char *class_name) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "SELECT * FROM student WHERE age = %d AND class = '%s'", grade, class_name);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "QUERY FAILED: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row;
    printf("\n年级 %d, 班级 %s 的学生信息：\n", grade, class_name);
    printf("学号        | 年级 | 班级            | 姓名\n");
    printf("-----------------------------------------------\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%-12s | %-5s | %-15s | %-20s\n",
               row[0] ? row[0] : "NULL", row[1] ? row[1] : "NULL",
               row[2] ? row[2] : "NULL", row[3] ? row[3] : "NULL");
    }

    mysql_free_result(res);
}

// 查看所有学生信息
void select_all_students(MYSQL *conn) {
    char query[MAX_QUERY_LENGTH] = "SELECT * FROM student";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "QUERY FAILED: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row;
    printf("\n所有学生信息：\n");
    printf("学号        | 年级 | 班级            | 姓名\n");
    printf("-----------------------------------------------\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%-12s | %-5s | %-15s | %-20s\n",
               row[0] ? row[0] : "NULL", row[1] ? row[1] : "NULL",
               row[2] ? row[2] : "NULL", row[3] ? row[3] : "NULL");
    }

    mysql_free_result(res);
}

// 更新学生信息
void update_student(MYSQL *conn, int student_id, int age, const char *class_name, const char *name) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "UPDATE student SET age = %d, class = '%s', name = '%s' WHERE student_id = %d",
             age, class_name, name, student_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "UPDATE FAILED: %s\n", mysql_error(conn));
        return;
    }

    printf("学生 ID %d 更新成功。\n", student_id);
}

// 删除学生信息
void delete_student(MYSQL *conn, int student_id) {
    char query[MAX_QUERY_LENGTH];
    snprintf(query, sizeof(query), "DELETE FROM student WHERE student_id = %d", student_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "DELETE FAILED: %s\n", mysql_error(conn));
        return;
    }
    printf("学生 ID %d 删除成功。\n", student_id);
}

// 显示操作菜单
void display_menu() {
    printf("\n请选择操作：\n");
    printf("1. 插入新学生\n");
    printf("2. 查询指定学号的学生\n");
    printf("3. 查询整个年级的学生\n");
    printf("4. 查询特定年级班级组合的学生\n");
    printf("5. 查看所有学生\n");
    printf("6. 更新学生信息\n");
    printf("7. 删除学生信息\n");
    printf("8. 退出\n");
}

// 主函数，提供操作菜单
int main() {
    // 连接 MySQL 数据库
    MYSQL *conn = connect_mysql();

    int choice;
    int student_id, age, grade;
    char class[MAX_COLUMN_NAME_LENGTH], name[MAX_COLUMN_NAME_LENGTH];

    while (1) {
        display_menu();
        printf("请输入你的选择：");
        scanf("%d", &choice);

        switch (choice) {
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
                insert_student(conn, student_id, age, class, name);
                break;

            case 2:
                // 查询指定学号的学生
                printf("请输入学生ID: ");
                scanf("%d", &student_id);
                select_student_by_id(conn, student_id);
                break;

            case 3:
                // 查询指定年级的所有学生
                printf("请输入年级: ");
                scanf("%d", &grade);
                select_students_by_grade(conn, grade);
                break;

            case 4:
                // 查询指定年级和班级的所有学生
                printf("请输入年级: ");
                scanf("%d", &grade);
                printf("请输入班级: ");
                scanf("%s", class);
                select_students_by_grade_class(conn, grade, class);
                break;

            case 5:
                // 查看所有学生信息
                select_all_students(conn);
                break;

            case 6:
                // 更新学生信息
                printf("请输入学生ID: ");
                scanf("%d", &student_id);

                // 检查学生是否存在
                if (!student_exists(conn, student_id)) {
                    printf("未找到学号为 %d 的学生，更新失败。\n", student_id);
                    break;
                }

                printf("请输入新的年级: ");
                scanf("%d", &age);
                printf("请输入新的班级: ");
                scanf("%s", class);
                printf("请输入新的姓名: ");
                scanf("%s", name);
                update_student(conn, student_id, age, class, name);
                break;

            case 7:
                // 删除学生信息
                printf("请输入学生ID: ");
                scanf("%d", &student_id);

                // 检查学生是否存在
                if (!student_exists(conn, student_id)) {
                    printf("未找到学号为 %d 的学生，删除失败。\n", student_id);
                    break;
                }

                delete_student(conn, student_id);
                break;

            case 8:
                // 退出
                printf("退出程序。\n");
                mysql_close(conn); // 关闭数据库连接
                exit(0);

            default:
                printf("无效的选项，请重新选择。\n");
                break;
        }
    }

    return 0;
}

