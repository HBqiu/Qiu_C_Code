#ifndef STD_H
#define STD_H

#ifndef MAX_QUERY_LENGTH
#define MAX_QUERY_LENGTH 1024
#endif

#ifndef MAX_COLUMN_NAME_LENGTH 
#define MAX_COLUMN_NAME_LENGTH 100  // 定义列名的最大长度
#endif

/*/ 数据库连接信息
const char *host = "localhost"; // MySQL主机
const char *user = "xiao";      // MySQL用户名
const char *password = "1125";  // MySQL密码
const char *dbname = "stu";     // MySQL数据库名
*/
// MySQL连接函数
MYSQL *connect_mysql();
// 执行SQL查询
int execute_query(MYSQL *conn, const char *query);
// 检查学生是否存在
int student_exists(MYSQL *conn, int student_id);
// 插入新学生
void insert_student(MYSQL *conn, int student_id, int age, const char *class_name, const char *name);
// 查询指定学号的学生
void select_student_by_id(MYSQL *conn, int student_id);
// 查询指定年级的所有学生
void select_students_by_grade(MYSQL *conn, int grade);
// 查询指定年级和班级的所有学生
void select_students_by_grade_class(MYSQL *conn, int grade, const char *class_name);
// 查看所有学生信息
void select_all_students(MYSQL *conn);
// 更新学生信息
void update_student(MYSQL *conn, int student_id, int age, const char *class_name, const char *name);
// 删除学生信息
void delete_student(MYSQL *conn, int student_id);
// 显示操作菜单
void display_menu();

#endif
