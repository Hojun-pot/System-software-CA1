#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <signal.h>
#include <time.h>

#define RUNNING_DIR "/tmp"
#define LOCK_FILE   "exampled.lock"
#define LOG_FILE    "exampled.log"

void log_message(filename, message)
char *filename;
char *message;
{
    FILE *logfile;
    logfile = fopen(filename, "a");
    if (!logfile) return;
    fprintf(logfile, "%s\n", message);
    fclose(logfile);
}

void daemonize()
{
    int i;
    if (getppid() == 1) return; // already a daemon
    i = fork();
    if (i < 0) exit(1); // fork error
    if (i > 0) exit(0); // parent exits
    // child (daemon) continues
    setsid(); // obtain a new process group
    for (i = getdtablesize(); i >= 0; --i) close(i); // close all descriptors
    i = open("/dev/null", O_RDWR); dup(i); dup(i); // handle standard I/O
    umask(027); // set newly created file permissions
    chdir(RUNNING_DIR); // change running directory
    // lockfile and logging
    log_message(LOG_FILE, "Daemon started.");
}

int main()
{
    daemonize();
    while (1) {
        // Daemon code here.
        // 예: XML 보고서 체크, 로깅, 백업 및 전송 요청 처리 등
        sleep(1); // 1초 대기
    }
    return 0;
}
