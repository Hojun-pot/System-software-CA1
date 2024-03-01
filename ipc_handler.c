#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    int must_stop = 0;

    // 메시지 큐 속성 설정
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // 메시지 큐 생성
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == -1) {
        perror("MQ Open");
        exit(1);
    }

    do {
        printf("Enter message: ");
        fflush(stdout);
        memset(buffer, 0, MAX_SIZE); // 버퍼 초기화
        fgets(buffer, MAX_SIZE, stdin);

        // 메시지 전송
        if (mq_send(mq, buffer, MAX_SIZE, 0) == -1) {
            perror("MQ Send");
            continue;
        }

        must_stop = strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0;

    } while (!must_stop);

    // 메시지 큐 닫기
    if (mq_close(mq) == -1) {
        perror("MQ Close");
        exit(2);
    }

    // 메시지 큐 제거
    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("MQ Unlink");
        exit(3);
    }

    return 0;
}

//gcc -o message_sender message_sender.c -lrt
