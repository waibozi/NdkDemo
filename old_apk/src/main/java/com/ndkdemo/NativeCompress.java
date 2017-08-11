package com.ndkdemo;

import android.graphics.Bitmap;

/**
 * Created by liupei on 2017/8/10.
 * jpeg图片压缩
 */

public class NativeCompress {

    static {
        System.loadLibrary("compress");
    }

    /**
     * @param bitmap  需要处理的图片
     * @param outPath 压缩图片输出目录
     * @param quality 压缩质量，越小压缩率越高
     */
    public native static void ImageCompress(Bitmap bitmap, int quality, String outPath);
}
