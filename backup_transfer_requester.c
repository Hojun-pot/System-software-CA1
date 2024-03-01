#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        // 백업 및 전송 작업 실행
        printf("Received SIGUSR1, initiating backup and transfer...\n");
        // 실제 백업 및 전송 로직을 여기에 구현
    }
}

int main() {
    // 시그널 핸들러 설정
    signal(SIGUSR1, handle_signal);

    // 데몬의 메인 루프
    while (1) {
        pause(); // 시그널을 기다림
    }

    return 0;
}

//kill -SIGUSR1 1234 (change 1234 to your proccess ID)

