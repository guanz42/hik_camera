
//#include <malloc.h>
//#include <cstring>
#include "../include/hik/hik_driver.h"

void printError() {
    int errNo = getLastError();
    char errMsg[128] = {0};
    snprintf(errMsg, sizeof(errMsg), "%s", getErrorMsg(&errNo));
    printf("ERROR[%d]: %s\n", errNo, errMsg);
}

int main() {
    int ret = 0;

    init();

//    setLogToFile(0, "./logs");

    int userId;
//    int idx;
//    for (idx = 50; idx < 101; idx++) {
//        char test_ip[15] = {0};
//        snprintf(test_ip, sizeof(test_ip), "172.16.10.%d", idx);
//
//        int len = strlen(test_ip);
//        char *ip = (char *) malloc(len * sizeof(char));
//        memcpy(ip, test_ip, len);
//        printf("test ip = [%s]\n", ip);
//        userId = login(ip, 8000, "admin", "test1234");
//        if (userId >= 0) {
//            break;
//        }
//
//    }

    userId = login("172.16.10.85", 8000, "admin", "test1234");
    printf("userId = %d\n", userId);
    if (userId < 0) {
        printError();
        cleanup();
        return -1;
    }

    ret = capture(userId, 1, 0, 0, "./hik.jpg");
    printf("capture = %d\n", ret);
    if (!ret) {
        printError();
        return -1;
    }

    ret = logout(userId);
    printf("logout = %d\n", ret);
    if (!ret) {
        printError();
        return -1;
    }

    ret = cleanup();
    printf("cleanup = %d\n", ret);
    if (!ret) {
        printError();
        return -1;
    }

    return 0;
}
