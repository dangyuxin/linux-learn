#include <contact.h>
void InitContact(struct Contact *ps)
{
    memset(ps->date, 0, sizeof(ps->date));
    ps->size = 0;
}