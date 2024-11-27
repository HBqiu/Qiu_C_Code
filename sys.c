#include <stdio.h>
#include <windows.h>

#define MAX 3

typedef struct {
    int cmd;
    wchar_t *Loc;
} CMD;

CMD cmds[MAX] = {
    {
        1,
        L"C:\\Program Files (x86)\\Tencent\\WeChat\\WeChat.exe"
    },
    {
        2,
        L"D:\\qq\\Bin\\QQScLauncher.exe"
    },
    {
        3,
        L"D:\\酷狗音乐\\KGMusic\\KuGou.exe"
    }
};

int main(int argc, wchar_t *argv[]) {
    if (argc != 2) {
        wprintf(L"Usage: <1 - %d>\n", MAX);
    } else {
        int cmd = _wtoi(argv[1]);
        for (size_t i = 0; i < MAX; i++) {
            if (cmd == cmds[i].cmd) {
                HINSTANCE result = ShellExecuteW(NULL, L"open", cmds[i].Loc, NULL, NULL, SW_HIDE);
                if ((INT_PTR)result <= 32) {
                    wprintf(L"无法执行程序，错误代码: %ld\n", (LONG)(INT_PTR)result);
                }
                return 0;
            }
        }
        wprintf(L"参数有误\n");
    }
    return 0;
}
