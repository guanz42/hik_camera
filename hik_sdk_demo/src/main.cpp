
#include <cstdio>
#include <cstring>
#include "HCNetSDK.h"

int main() {
    long userId;

    NET_DVR_Init();

    NET_DVR_USER_LOGIN_INFO stuLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 stuDeviceInfoV40 = {0};

    stuLoginInfo.wPort = 8000;
    memcpy(stuLoginInfo.sDeviceAddress, "172.16.10.85", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(stuLoginInfo.sUserName, "admin", NET_DVR_LOGIN_USERNAME_MAX_LEN);
    memcpy(stuLoginInfo.sPassword, "test1234", NET_DVR_LOGIN_PASSWD_MAX_LEN);

    userId = NET_DVR_Login_V40(&stuLoginInfo, &stuDeviceInfoV40);
    if (userId < 0) {
        printf("login failed\n");
        return -1;
    }

    int ret;

    NET_DVR_JPEGPARA stuPara = {0};
    stuPara.wPicQuality = 0;
    stuPara.wPicSize = 0;
    ret = NET_DVR_CaptureJPEGPicture(userId, stuDeviceInfoV40.struDeviceV30.byStartChan, &stuPara, "./ttt.jpg");
    if (!ret) {
        printf("capture failed, %d\n", ret);

        int errNo;
        errNo = NET_DVR_GetLastError();
        printf("ERROR[%d]: %s\n", errNo, NET_DVR_GetErrorMsg(&errNo));
        return -1;
    }

    NET_DVR_Logout(userId);

    NET_DVR_Cleanup();

    return 0;
}
