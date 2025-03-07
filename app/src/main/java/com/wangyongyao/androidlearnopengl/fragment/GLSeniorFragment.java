package com.wangyongyao.androidlearnopengl.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.ViewModelProviders;

import com.wangyongyao.GLSeniorCallJni;
import com.wangyongyao.androidlearnopengl.databinding.FragmentGlSeniorBinding;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
import com.wangyongyao.views.GLSeniorAsteroidView;
import com.wangyongyao.views.GLCubeMapReflectionView;
import com.wangyongyao.views.GLFBOPostProcessingView;
import com.wangyongyao.views.GLSeniorBlendingDiscardView;
import com.wangyongyao.views.GLSeniorBlendingSortView;
import com.wangyongyao.views.GLSeniorCubeMapView;
import com.wangyongyao.views.GLSeniorDepthTestView;
import com.wangyongyao.views.GLSeniorFBOView;
import com.wangyongyao.views.GLSeniorGeometryView;
import com.wangyongyao.views.GLSeniorInstanceView;
import com.wangyongyao.views.GLSeniorStencilTestView;
import com.wangyongyao.views.GLSeniorUniformView;


/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/1/8 18:00
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl.fragment
 */
public class GLSeniorFragment extends BaseFragment {

    private FragmentGlSeniorBinding mBinding;
    private FrameLayout mGlShow1;
    private GLSeniorCallJni mGLSeniorCallJni;
    private Button mBtnBack;
    private GLViewModel mGlViewModel;
    private Button mBtnSenior1;
    private Button mBtnSenior2;
    private Button mBtnSenior3;
    private Button mBtnSenior4;
    private Button mBtnSenior5;
    private Button mBtnSenior6;
    private Button mBtnSenior7;
    private Button mBtnSenior8;

    private GLFBOPostProcessingView mGlView;
    private int switchType;
    private Button mBtnSenior9;
    private Button mBtnSenior10;
    private Button mBtnSenior11;
    private Button mBtnSenior12;
    private Button mBtnSenior13;
    private Button mBtnSenior14;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGlSeniorBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        mGlShow1 = mBinding.glShow;
        mBtnBack = mBinding.btnBack;
        mBtnSenior1 = mBinding.btnSenior1;
        mBtnSenior2 = mBinding.btnSenior2;
        mBtnSenior3 = mBinding.btnSenior3;
        mBtnSenior4 = mBinding.btnSenior4;
        mBtnSenior5 = mBinding.btnSenior5;
        mBtnSenior6 = mBinding.btnSenior6;
        mBtnSenior7 = mBinding.btnSenior7;
        mBtnSenior8 = mBinding.btnSenior8;

        mBtnSenior9 = mBinding.btnSenior9;
        mBtnSenior10 = mBinding.btnSenior10;
        mBtnSenior11 = mBinding.btnSenior11;
        mBtnSenior12 = mBinding.btnSenior12;
        mBtnSenior13 = mBinding.btnSenior13;
        mBtnSenior14 = mBinding.btnSenior14;

    }

    @Override
    public void initData() {
        mGLSeniorCallJni = new GLSeniorCallJni();
    }

    @Override
    public void initObserver() {
        mGlViewModel = ViewModelProviders.of(requireActivity()).get(GLViewModel.class);

    }

    @Override
    public void initListener() {
        mBtnBack.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.MAIN);
        });

        mBtnSenior1.setOnClickListener(view -> {
        });

        mBtnSenior2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorDepthTestView glSeniorDepthTestView = new GLSeniorDepthTestView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glSeniorDepthTestView);
        });

        mBtnSenior3.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorStencilTestView glSeniorStencilTestView = new GLSeniorStencilTestView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glSeniorStencilTestView);
        });

        mBtnSenior4.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorBlendingDiscardView glView = new GLSeniorBlendingDiscardView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior5.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorBlendingSortView glView = new GLSeniorBlendingSortView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior6.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorFBOView glView = new GLSeniorFBOView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior7.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            mGlView = new GLFBOPostProcessingView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(mGlView);
        });

        mBtnSenior8.setOnClickListener(view -> {
            if (mGlView == null) {
                return;
            }
            mGlView.setFBOPostProcessingType(switchType);
            int type = mGlView.getFBOPostProcessingType();
            switchBtnSenior7UI(type);
            switchType++;
        });

        mBtnSenior9.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorCubeMapView glView = new GLSeniorCubeMapView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior10.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLCubeMapReflectionView glView = new GLCubeMapReflectionView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior11.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorUniformView glView = new GLSeniorUniformView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior12.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorGeometryView glView = new GLSeniorGeometryView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior13.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorInstanceView glView = new GLSeniorInstanceView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

        mBtnSenior14.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSeniorAsteroidView glView = new GLSeniorAsteroidView(getActivity()
                    , mGLSeniorCallJni);
            mGlShow1.addView(glView);
        });

    }

    private void switchBtnSenior7UI(int type) {
        switch (type) {
            case 0: {
                mBtnSenior7.setText("反相");
            }
            break;
            case 1: {
                mBtnSenior7.setText("图像灰度化");
            }
            break;
            case 2: {
                mBtnSenior7.setText("灰度化加权");
            }
            break;
            case 3: {
                mBtnSenior7.setText("核效果");
            }
            break;
        }
    }

}