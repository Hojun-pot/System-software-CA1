#include <sys/stat.h>
#include <stdio.h>

// 디렉토리의 쓰기 권한 변경
void lock_directory(const char* path, int lock) {
    struct stat st;
    if (stat(path, &st) < 0) {
        perror("Failed to get directory stats");
        return;
    }

    mode_t mode = st.st_mode & 07777; // 현재 모드 가져오기
    if (lock) {
        // 쓰기 권한 제거
        mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
    } else {
        // 쓰기 권한 추가 (원래 권한에 따라 다를 수 있음)
        mode |= (S_IWUSR | S_IWGRP | S_IWOTH);
    }

    if (chmod(path, mode) < 0) {
        perror("chmod failed");
    }
}

int main() {
    const char* directoryPath = "/path/to/directory";

    // 디렉토리 잠금
    lock_directory(directoryPath, 1);
    printf("Directory locked for writing.\n");

    // 여기에서 백업 또는 전송 작업 수행...

    // 디렉토리 잠금 해제
    lock_directory(directoryPath, 0);
    printf("Directory unlocked for writing.\n");

    return 0;
}
