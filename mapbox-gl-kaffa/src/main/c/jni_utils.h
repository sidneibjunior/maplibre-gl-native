#include <jni.h>
#include <string>

namespace Utils {
    std::string jstring2str(jstring, JNIEnv *);
    jbyteArray toJavaByteArray(JNIEnv*, const uint8_t*, int);
}