package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProviders;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;
import com.wangyongyao.androidlearnopengl.fragment.GL3DShowFragment;
import com.wangyongyao.androidlearnopengl.fragment.GLFoundationFragment;
import com.wangyongyao.androidlearnopengl.fragment.GLSeniorFragment;
import com.wangyongyao.androidlearnopengl.fragment.GLShaderShowFragment;
import com.wangyongyao.androidlearnopengl.fragment.MainFragment;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;


public class MainActivity extends AppCompatActivity {
    private final static String TAG = MainActivity.class.getSimpleName();


    private ActivityMainBinding mBinding;
    private GLViewModel mGlViewModel;
    private FragmentTransaction mFragmentTransaction;
    private MainFragment mMainFragment;
    private FrameLayout mFlGlMain;
    private FrameLayout mFlGlFoundation;
    private GLFoundationFragment mFoundationFragment;
    private FrameLayout mFlGl3d;
    private GL3DShowFragment mGl3DShowFragment;
    private GLSeniorFragment mGLSeniorFragment;
    private GLShaderShowFragment mShaderShowFragment;

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
            case GL_3D: {
                if (mGl3DShowFragment == null) {
                    mGl3DShowFragment = new GL3DShowFragment();
                    fragmentTransaction
                            .add(mFlGl3d.getId(), mGl3DShowFragment);
                }
                fragmentTransaction.show(mGl3DShowFragment);
                fragmentTransaction.commit();
            }
            break;
            case GL_SENIOR: {
                if (mGLSeniorFragment == null) {
                    mGLSeniorFragment = new GLSeniorFragment();
                    fragmentTransaction
                            .add(mFlGl3d.getId(), mGLSeniorFragment);
                }
                fragmentTransaction.show(mGLSeniorFragment);
                fragmentTransaction.commit();
            }
            break;
            case GL_SHADER: {
                if (mShaderShowFragment == null) {
                    mShaderShowFragment = new GLShaderShowFragment();
                    fragmentTransaction
                            .add(mFlGl3d.getId(), mShaderShowFragment);
                }
                fragmentTransaction.show(mShaderShowFragment);
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

        if (mGl3DShowFragment != null) {
            frt.hide(mGl3DShowFragment);
        }

        if (mGLSeniorFragment != null) {
            frt.hide(mGLSeniorFragment);
        }

        if (mShaderShowFragment != null) {
            frt.hide(mShaderShowFragment);
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
        mFlGl3d = mBinding.flGl3d;

    }


}