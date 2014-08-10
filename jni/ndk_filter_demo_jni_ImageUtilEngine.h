/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ndk_filter_demo_jni_ImageUtilEngine */

#ifndef _Included_ndk_filter_demo_jni_ImageUtilEngine
#define _Included_ndk_filter_demo_jni_ImageUtilEngine
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    getResultFromJni
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_getResultFromJni
  (JNIEnv *, jobject);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toGray
 * Signature: ([III)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toGray
  (JNIEnv *, jobject, jintArray, jint, jint);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toSculpture
 * Signature: ([III)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toSculpture
  (JNIEnv *, jobject, jintArray, jint, jint);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toBlackWhite
 * Signature: ([III)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toBlackWhite
  (JNIEnv *, jobject, jintArray, jint, jint);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toBlur
 * Signature: ([IIII)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toBlur
  (JNIEnv *, jobject, jintArray, jint, jint, jint);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toNegative
 * Signature: ([III)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toNegative
  (JNIEnv *, jobject, jintArray, jint, jint);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toSunshine
 * Signature: ([IIIIIII)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toSunshine
  (JNIEnv *, jobject, jintArray, jint, jint, jint, jint, jint, jint);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toMagnifier
 * Signature: ([IIIIIIF)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toMagnifier
  (JNIEnv *, jobject, jintArray, jint, jint, jint, jint, jint, jfloat);

/*
 * Class:     ndk_filter_demo_jni_ImageUtilEngine
 * Method:    toMagicMirror
 * Signature: ([IIIIIIF)[I
 */
JNIEXPORT jintArray JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_toMagicMirror
  (JNIEnv *, jobject, jintArray, jint, jint, jint, jint, jint, jfloat);

#ifdef __cplusplus
}
#endif
#endif