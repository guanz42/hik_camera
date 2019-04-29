
#include "../include/hik_driver.h"

int init() {
    return NET_DVR_Init();
}

int cleanup() {
    return NET_DVR_Cleanup();
}

int login(char *ip, unsigned short port, char *user, char *pwd) {
    NET_DVR_USER_LOGIN_INFO sLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 sDeviceInfo = {0};

    snprintf(sLoginInfo.sDeviceAddress, sizeof(sLoginInfo.sDeviceAddress), "%s", ip);
    sLoginInfo.wPort = port;
    snprintf(sLoginInfo.sUserName, sizeof(sLoginInfo.sUserName), "%s", user);
    snprintf(sLoginInfo.sPassword, sizeof(sLoginInfo.sPassword), "%s", pwd);

    return NET_DVR_Login_V40(&sLoginInfo, &sDeviceInfo);
}

int logout(int userId) {
    return NET_DVR_Logout_V30(userId);
}

int capture(int userId, int channel, unsigned short size, unsigned short quality, char *filename) {
    NET_DVR_JPEGPARA sPara = {0};
    sPara.wPicSize = size;
    sPara.wPicQuality = quality;

    return NET_DVR_CaptureJPEGPicture(userId, channel, &sPara, filename);
}

unsigned int getLastError() {
    return NET_DVR_GetLastError();
}

char *getErrorMsg(int *errNo) {
    return NET_DVR_GetErrorMsg(errNo);
}

//int setLogToFile(int level, char *logDir) {
//    return NET_DVR_SetLogToFile(level, logDir);
//}
