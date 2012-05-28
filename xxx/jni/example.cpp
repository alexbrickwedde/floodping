#include <jni.h>

extern "C"
{
jstring Java_org_floodping_testjni_TestJNI_test (JNIEnv* env, jobject thiz);
}

jstring Java_org_floodping_testjni_TestJNI_test (JNIEnv* env, jobject thiz)
{
	return env->NewStringUTF("test1");
}
