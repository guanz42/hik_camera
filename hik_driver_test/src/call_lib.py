# -*- coding: utf-8 -*-
import logging
from ctypes import cdll, c_char_p, c_int, c_short

__author__ = 'gz'

nvr_info = {
    "nvr_ip": "172.16.10.85",
    "nvr_port": 8000,
    "nvr_user": "admin",
    "nvr_pass": "test1234"
}

capture_info = {
    "channel": 1,
    "jpg_quality": 0,
    "jpg_size": 0,
}


class Camera(object):
    def __init__(self) -> None:
        # 初始化动态库
        try:
            lib_path = '/home/gz/work/hik/hik_driver_test/lib/libhikdriver.so'
            print(lib_path)
            lib = cdll.LoadLibrary(lib_path)
            self.init_func = lib.init
            self.login_func = lib.login
            self.capture_func = lib.capture
            self.logout_func = lib.logout
            self.cleanup_func = lib.cleanup

            self._user_id = None

        except Exception as e:
            logging.error("Init Lib Func err = {}".format(e))
            return

    def do_init(self):
        self.init_func.restype = c_int
        return self.init_func()

    def do_cleanup(self):
        return self.cleanup_func()

    def do_login(self):
        # 登录NVR
        try:
            p_nvr_ip = c_char_p(str(nvr_info["nvr_ip"]).encode())
            p_nvr_user = c_char_p(str(nvr_info["nvr_user"]).encode())
            p_nvr_pass = c_char_p(str(nvr_info["nvr_pass"]).encode())
            p_nvr_port = c_short(nvr_info["nvr_port"])

            self.login_func.restype = c_int
            self.login_func.argtypes = [c_char_p, c_short, c_char_p, c_char_p]
            self._user_id = self.login_func(p_nvr_ip, p_nvr_port, p_nvr_user, p_nvr_pass)
            return True
        except Exception as e:
            logging.error("NVR login error! err = {}".format(e))
            return False

    def do_logout(self):
        try:
            self.logout_func.restype = c_int
            self.logout_func.argtypes = [c_int]
            return self.logout_func(self._user_id)
        except Exception as e:
            logging.error("logout fail! err = {}".format(e))

    def do_capture(self, path):
        try:
            if self._user_id is None or self._user_id < 0:
                logging.error(f'invalid userid: {self._user_id}')
                return False

            p_cap_channel = c_int(capture_info["channel"])
            p_cap_jpg_quality = c_short(capture_info["jpg_quality"])
            p_cap_jpg_size = c_short(capture_info["jpg_size"])
            p_cap_pic_filename = c_char_p(str(path).encode())
            p_cap_userid = c_int(self._user_id)

            self.capture_func.restype = c_int
            self.capture_func.argtypes = [c_int, c_int, c_short, c_short, c_char_p]
            ret = self.capture_func(p_cap_userid, p_cap_channel, p_cap_jpg_quality, p_cap_jpg_size, p_cap_pic_filename)
            logging.info(f'do_capture [{path}] ret: {ret}')

            if ret == 0:
                return True
            else:
                return False

        except Exception as e:
            logging.error("capture fail! err = {}".format(e))
            return False


def foo():
    cam = Camera()
    print(f'init>>>{cam.do_init()}')
    print(f'login>>>{cam.do_login()}')
    print(f'capture>>>{cam.do_capture("./test.jpg")}')
    print(f'logout>>>{cam.do_logout()}')
    print(f'cleanup>>>{cam.do_cleanup()}')


if __name__ == '__main__':
    foo()
