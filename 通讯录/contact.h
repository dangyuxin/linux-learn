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