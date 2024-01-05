#pragma once
#if ANDROID

#include <jni.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vulkan/vulkan.h>

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

// Symbols used to exchange critical information between OpenComposite and the application
#ifdef __cplusplus
extern "C" {
#endif
extern XrInstanceCreateInfoAndroidKHR* OpenComposite_Android_Create_Info;
extern XrGraphicsBindingOpenGLESAndroidKHR* OpenComposite_Android_GLES_Binding_Info;
#ifdef __cplusplus
};
#endif

#ifdef __cplusplus
extern std::string (*OpenComposite_Android_Load_Input_File)(const char* path);
#endif

/**
 * Poll for OpenXR events. Call this regularly while sleeping.
 */
#ifdef __cplusplus
extern "C" {
#endif
    void OpenComposite_Android_EventPoll();
#ifdef __cplusplus
};
#endif

#endif
