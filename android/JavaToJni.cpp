#include <jni.h>

#include <stdio.h>
#include <stdlib.h>

#include "NativeLogcat.h"

#undef LOG_TAG
#define LOG_TAG "JavaToJni Jni"

const char *MY_BUILD_VERSION = "JavaToJni 13";

JavaVM* JniGlobalVM;
jobject JniGlobalContext = NULL;

/**
 * Class:     com_skydjn_javatojni_MainActivity
 * Method:    initCamera
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL init(JNIEnv *env, jobject context, jint argc, jstring argv)
{
    LOGD("================>Enter");

    LOGW("Build Version:%s", MY_BUILD_VERSION);

    jsize nativeStringLen = env->GetStringUTFLength(argv);
    const char *nativeString = env->GetStringUTFChars(argv, JNI_FALSE);

    int tmpInt = argc;
    char *tmpStr = (char*)malloc(nativeStringLen + 1);
    if (tmpStr == NULL) {
        LOGE("Error malloc string");
        return -1;
    }
    strncpy(tmpStr, nativeString, nativeStringLen);
    if (JniGlobalVM != NULL) {
        JniGlobalContext = env->NewGlobalRef(context);
        env->DeleteLocalRef(context);
    }
    free(tmpStr);
    tmpStr = NULL;

    env->ReleaseStringUTFChars(argv, nativeString);

    LOGD("Leave================>");
    return 0;
}

/**
 * Class:     com_skydjn_javatojni_MainActivity
 * Method:    destroyCamera
 * Signature: ()I
 */
JNIEXPORT jint JNICALL destroy(JNIEnv *env, jobject context)
{
    LOGD("================>Enter");

    LOGD("Leave================>");
    return 0;
}


/*****************************************************************************/
/* Copy From This Line
/*****************************************************************************/
static JNINativeMethod methods[] = {
        { "init",     "(ILjava/lang/String;)I",    (void*)init },
        { "destroy",  "()I",                       (void*)destroy }
};

/*
 * Register several native methods for one class.
 */
static int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods,
        int numMethods) {
    jclass clazz;

    clazz = env->FindClass(className);
    if (clazz == NULL) {
        LOGE("Native registration unable to find class '%s'", className);
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        LOGE("RegisterNatives failed for '%s'", className);
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static const char *classPathName = "com/djn/javatojni/MainActivity";


/*****************************************************************************/
/* Don't modify contents under this line
/*****************************************************************************/
const char *COMPILE_BUILD_TIME = __DATE__ ", " __TIME__; // ±àÒëÊ±¼ä
/*
 * Register native methods for all classes we know about.
 */
static int registerNatives(JNIEnv* env) {
    if (!registerNativeMethods(env, classPathName, methods, sizeof(methods) / sizeof(methods[0]))) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

typedef union {
    JNIEnv* env;
    void* vEnv;
} UnionJNIEnvToVoid;

/* This function will be call when the library first be loaded */
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    UnionJNIEnvToVoid uEnv;
    JNIEnv* env = NULL;
    LOGI("JNI_OnLoad!");
    LOGI("Build Time:%s ", COMPILE_BUILD_TIME);
    JnitGlobalVM = vm;
    if (vm->GetEnv((void**) &uEnv.vEnv, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed");
        return -1;
    }

    env = uEnv.env;

    if (registerNatives(env) != JNI_TRUE) {
        LOGE("ERROR: registerNatives failed");
        return -1;
    }

    return JNI_VERSION_1_4;
}
/*****************************************************************************/
/* Don't modify contents before this line
/*****************************************************************************/
