package com.wangyongyao.androidlearnopengl;

public class JniCall {

    // Used to load the 'androidlearnopengl' library on application startup.
    static {
        System.loadLibrary("androidlearnopengl");
    }

    public boolean initOpenGl(int w, int h) {
        return native_init_opengl(w, h);
    }

    public void openGlRenderFrame() {
        native_render_frame();
    }


    public native String stringFromJNI();

    private native void native_callback();


    private native boolean native_init_opengl(int width, int height);

    private native void native_render_frame();


}
