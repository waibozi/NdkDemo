package com.ndkdemo;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private ProgressDialog progressDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * 合并拆分文件
     */
    public void patch(View view) {
        progressDialog = new ProgressDialog(this);
        progressDialog.setMessage("正在合并...");
        progressDialog.show();
        new BSPatchApkThread().start();
    }

    /**
     * 压缩图片
     */
    public void compress(View view) {
        Bitmap bitmap = BitmapFactory.decodeFile(Environment.getExternalStorageDirectory() + File.separator + "big.jpg");
        NativeCompress.ImageCompress(bitmap, 20, Environment.getExternalStorageDirectory() + File.separator + "small.jpg");
    }

    private class BSPatchApkThread extends Thread {
        @Override
        public void run() {
            BsPatchApk.BsPatch(Environment.getExternalStorageDirectory() + File.separator + "old.apk", Environment.getExternalStorageDirectory() + File.separator + "new.apk", Environment.getExternalStorageDirectory() + File.separator + "apk.patch");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    progressDialog.dismiss();
                    new AlertDialog.Builder(MainActivity.this).setTitle("提示").setMessage("合并完成").setPositiveButton("确定", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    }).create().show();
                }
            });
        }
    }
}
