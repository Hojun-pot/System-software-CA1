#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define LOG_FILE "project_log.txt"
#define ERROR_LOG_FILE "error_log.txt"

// 필요한 기능 구현을 위한 함수 프로토타입 선언
void startDaemon();
void monitorDirectoryChanges();
void backupAndTransferFiles();
void logEvent(const char* event);
void logError(const char* error);

int main() {
    startDaemon();
    monitorDirectoryChanges();
    // 필요한 기본 로직 추가
    return 0;
}

//Function to transfrom main process into the deamon
void startDaemon() {
    //Declare storing a process id
    pid_t pid;
    //Create a proccess
    pid = fork();
    //Error handler
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    //Return success
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    //Set the session leader whith the child process
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }
    //Ignore the signals below
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    //Second fork to detach completely
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    //Set the new file descriptors
    umask(0);
    //Change executing directory
    chdir("/");

    //Closing all the opened filed descripors
    for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close(x);
    }
    // 데몬 구현 로직 추가
}

void monitorDirectoryChanges() {
    // 디렉토리 변경 감지 및 로깅 로직
}

void backupAndTransferFiles() {
    // 파일 백업 및 전송 로직
}

void logEvent(const char* event) {
    // 이벤트 로깅
}

void logError(const char* error) {
    // 에러 로깅
}
