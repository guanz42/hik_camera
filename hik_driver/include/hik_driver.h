
#ifndef HIK_DRIVER_H_
#define HIK_DRIVER_H_ (1)

#include <stdio.h>
#include "HCNetSDK.h"

#ifdef __cplusplus
extern "C" {
#endif

int init();

int cleanup();

int login(char *ip, unsigned short port, char *user, char *pwd);

int logout(int userId);

int capture(int userId, int channel, unsigned short size, unsigned short quality, char *filename);

unsigned int getLastError();

char *getErrorMsg(int *errNo);

//int setLogToFile(int level, char *logDir);

#ifdef __cplusplus
}
#endif

#endif
