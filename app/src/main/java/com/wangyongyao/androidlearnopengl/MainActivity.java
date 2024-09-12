package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;
import com.wangyongyao.glfoundation.GLFounationJniCall;
import com.wangyongyao.glfoundation.view.GL3DCameraView;
import com.wangyongyao.glfoundation.view.GL3DCubeView;
import com.wangyongyao.glfoundation.view.GL3DMultiCubeView;
import com.wangyongyao.glfoundation.view.GL3DView;
import com.wangyongyao.glfoundation.view.GL3FoundationView;
import com.wangyongyao.glfoundation.view.GL3TextureView;
import com.wangyongyao.glfoundation.view.GLAttenuationLightView;
import com.wangyongyao.glfoundation.view.GLDiffuseMapView;
import com.wangyongyao.glfoundation.view.GLDiffuseReflectionLightingView;
import com.wangyongyao.glfoundation.view.GLDirectionalLightView;
import com.wangyongyao.glfoundation.view.GLFlashLightView;
import com.wangyongyao.glfoundation.view.GLLightingView;
import com.wangyongyao.glfoundation.view.GLMaterialView;
import com.wangyongyao.glfoundation.view.GLMultiLightView;
import com.wangyongyao.glfoundation.view.GLSpecularLightingView;
import com.wangyongyao.glfoundation.view.GLSpecularMapView;
import com.wangyongyao.glfoundation.view.GLSpotLightView;


public class MainActivity extends AppCompatActivity {
    private final static String TAG = MainActivity.class.getSimpleName();


    private ActivityMainBinding mBinding;
    private Button mBtn1;
    private FrameLayout mGlShow1;
    private GLFounationJniCall mFounationJniCall;
    private Button mBtn2;
    private Button mBtn3;
    private Button mBtn4;
    private Button mBtn5;
    private Button mBtn6;
    private Button mBtn7;
    private Button mBtn8;
    private Button mBtn9;
    private Button mBtn10;
    private Button mBtn11;
    private Button mBtn12;
    private Button mBtn13;
    private Button mBtn14;
    private Button mBtn15;
    private Button mBtn16;
    private Button mBtn17;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mBinding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(mBinding.getRoot());
        ActionBar supportActionBar = getSupportActionBar();
        if (supportActionBar != null) {
            supportActionBar.hide();
        }
        if(getRequestedOrientation()!= ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE){
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        }
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN);//隐藏状态栏
        initView();
        initData();
        initListener();
        initObserver();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    private void initObserver() {

    }

    private void initListener() {
        mBtn1.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3FoundationView gl3BaseView = new GL3FoundationView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3BaseView);
        });
        mBtn2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3TextureView gl3TextureView = new GL3TextureView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3TextureView);
        });
        mBtn3.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DView gl3dView = new GL3DView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3dView);
        });
        mBtn4.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DCubeView gl3DCubeView = new GL3DCubeView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3DCubeView);
        });
        mBtn5.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DMultiCubeView gl3DMultiCubeView = new GL3DMultiCubeView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3DMultiCubeView);
        });
        mBtn6.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DCameraView gl3DCameraView = new GL3DCameraView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3DCameraView);
        });
        mBtn7.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLLightingView gl3DCameraView = new GLLightingView(getApplication(), mFounationJniCall);
            mGlShow1.addView(gl3DCameraView);
        });
        mBtn8.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDiffuseReflectionLightingView reflectionLightingView
                    = new GLDiffuseReflectionLightingView(getApplication(), mFounationJniCall);
            mGlShow1.addView(reflectionLightingView);
        });
        mBtn9.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSpecularLightingView glSpecularLightingView
                    = new GLSpecularLightingView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glSpecularLightingView);
        });
        mBtn10.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLMaterialView glMaterialView
                    = new GLMaterialView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glMaterialView);
        });
        mBtn11.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDiffuseMapView glDiffuseMap
                    = new GLDiffuseMapView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glDiffuseMap);
        });
        mBtn12.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSpecularMapView glSpecularMap
                    = new GLSpecularMapView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glSpecularMap);
        });
        mBtn13.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDirectionalLightView glDirectionalLight
                    = new GLDirectionalLightView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glDirectionalLight);
        });
        mBtn14.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLAttenuationLightView glAttenuationLight
                    = new GLAttenuationLightView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glAttenuationLight);
        });
        mBtn15.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLFlashLightView glFlashLight
                    = new GLFlashLightView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glFlashLight);
        });
        mBtn16.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSpotLightView glSpotLightView
                    = new GLSpotLightView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glSpotLightView);
        });
        mBtn17.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLMultiLightView glMultiLightView
                    = new GLMultiLightView(getApplication(), mFounationJniCall);
            mGlShow1.addView(glMultiLightView);
        });



    }

    private void initData() {
        mFounationJniCall = new GLFounationJniCall();
    }

    private void initView() {
        mGlShow1 = mBinding.glShow;
        mBtn1 = mBinding.btn1;
        mBtn2 = mBinding.btn2;
        mBtn3 = mBinding.btn3;
        mBtn4 = mBinding.btn4;
        mBtn5 = mBinding.btn5;
        mBtn6 = mBinding.btn6;
        mBtn7 = mBinding.btn7;
        mBtn8 = mBinding.btn8;
        mBtn9 = mBinding.btn9;
        mBtn10 = mBinding.btn10;
        mBtn11 = mBinding.btn11;
        mBtn12 = mBinding.btn12;
        mBtn13 = mBinding.btn13;
        mBtn14 = mBinding.btn14;
        mBtn15 = mBinding.btn15;
        mBtn16 = mBinding.btn16;
        mBtn17 = mBinding.btn17;

    }


}