package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = MainActivity.class.getSimpleName();


    private ActivityMainBinding mBinding;
    private GL3JniView mGlView;


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
        mGlView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGlView.onPause();
    }

    private void initObserver() {

    }

    private void initListener() {

    }

    private void initData() {

    }

    private void initView() {
        mGlView = mBinding.glView;

    }


}