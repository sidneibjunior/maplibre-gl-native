#include <jni.h>
#ifndef _Included_NativeSample
#define _Included_NativeSample
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_exportImage(JNIEnv *, jobject, jstring, jstring);
#ifdef __cplusplus
}
#endif
#endif