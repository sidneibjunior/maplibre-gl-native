#include "jni_utils.h"

namespace Utils {
  std::string jstring2str(jstring jStr, JNIEnv *env) {
      if (!jStr)
          return "";

      const jclass stringClass = env->GetObjectClass(jStr);
      const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
      const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

      size_t length = (size_t) env->GetArrayLength(stringJbytes);
      jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

      std::string ret = std::string((char *)pBytes, length);
      env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

      env->DeleteLocalRef(stringJbytes);
      env->DeleteLocalRef(stringClass);
      return ret;
  }

  jbyteArray toJavaByteArray(JNIEnv* env, const uint8_t* bytes, int len) {
    jbyteArray byte_array = env->NewByteArray(len);
    env->SetByteArrayRegion(byte_array, 0, len, reinterpret_cast<const jbyte*>(bytes));
    return byte_array;
  }
}