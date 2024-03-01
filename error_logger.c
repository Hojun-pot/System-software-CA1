#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

void log_error(const char* filename, const char* message, ...) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening log file");
        return;
    }

    // 현재 시간을 로그에 추가
    time_t now;
    time(&now);
    char* time_string = ctime(&now);
    time_string[24] = '\0'; // 개행 문자 제거
    fprintf(file, "[%s] ", time_string);

    // 가변 인자를 사용하여 로그 메시지 포맷팅
    va_list args;
    va_start(args, message);
    vfprintf(file, message, args);
    va_end(args);

    fprintf(file, "\n");
    fclose(file);
}

int main() {
    // 로깅 테스트
    log_error("error.log", "This is an error message with a number: %d", 42);

    // 파일 열기 시도
    FILE* file = fopen("nonexistent_file.txt", "r");
    if (file == NULL) {
        log_error("error.log", "Failed to open file: %s", "nonexistent_file.txt");
    } else {
        // 파일 처리 로직
        fclose(file);
    }

    return 0;
}
