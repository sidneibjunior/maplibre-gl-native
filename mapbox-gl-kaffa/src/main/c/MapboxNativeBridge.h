#include <jni.h>
#ifndef _Included_NativeSample
#define _Included_NativeSample
#ifdef __cplusplus
extern "C"
{
#endif

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_initialize(JNIEnv *, jobject, jint, jint, jdouble, jdouble, jdouble, jstring);

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_destroy(JNIEnv *, jobject);

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_jumpTo(JNIEnv *, jobject, jdouble, jdouble, jdouble);

  JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_setSize(JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif