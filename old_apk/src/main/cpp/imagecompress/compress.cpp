#include "compress.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <android/log.h>
#include <android/bitmap.h>

extern "C" {
#include "../include/jpeg/jpeglib.h"
}

#define LOGW(...) __android_log_write(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_write(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOG_TAG "jni"
#define true 1
#define false 0

typedef uint8_t BYTE;
char *error;

void writeImage(BYTE *data, const char *path, int quality, int w, int h) {
    struct jpeg_compress_struct jpeg_struct;
    struct jpeg_error_mgr jerr;
    jpeg_struct.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&jpeg_struct);

    jpeg_struct.image_width = w;
    jpeg_struct.image_height = h;

    FILE *outfile = fopen(path, "wb");
    jpeg_stdio_dest(&jpeg_struct, outfile);
    jpeg_struct.in_color_space = JCS_RGB;
    jpeg_struct.input_components = 3;
    jpeg_struct.arith_code = false;
    jpeg_struct.optimize_coding = true;

    jpeg_set_defaults(&jpeg_struct);
    jpeg_struct.optimize_coding = true;
    //设置质量
    jpeg_set_quality(&jpeg_struct, quality, true);

    jpeg_start_compress(&jpeg_struct, true);

    JSAMPROW row_pointer[1];
    int row_stride;
    row_stride = w * 3;
    while (jpeg_struct.next_scanline < jpeg_struct.image_height) {
        row_pointer[0] = &data[jpeg_struct.next_scanline * row_stride];
        jpeg_write_scanlines(&jpeg_struct, row_pointer, 1);
    }
    jpeg_finish_compress(&jpeg_struct);
    jpeg_destroy_compress(&jpeg_struct);
    fclose(outfile);
    LOGW("压缩完成");
}

JNIEXPORT void JNICALL
Java_com_ndkdemo_NativeCompress_ImageCompress(JNIEnv *env, jclass type, jobject bitmap,
                                                  jint quality,
                                                  jstring _path) {
    BYTE *pixel;
    AndroidBitmapInfo androidBitmapInfo;

    AndroidBitmap_getInfo(env, bitmap, &androidBitmapInfo);
    int w = androidBitmapInfo.width;
    int h = androidBitmapInfo.height;

    AndroidBitmap_lockPixels(env, bitmap, (void **) &pixel);
    BYTE *data = (BYTE *) malloc(w * h * 3);
    BYTE r, g, b;
    BYTE *tmpData = data;

    int color;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            //取出像素
            color = *(int *) pixel;
            r = (color >> 16) & 0xFF;
            g = (color >> 8) & 0xFF;
            b = color & 0xFF;

            *data = b;
            *(data + 1) = g;
            *(data + 2) = r;
            data += 3;
            pixel += 4;
        }
    }

    LOGE("RGB解析成功");
    AndroidBitmap_unlockPixels(env, bitmap);

    const char *path = env->GetStringUTFChars(_path, 0);
    writeImage(tmpData, path, quality, w, h);
}


