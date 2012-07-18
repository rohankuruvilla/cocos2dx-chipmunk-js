LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsbindings

LOCAL_SRC_FILES := ScriptingCore.cpp \
                   cocos2d_generated.cpp \
                   cocos2d_manual_bindings.cpp \
                   cocos_denshion_generated.cpp \
		   js_bindings_chipmunk_manual.cpp \
		   js_bindings_chipmunk_functions.cpp \
		   js_manual_conversions.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static spidermonkey_static chipmunk_static

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)

$(call import-module, android)
$(call import-module, chipmunk)