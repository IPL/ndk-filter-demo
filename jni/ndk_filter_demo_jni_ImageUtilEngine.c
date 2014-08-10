#include <stdlib.h>
#include "ndk_filter_demo_jni_ImageUtilEngine.h"

#include <android/log.h>
#include <android/bitmap.h>
#include <math.h>
#define LOG_TAG "ImageUtil"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JNIEXPORT jstring JNICALL Java_ndk_filter_demo_jni_ImageUtilEngine_getResultFromJni(
		JNIEnv* env, jobject thiz) {
	return (*env)->NewStringUTF(env, "ArtFilter from JNI !!!");
}

int min(int x, int y) {
    return (x <= y) ? x : y;
}
int max(int x,int y){
	return (x >= y) ? x : y;
}
int alpha(int color) {
    return (color >> 24) & 0xFF;
}
int red(int color) {
    return (color >> 16) & 0xFF;
}
int green(int color) {
    return (color >> 8) & 0xFF;
}
int blue(int color) {
    return color & 0xFF;
}
int ARGB(int alpha, int red, int green, int blue) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toGray(JNIEnv* env,
		jobject thiz, jintArray buf, jint width, jint height)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);

	int newSize = width * height;
	jint rbuf[newSize];

	int count = 0;
	int preColor = 0;
	int prepreColor = 0;
	int color = 0;
	preColor = cbuf[0];

	int i = 0;
	int j = 0;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			int curr_color = cbuf[j * width + i];
			int r = red(curr_color);
			int g = green(curr_color);
			int b = blue(curr_color);
			int modif_color = (int)(r * 0.3 + g * 0.59 + b * 0.11);
			rbuf[j * width + i] = ARGB(alpha(curr_color),modif_color,modif_color,modif_color);
		}
	}
	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toSculpture(JNIEnv* env,
		jobject thiz, jintArray buf, jint width, jint height)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);
	//jintArray result = (*env)->NewIntArray(env, width * height);
	LOGE("Bitmap Buffer %d %d",cbuf[0],cbuf[1]);

	int newSize = width * height;
	jint rbuf[newSize];

	int count = 0;
	int preColor = 0;
	int prepreColor = 0;
	int color = 0;
	preColor = cbuf[0];

	int i = 0;
	int j = 0;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			int curr_color = cbuf[j * width + i];
			int r = red(curr_color) - red(prepreColor) + 128;
			int g = green(curr_color) - red(prepreColor) + 128;
			int b = green(curr_color) - blue(prepreColor) + 128;
			int a = alpha(curr_color);

			int newcolor = (int)(r * 0.3 + g * 0.59 + b * 0.11);

			int modif_color = ARGB(a, newcolor, newcolor, newcolor);
			rbuf[j * width + i] = modif_color;
			prepreColor = preColor;
			preColor = curr_color;
		}
	}
	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toBlackWhite
  (JNIEnv* env,jobject thiz, jintArray buf, jint width, jint height)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);

	int newSize = width * height;
	jint rbuf[newSize];

	int count = 0;
	int preColor = 0;
	int prepreColor = 0;
	int color = 0;
	preColor = cbuf[0];

	int i = 0;
	int j = 0;
	int iPixel = 0;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			int curr_color = cbuf[j * width + i];

			int avg = (red(curr_color)*0.3 + green(curr_color)*0.11 + blue(curr_color)*0.59);
			int modif_color = ARGB(255, avg, avg, avg);
			rbuf[j * width + i] = modif_color;
		}
	}
	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toBlur
  (JNIEnv* env,jobject thiz, jintArray buf, jint width, jint height,jint blur)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);

	int newSize = width * height;
	jint rbuf[newSize];

	int pixColor = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;

	int newColor = 0;

	int i = 1;
	int j = 1;
	int times = 0;
	for(;times<blur;times++)
	for (i = 1; i < width - 1; i++)
	{
		for (j = 1; j < height - 1; j++)
		{
			newR = 0;
			newG = 0;
			newB = 0;
			int m = 0;
			for (; m < 9; m++)
			{
				int s = 0;
				int p = 0;
				switch (m)
				{
				case 0:
					s = i - 1;
					p = j - 1;
					break;
				case 1:
					s = i;
					p = j - 1;
					break;
				case 2:
					s = i + 1;
					p = j - 1;
					break;
				case 3:
					s = i + 1;
					p = j;
					break;
				case 4:
					s = i + 1;
					p = j + 1;
					break;
				case 5:
					s = i;
					p = j + 1;
					break;
				case 6:
					s = i - 1;
					p = j + 1;
					break;
				case 7:
					s = i - 1;
					p = j;
					break;
				case 8:
					s = i;
					p = j;
				}
				pixColor = cbuf[p * width + s];
				newR += red(pixColor);
				newG += green(pixColor);
				newB += blue(pixColor);
			}

			newR = (int) (newR / 9.0);
			newG = (int) (newG / 9.0);
			newB = (int) (newB / 9.0);

			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));

			newColor = ARGB(255, newR, newG, newB);
			rbuf[j * width + i] = newColor;
		}
	}

	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toNegative
  (JNIEnv* env,jobject thiz, jintArray buf, jint width, jint height)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);
	LOGE("Bitmap Buffer %d %d",cbuf[0],cbuf[1]);

	int newSize = width * height;
	jint rbuf[newSize];

	int count = 0;
	int preColor = 0;
	int prepreColor = 0;
	int color = 0;
	preColor = cbuf[0];

	int i = 0;
	int j = 0;
	int iPixel = 0;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			int curr_color = cbuf[j * width + i];

			int r = 255 - red(curr_color);
			int g = 255 - green(curr_color);
			int b = 255 - blue(curr_color);
			int a = alpha(curr_color);
			int modif_color = ARGB(a, r, g, b);
			rbuf[j * width + i] = modif_color;
		}
	}
	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toMultiply
  (JNIEnv* env,jobject thiz, jintArray buf, jintArray mergeArray, jint width, jint height, int type)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);
	LOGE("Bitmap Buffer %d %d",cbuf[0],cbuf[1]);

	jint * cmerge;
	cmerge = (*env)->GetIntArrayElements(env, mergeArray, 0);
	LOGE("Bitmap Buffer %d %d",cbuf[0],cbuf[1]);

	int newSize = width * height;
	jint rbuf[newSize];

	int count = 0;
	int preColor = 0;
	int prepreColor = 0;
	int color = 0;
	preColor = cbuf[0];

	int i = 0;
	int j = 0;
	int iPixel = 0;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			int curr_color = cbuf[j * width + i];
			int merge_color = cmerge[j * width + i];

			int r = 0, g = 0, b = 0;
			int r1 = red(curr_color);
			int g1 = green(curr_color);
			int b1 = blue(curr_color);
			int a1 = alpha(curr_color);
			
			int r2 = red(merge_color);
			int g2 = green(merge_color);
			int b2 = blue(merge_color);
			int a2 = alpha(merge_color);
			
			if (type == 3){ //Multipy
				r  = r1*r2/255;
				g  = g1*g2/255;
				b  = b1*b2/255;
			} else if (type == 4) {//Overlay
				// Overlay
				// Overlay combines Multiply and Screen blend modes. Light parts of the picture become lighter and dark parts become darker. An overlay with the same picture looks like an S-curve.
				// Formula: Result Color = if (Bottom Color < 128) 
				//                         then (2 * Top Color * Bottom Color / 255) 
				//                         else (255 - 2 * (255 - Top Color) * (255 - Bottom Color) / 255)
			    r = (r1 < 0x80) ? (((2 * r2) * r1) / 255) : (255 - (((2 * (255 - r2)) * (255 - r1)) / 255));
		        g = (g1 < 0x80) ? (((2 * g2) * g1) / 255) : (255 - (((2 * (255 - g2)) * (255 - g1)) / 255));
		        b = (b1 < 0x80) ? (((2 * b2) * b1) / 255) : (255 - (((2 * (255 - b2)) * (255 - b1)) / 255));
			} else if (type == 5) {//ColorDodge
			    r = (r1 << 8) / (255 - ((r2 != 255) ? r2 : 0xfe));
		        g = (g1 << 8) / (255 - ((g2 != 255) ? g2 : 0xfe));
		        b = (b1 << 8) / (255 - ((b2 != 255) ? b2 : 0xfe));
		        r = (r2 == 255) ? r2 : ((r < 255) ? r : 255);
		        g = (g2 == 255) ? g2 : ((g < 255) ? g : 255);
		        b = (b2 == 255) ? b2 : ((b < 255) ? b : 255);
			} else if (type == 6){//ColorBurn
				r = 255 - (((255 - r1) << 8) / ((r2 != 0) ? r2 : 1));
		        g = 255 - (((255 - g1) << 8) / ((g2 != 0) ? g2 : 1));
		        b = 255 - (((255 - b1) << 8) / ((b2 != 0) ? b2 : 1));
		        r = (r2 == 0) ? r2 : ((r > 0) ? r : 0);
		        g = (g2 == 0) ? g2 : ((g > 0) ? g : 0);
		        b = (b2 == 0) ? b2 : ((b > 0) ? b : 0);
			} else if (type == 7){//Lighten
				r = (r2 > r1) ? r2 : r1;
		        g = (g2 > g1) ? g2 : g1;
		        b = (b2 > b1) ? b2 : b1;
			}
			
			int modif_color = ARGB(a1, r, g, b);
			rbuf[j * width + i] = modif_color;
		}
	}
	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	(*env)->ReleaseIntArrayElements(env, buf, cmerge, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toSunshine
  (JNIEnv* env,jobject thiz, jintArray buf, jint width, jint height,jint centerX, jint centerY, jint radius, jint strength)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);

	int newSize = width * height;
	jint rbuf[newSize];

	radius = min(centerX, centerY);

	int i = 0;
	int j = 0;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			int curr_color = cbuf[j * width + i];

			int pixR = red(curr_color);
			int pixG = green(curr_color);
			int pixB = blue(curr_color);

			int newR = pixR;
			int newG = pixG;
			int newB = pixB;
			int distance = (int) ((centerY - i) * (centerY - i) + (centerX - j) * (centerX - j));
			if (distance < radius * radius)
			{
				int result = (int) (strength * (1.0 - sqrt(distance) / radius));
				newR = pixR + result;
				newG = pixG + result;
				newB = pixB + result;
			}
			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));

			int a = alpha(curr_color);
			int modif_color = ARGB(a, newR, newG, newB);
			rbuf[j * width + i] = modif_color;
		}
	}
	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toMagnifier
  (JNIEnv* env,jobject thiz, jintArray buf, jint width, jint height,jint centerX, jint centerY, jint radius, jfloat multiple)
{
	jint * cbuf;
	cbuf = (*env)->GetIntArrayElements(env, buf, 0);

	int newSize = width * height;
	jint rbuf[newSize];

	float ratio = multiple;
	int real_radius = (int)(radius / ratio);

	int i = 0, j = 0;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			int curr_color = cbuf[j * width + i];

			int pixR = red(curr_color);
			int pixG = green(curr_color);
			int pixB = blue(curr_color);
			int pixA = alpha(curr_color);

			int newR = pixR;
			int newG = pixG;
			int newB = pixB;
			int newA = pixA;

			int distance = (int) ((centerX - i) * (centerX - i) + (centerY - j) * (centerY - j));
			if (distance < radius * radius)
			{
				int src_x = (int)((float)(i - centerX) / ratio + centerX);
				int src_y = (int)((float)(j - centerY) / ratio + centerY);

				int src_color = cbuf[src_y * width + src_x];
				newR = red(src_color);
				newG = green(src_color);
				newB = blue(src_color);
				newA = alpha(src_color);
			}

			newR = min(255, max(0, newR));
			newG = min(255, max(0, newG));
			newB = min(255, max(0, newB));
			newA = min(255, max(0, newA));

			int modif_color = ARGB(newA, newR, newG, newB);
			rbuf[j * width + i] = modif_color;
		}
	}

	jintArray result = (*env)->NewIntArray(env, newSize);
	(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
	(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
	return result;
}

jintArray Java_ndk_filter_demo_jni_ImageUtilEngine_toMagicMirror
  (JNIEnv* env,jobject thiz, jintArray buf, jint width, jint height,jint centerX, jint centerY, jint radius, jfloat multiple)
{
	jint * cbuf;
		cbuf = (*env)->GetIntArrayElements(env, buf, 0);

		int newSize = width * height;
		jint rbuf[newSize];

		float ratio = multiple;
		int real_radius = (int)(radius / ratio);

		int i = 0, j = 0;
		for (i = 0; i < width; i++)
		{
			for (j = 0; j < height; j++)
			{
				int curr_color = cbuf[j * width + i];

				int pixR = red(curr_color);
				int pixG = green(curr_color);
				int pixB = blue(curr_color);
				int pixA = alpha(curr_color);

				int newR = pixR;
				int newG = pixG;
				int newB = pixB;
				int newA = pixA;

				int distance = (int) ((centerX - i) * (centerX - i) + (centerY - j) * (centerY - j));
				if (distance < radius * radius)
				{
					int src_x = (int) ((float) (i - centerX) / ratio);
					int src_y = (int) ((float) (j - centerY) / ratio);
					src_x = (int)(src_x * (sqrt(distance) / real_radius));
					src_y = (int)(src_y * (sqrt(distance) / real_radius));
					src_x = src_x + centerX;
					src_y = src_y + centerY;

					int src_color = cbuf[src_y * width + src_x];
					newR = red(src_color);
					newG = green(src_color);
					newB = blue(src_color);
					newA = alpha(src_color);
				}

				newR = min(255, max(0, newR));
				newG = min(255, max(0, newG));
				newB = min(255, max(0, newB));
				newA = min(255, max(0, newA));

				int modif_color = ARGB(newA, newR, newG, newB);
				rbuf[j * width + i] = modif_color;
			}
		}

		jintArray result = (*env)->NewIntArray(env, newSize);
		(*env)->SetIntArrayRegion(env, result, 0, newSize, rbuf);
		(*env)->ReleaseIntArrayElements(env, buf, cbuf, 0);
		return result;
}
