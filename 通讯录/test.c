#define MAX 1000
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30
#include <stdio.h>
#include <string.h>

struct PeoInfo
{
    char name[MAX_NAME];
    int age;
    char sex[MAX_SEX];
    char tele[MAX_TELE];
    char addr[MAX_ADDR];
};

struct Contact
{
    struct PeoInfo date[MAX];
    int size;
};

//声明函数
void InitContact(struct Contact *ps);

void menu()
{
    printf("*******************************");
    printf("*****1.add       2.del     ****");
    printf("*****3.search    4.modify  ****");
    printf("*****5. show     6.sort    *****");
    printf("*****0.exit                *****");
    printf("*******************************");
}

void InitContact(struct Contact *ps)
{
    memset(ps->date, 0, sizeof(ps->date));
    ps->size = 0;
}

int main()
{
    struct Contact con;
    InitContact(&con);

    do
    {
        int input = 0;
        int size = 0; //记录通讯录的大小
        menu();
        printf("请输入\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            // Addcontact(con, size);
            break;
        case 0:
            printf("退出通讯录\n");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            printf("选择错误\n");
            break;
        }
    } while (1);
    return 0;
}