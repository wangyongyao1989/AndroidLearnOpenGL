package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.FrameLayout;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;
import com.wangyongyao.androidlearnopengl.view.GL3DCubeView;
import com.wangyongyao.androidlearnopengl.view.GL3DView;
import com.wangyongyao.androidlearnopengl.view.GL3FoundationView;
import com.wangyongyao.androidlearnopengl.view.GL3TextureView;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = MainActivity.class.getSimpleName();


    private ActivityMainBinding mBinding;
    private Button mBtn1;
    private FrameLayout mGlShow1;
    private JniCall mJniCall;
    private Button mBtn2;
    private Button mBtn3;
    private Button mBtn4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mBinding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(mBinding.getRoot());

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
            GL3FoundationView gl3BaseView = new GL3FoundationView(getApplication(), mJniCall);
            mGlShow1.addView(gl3BaseView);
        });
        mBtn2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3TextureView gl3TextureView = new GL3TextureView(getApplication(), mJniCall);
            mGlShow1.addView(gl3TextureView);
        });
        mBtn3.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DView gl3dView = new GL3DView(getApplication(), mJniCall);
            mGlShow1.addView(gl3dView);
        });
        mBtn4.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DCubeView gl3DCubeView = new GL3DCubeView(getApplication(), mJniCall);
            mGlShow1.addView(gl3DCubeView);
        });
    }

    private void initData() {
        mJniCall = new JniCall();
    }

    private void initView() {
        mGlShow1 = mBinding.glShow;
        mBtn1 = mBinding.btn1;
        mBtn2 = mBinding.btn2;
        mBtn3 = mBinding.btn3;
        mBtn4 = mBinding.btn4;
    }


}