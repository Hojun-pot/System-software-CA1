#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void move_files(const char* sourceDir, const char* destDir) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(sourceDir)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Ensure it's a file
                char sourcePath[256];
                char destPath[256];
                snprintf(sourcePath, sizeof(sourcePath), "%s/%s", sourceDir, ent->d_name);
                snprintf(destPath, sizeof(destPath), "%s/%s", destDir, ent->d_name);
                rename(sourcePath, destPath); // Move file
                printf("Moved: %s -> %s\n", sourcePath, destPath);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}

void check_and_move_files(const char* sourceDir, const char* destDir) {
    while (1) {
        time_t now;
        struct tm newyear;
        double seconds;

        time(&now);  // 현재 시간을 가져옵니다.
        newyear = *localtime(&now);

        // 오전 1시에 파일 이동을 위한 조건 설정
        newyear.tm_hour = 1;
        newyear.tm_min = 0;
        newyear.tm_sec = 0;

        seconds = difftime(now,mktime(&newyear));

        if (seconds > 0 && seconds < 60) { // 오전 1시 정각에 파일 이동
            move_files(sourceDir, destDir);
            sleep(60); // 1분 대기
        }

        sleep(1); // 다음 체크까지 1초 대기
    }
}

int main() {
    const char* sourceDir = "/path/to/source";
    const char* destDir = "/path/to/destination";

    check_and_move_files(sourceDir, destDir);

    return 0;
}
