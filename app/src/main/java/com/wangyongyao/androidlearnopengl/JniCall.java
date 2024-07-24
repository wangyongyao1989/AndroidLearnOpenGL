package com.wangyongyao.androidlearnopengl;

public class JniCall {

    // Used to load the 'androidlearnopengl' library on application startup.
    static {
        System.loadLibrary("androidlearnopengl");
    }


    public native String stringFromJNI();

    private native void native_callback();

}
