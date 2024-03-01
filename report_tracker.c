#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void log_change(const char* logFile, const char* file, const char* operation) {
    FILE* log_fp = fopen(logFile, "a");
    if (log_fp == NULL) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

    time_t now;
    time(&now);
    char* time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove newline

    fprintf(log_fp, "%s: %s was %s\n", time_str, file, operation);
    fclose(log_fp);
}

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

void watch_directory(const char* path, const char* logFile) {
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
    }

    int wd = inotify_add_watch(fd, path, IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd == -1) {
        fprintf(stderr, "Cannot watch '%s'\n", path);
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_LEN];
    while (1) {
        int length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < length;) {
            struct inotify_event* event = (struct inotify_event*)&buffer[i];
            if (event->len) {
                if (event->mask & IN_CREATE) {
                    log_change(logFile, event->name, "created");
                } else if (event->mask & IN_MODIFY) {
                    log_change(logFile, event->name, "modified");
                } else if (event->mask & IN_DELETE) {
                    log_change(logFile, event->name, "deleted");
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
}

int main() {
    // XML 파일들이 저장되는 디렉토리와 로그 파일의 경로 설정
    const char* watchPath = "/path/to/xml/reports";
    const char* logFile = "/path/to/logfile.log";

    watch_directory(watchPath, logFile);

    return 0;
}
