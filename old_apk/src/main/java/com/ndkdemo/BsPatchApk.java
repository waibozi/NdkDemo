package com.ndkdemo;

/**
 * Created by liupei on 2017/8/11.
 * 增量更新
 */

public class BsPatchApk {
    static {
        System.loadLibrary("bspatch");
    }

    /**
     * @param oldPath   旧APK路径
     * @param newPath   合并后的新apk路径
     * @param patchPath 差分文件路径
     * @return
     */
    public native static String BsPatch(String oldPath, String newPath, String patchPath);
}
