#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

// 로그 메시지를 파일에 기록하는 함수
void log_message(const char* filename, const char* message) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(file, "%s\n", message);
    fclose(file);
}

void check_upload(const char* dirPath, const char* logFile) {
    DIR* dir;
    struct dirent* ent;
    int found = 0; // 파일 발견 여부 표시

    if ((dir = opendir(dirPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // 여기서 파일 명명 규칙을 확인
            // 예: 파일 이름이 특정 날짜 포맷을 포함하는지 확인
            if (ent->d_type == DT_REG) { // Regular file
                // 파일 명명 규칙에 맞는지 확인
                found = 1; // 이 예에서는 항상 찾았다고 가정
                break;
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }

    if (!found) {
        // 파일이 없으면 로그 파일에 기록
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "No upload found for today in %s", dirPath);
        log_message(logFile, buffer);
    }
}

int main() {
    const char* uploadDir = "/path/to/uploads";
    const char* logFile = "/path/to/logfile.log";

    while (1) {
        // 매일 특정 시간에 실행
        check_upload(uploadDir, logFile);
        sleep(86400); // 다음 날까지 대기 (24시간 * 60분 * 60초)
    }

    return 0;
}
