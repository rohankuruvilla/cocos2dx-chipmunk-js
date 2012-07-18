LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_LDLIBS := -landroid

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \

                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
	   	    $(LOCAL_PATH)/ \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += jsbindings


            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx) $(call import-module,android) $(call import-module, jsbindings)
