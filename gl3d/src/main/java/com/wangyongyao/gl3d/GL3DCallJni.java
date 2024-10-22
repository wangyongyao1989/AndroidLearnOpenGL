package com.wangyongyao.gl3d;

import android.util.Log;

public class GL3DCallJni {

    private static final String TAG = GL3DCallJni.class.getSimpleName();

    static {
        System.loadLibrary("gl3d");
    }



    private void CppEventCallback(int msgType, float msgValue) {
        Log.e(TAG, "msgType:" + msgType + "====msgValue:" + msgValue);

    }

    private void CppPlayStatusCallback(String status) {
        Log.e(TAG, "status:" + status);

    }


}
