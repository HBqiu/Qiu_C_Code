#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_DB_NAME_LENGTH 10
#define MAX_TABLE_NAME_LENGTH 20
#define MAX_COLUMN_NAME_LENGTH 20
#define MAX_COLUMNS 5
#define MAX_TABLES 3
#define MAX_DATABASES 3

// 表结构体，用于描述每个表的结构
typedef struct {
    char table_name[MAX_TABLE_NAME_LENGTH];  // 表名
    int column_count;  // 列数
    char column_names[MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH];  // 列名数组
} TableInfo;

// 数据库结构体，用于描述数据库的结构
typedef struct {
    char database_name[MAX_DB_NAME_LENGTH];  // 数据库名
    int table_count;  // 表的数量
    TableInfo tables[MAX_TABLES];  // 表的结构数组
} DatabaseInfo;

// 数据库数组，存储多个数据库
DatabaseInfo databases[MAX_DATABASES];
int database_count = 0;

// 创建数据库信息
void create_database_info(DatabaseInfo *db_info, const char *database_name, int table_count, ...) {
    va_list args;
    va_start(args, table_count);

    // 设置数据库名
    strncpy(db_info->database_name, database_name, MAX_DB_NAME_LENGTH);
    db_info->table_count = table_count;

    // 创建每个表的信息
    for (int i = 0; i < table_count; i++) {
        // 获取每个表的名称
        const char *table_name = va_arg(args, const char*);
        int column_count = va_arg(args, int);  // 每个表的列数
        TableInfo *table_info = &db_info->tables[i];
        strncpy(table_info->table_name, table_name, MAX_TABLE_NAME_LENGTH);
        table_info->column_count = column_count;

        // 获取每一列的列名
        for (int j = 0; j < column_count; j++) {
            const char *column_name = va_arg(args, const char*);
            strncpy(table_info->column_names[j], column_name, MAX_COLUMN_NAME_LENGTH);
        }
    }

    va_end(args);
}

// 打印数据库的结构信息
void print_database_info(const DatabaseInfo *db_info) {
    printf("数据库名称: %s\n", db_info->database_name);
    printf("表数量: %d\n", db_info->table_count);

    for (int i = 0; i < db_info->table_count; i++) {
        const TableInfo *table_info = &db_info->tables[i];
        printf("  表名: %s\n", table_info->table_name);
        printf("  列数: %d\n", table_info->column_count);
        printf("  列名: ");
        for (int j = 0; j < table_info->column_count; j++) {
            printf("%s ", table_info->column_names[j]);
        }
        printf("\n");
    }
}

// 打印所有数据库的信息
void print_all_databases_info() {
    for (int i = 0; i < database_count; i++) {
        print_database_info(&databases[i]);
    }
}

int main() {
    // 创建第一个数据库信息
    DatabaseInfo db_info1;
    create_database_info(&db_info1, "user", 1,
                         "userpass", 4, "username", "password", "salt",
                         "root", 2);
    databases[database_count++] = db_info1;  // 将第一个数据库添加到数据库数组中

    // 创建第二个数据库信息
    DatabaseInfo db_info2;
    create_database_info(&db_info2, "stu", 1,
                         "student", 4, "student_id", "age", "class", "anme");
    databases[database_count++] = db_info2;  // 将第二个数据库添加到数据库数组中

    // 打印所有数据库的结构信息
    print_all_databases_info();

    return 0;
}

