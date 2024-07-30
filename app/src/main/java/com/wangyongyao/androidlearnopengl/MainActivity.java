package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.FrameLayout;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;
import com.wangyongyao.androidlearnopengl.view.GL3BaseView;
import com.wangyongyao.androidlearnopengl.view.GL3TextureView;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = MainActivity.class.getSimpleName();


    private ActivityMainBinding mBinding;
    private Button mBtn1;
    private FrameLayout mGlShow1;
    private JniCall mJniCall;
    private Button mBtn2;

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
            GL3BaseView gl3BaseView = new GL3BaseView(getApplication(),mJniCall);
            mGlShow1.addView(gl3BaseView);
        });
        mBtn2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3TextureView gl3TextureView = new GL3TextureView(getApplication(),mJniCall);
            mGlShow1.addView(gl3TextureView);
        });
    }

    private void initData() {
        mJniCall = new JniCall();
    }

    private void initView() {
        mBtn1 = mBinding.btn1;
        mBtn2 = mBinding.btn2;
        mGlShow1 = mBinding.glShow;
    }


}