#include <stdio.h>
#include "MapboxNativeBridge.h"
#include <string>
#include <iostream>

using namespace std;

class MyClass {       // The class

  public:             // Access specifier
    int myNum;        // Attribute (int variable)
    string myString;  // Attribute (string variable)
};

jfieldID getMapPtrField(JNIEnv * env, jobject obj) {
    static jfieldID mapFieldId = 0;
    if (!mapFieldId) {
        jclass c = env->GetObjectClass(obj);
        mapFieldId = env->GetFieldID(c, "mapPtr", "J");
        env->DeleteLocalRef(c);
    }
    return mapFieldId;
}

void setMapPtr(JNIEnv *env, jobject obj, MyClass *myObj) {
    env->SetLongField(obj, getMapPtrField(env, obj), (jlong) myObj);
}

MyClass* getMapObj(JNIEnv *env, jobject obj) {
    return (MyClass*) env->GetLongField(obj, getMapPtrField(env, obj));
}

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_initialize(JNIEnv *env, jobject obj, jint width, jint height, jdouble lat, jdouble lng, jdouble zoom, jstring styleUrl) {
    MyClass *myObj = new MyClass();
    myObj->myNum = 15;
    myObj->myString = "Some text";
    setMapPtr(env, obj, myObj);
    return;
}

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_destroy(JNIEnv *env, jobject obj) {
    MyClass* myObj = getMapObj(env, obj);
    delete myObj;
    return;
}

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_jumpTo(JNIEnv *env, jobject obj, jdouble lat, jdouble lng, jdouble zoom) {
    MyClass* myObj = getMapObj(env, obj);
    cout << "\n\nmyObj (*): " << myObj << "\n";
    cout << "myObj->myNum: " << myObj->myNum << "\n";
    return;
}

JNIEXPORT void JNICALL Java_kaffa_e3_mapbox_MapboxNativeBridge_setSize(JNIEnv *env, jobject obj, jint width, jint height) {
    return;
}