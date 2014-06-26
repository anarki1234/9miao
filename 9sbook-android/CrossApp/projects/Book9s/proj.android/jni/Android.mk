LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ViewController.cpp \
                   ../../Classes/adView.cpp \
                   ../../Classes/BookDB.cpp \
                   ../../Classes/BookIcon.cpp \
                   ../../Classes/MenuCell.cpp \
                   ../../Classes/PageBase.cpp \
                   ../../Classes/PageBookInfo.cpp \
                   ../../Classes/PageBookStorage.cpp \
                   ../../Classes/PageHome.cpp \
                   ../../Classes/PageManager.cpp \
                   ../../Classes/PageMenu.cpp \
                   ../../Classes/PageRank.cpp \
                   ../../Classes/PageReader.cpp \
                   ../../Classes/PageSearch.cpp \
                   ../../Classes/PageSetting.cpp \
                   ../../Classes/utf8.cpp \
                   ../../Classes/sqlite3.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, D:/work/workspace/CrossApp)
$(call import-add-path, D:/work/workspace/CrossApp/cocos2dx/platform/third_party/android/prebuilt)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
