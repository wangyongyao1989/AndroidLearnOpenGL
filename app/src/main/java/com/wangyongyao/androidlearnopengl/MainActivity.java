package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProvider;
import androidx.lifecycle.ViewModelProviders;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;
import com.wangyongyao.androidlearnopengl.fragment.GLFoundationFragment;
import com.wangyongyao.androidlearnopengl.fragment.MainFragment;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
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
    private GLViewModel mGlViewModel;
    private FragmentTransaction mFragmentTransaction;
    private MainFragment mMainFragment;
    private FrameLayout mFlGlMain;
    private FrameLayout mFlGlFoundation;
    private GLFoundationFragment mFoundationFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mBinding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(mBinding.getRoot());
        ActionBar supportActionBar = getSupportActionBar();
        if (supportActionBar != null) {
            supportActionBar.hide();
        }
        if (getRequestedOrientation() != ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) {
            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        }
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN);//隐藏状态栏
        initView();
        initData();
        initListener();
        initObserver();
        addFragment();
    }

    private void addFragment() {
        mMainFragment = new MainFragment();
        FragmentManager fragmentManager = getSupportFragmentManager();
        mFragmentTransaction = fragmentManager.beginTransaction();
        mFragmentTransaction
                .add(mFlGlMain.getId(), mMainFragment)
                .commit();
    }

    private void selectionFragment(GLViewModel.FRAGMENT_STATUS status) {
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        hideTransaction(fragmentTransaction);
        switch (status) {
            case MAIN: {
                fragmentTransaction.show(mMainFragment);
                fragmentTransaction.commit();
            }
            break;
            case GL_FOUNDATION: {
                if (mFoundationFragment == null) {
                    mFoundationFragment = new GLFoundationFragment();
                    fragmentTransaction
                            .add(mFlGlFoundation.getId(), mFoundationFragment);
                }
                fragmentTransaction.show(mFoundationFragment);
                fragmentTransaction.commit();
            }
            break;
        }
    }

    private void hideTransaction(FragmentTransaction frt) {
        if (mMainFragment != null) {
            frt.hide(mMainFragment);
        }
        if (mFoundationFragment != null) {
            frt.hide(mFoundationFragment);
        }

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
        mGlViewModel = ViewModelProviders.of(this).get(GLViewModel.class);
        mGlViewModel.getSwitchFragment().observe(this, status -> {
            Log.e(TAG, "initObserver: status" + status);
            selectionFragment(status);
        });

    }

    private void initListener() {


    }

    private void initData() {
    }

    private void initView() {
        mFlGlMain = mBinding.flGlMain;
        mFlGlFoundation = mBinding.flGlFoundation;

    }


}