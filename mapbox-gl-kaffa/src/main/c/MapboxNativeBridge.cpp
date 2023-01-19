#include <stdio.h>
#include "MapboxNativeBridge.h"

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_exportImage(JNIEnv *env, jobject obj, jstring styleUrl, jstring outputFileName) {
    printf("Hello World!\n");
    return;
}