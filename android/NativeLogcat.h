#pragma once

#ifndef NATIVE_LOGCAT_H_
#define NATIVE_LOGCAT_H_

// add "LOCAL_LDLIBS := -llog" to file "Android.mk"
#include <android/log.h>
#include <string.h>

#ifdef LOGV
    #undef LOGV
#endif
#ifdef LOGI
    #undef LOGI
#endif
#ifdef LOGD
    #undef LOGD
#endif
#ifdef LOGW
    #undef LOGW
#endif
#ifdef LOGE
    #undef LOGE
#endif

#ifdef LOG_TAG
    #undef LOG_TAG
#endif
#define LOG_TAG "mylogcat"

// convert long file name to short file name
// "../inc/nativelogcat.h" -> "nativelogcat.h"
#ifdef COMPART
    #undef COMPART
#endif

#ifdef _WIN32
    #define COMPART '\\'
#else
    #define COMPART '/'
#endif

static char* ConvertTOShortFileName(const char* pszFileName)
{
    char *pszPret = const_cast<char *>(pszFileName);
    char *pszNext = NULL;

    if(NULL == pszFileName)
    {
        return NULL;
    }

    if ((pszNext = strrchr(pszPret, COMPART)) != NULL)
    {
        pszPret = pszNext + 1;
    }

    return pszPret;
}



#define LOGV(fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "[%s:%s](%d): " fmt, ConvertTOShortFileName(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG,   LOG_TAG, "[%s:%s](%d): " fmt, ConvertTOShortFileName(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGI(fmt, ...) __android_log_print(ANDROID_LOG_INFO,    LOG_TAG, "[%s:%s](%d): " fmt, ConvertTOShortFileName(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGW(fmt, ...) __android_log_print(ANDROID_LOG_WARN,    LOG_TAG, "[%s:%s](%d): " fmt, ConvertTOShortFileName(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR,   LOG_TAG, "[%s:%s](%d): " fmt, ConvertTOShortFileName(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif // NATIVE_LOGCAT_H_
