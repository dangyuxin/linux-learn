#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define BUFSIZE 1024

enum
{
	STATE_R = 1,
	STATE_W,
	STATE_Ex,
	STATE_T
};

struct fsm_t
{
	int state;
	int sfd;
	int dfd;
	char buf[BUFSIZE];
	int len;
	int pos;
};

static void drive(struct fsm_t *fsm)
{
	int ret;
	switch (fsm->state)
	{
	case STATE_R:
		fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
		if (fsm->len == 0)
		{
			fsm->state = STATE_T;
		}
		else if (fsm->len < 0)
		{
			if (errno = EAGAIN)
				fsm->state = STATE_R;
			else
				fsm->state = STATE_Ex;
		}
		else
		{
			fsm->state = STATE_W;
			fsm->pos = 0;
		}
		break;
	case STATE_W:
		ret = write(fsm->dfd, fsm->buf, fsm->len);
		if (fsm->len < 0)
		{
			if (errno = EAGAIN)
				fsm->state = STATE_W;
			else
				fsm->state = STATE_Ex;
		}
		else
		{
			fsm->pos += ret;
			fsm->len -= ret;
			if (fsm->len == 0)
			{
				fsm->state = STATE_R;
			}
			else
			{
				fsm->state = STATE_W;
			}
		}
		break;
	case STATE_Ex:
		break;
	case STATE_T:
		break;
	}
}

static void relay(int fd1, int fd2)
{
	int fd1_save, fd2_save;
	struct fsm_t fsm12, fsm21;
	fcntl(fd1, F_GETFL);
	fcntl(fd1, F_SETFL, fd1_save | O_NONBLOCK);

	fcntl(fd2, F_GETFL);
	fcntl(fd2, F_SETFL, fd2_save | O_NONBLOCK);

	fsm12.state = STATE_R;
	fsm12.sfd = fd1;
	fsm12.dfd = fd2;

	fsm21.state = STATE_R;
	fsm21.sfd = fd2;
	fsm21.dfd = fd1;

	while (fsm12.state != STATE_T || fsm21.state != STATE_T)
	{
		drive(&fsm12);
		drive(&fsm21);
	}

	fcntl(fd1, F_SETFL, fd1_save);
	fcntl(fd2, F_SETFL, fd2_save);
}

int main()
{
	int fd1, fd2;
	fd1 = open(TTY1, O_RDWR);
	if (fd1 < 0)
	{
		perror("open(fd1)");
		exit(1);
	}
	fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
	if (fd2 < 0)
	{
		perror("open(fd2)");
		exit(1);
	}
	write(fd1, "tty1\n", 5);
	write(fd2, "tty2\n", 5);
	relay(fd1, fd2);
	close(fd1);
	close(fd2);
	exit(0);
}
