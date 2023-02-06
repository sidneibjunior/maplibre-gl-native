#include <jni.h>
#ifndef _Included_NativeSample
#define _Included_NativeSample
#ifdef __cplusplus
extern "C"
{
#endif

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_initializeN(JNIEnv *, jobject, jint, jint, jdouble, jdouble, jdouble, jstring, jstring);

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_destroyN(JNIEnv *, jobject);

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_jumpToN(JNIEnv *, jobject, jdouble, jdouble, jdouble);

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_setSizeN(JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif