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

import com.wangyongyao.androidlearnopengl.databinding.FragmentGlFoundationBinding;
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

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2024/9/12 23:37
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl
 */
public class GLFoundationFragment extends BaseFragment {

    private FragmentGlFoundationBinding mBinding;
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
    private Button mBtnBack;
    private GLViewModel mGlViewModel;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGlFoundationBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        mGlShow1 = mBinding.glShow;
        mBtnBack = mBinding.btnBack;
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

    @Override
    public void initData() {
        mFounationJniCall = new GLFounationJniCall();
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
        mBtn1.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3FoundationView gl3BaseView = new GL3FoundationView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3BaseView);
        });
        mBtn2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3TextureView gl3TextureView = new GL3TextureView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3TextureView);
        });
        mBtn3.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DView gl3dView = new GL3DView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3dView);
        });
        mBtn4.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DCubeView gl3DCubeView = new GL3DCubeView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3DCubeView);
        });
        mBtn5.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DMultiCubeView gl3DMultiCubeView = new GL3DMultiCubeView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3DMultiCubeView);
        });
        mBtn6.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DCameraView gl3DCameraView = new GL3DCameraView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3DCameraView);
        });
        mBtn7.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLLightingView gl3DCameraView = new GLLightingView(getActivity(), mFounationJniCall);
            mGlShow1.addView(gl3DCameraView);
        });
        mBtn8.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDiffuseReflectionLightingView reflectionLightingView
                    = new GLDiffuseReflectionLightingView(getActivity(), mFounationJniCall);
            mGlShow1.addView(reflectionLightingView);
        });
        mBtn9.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSpecularLightingView glSpecularLightingView
                    = new GLSpecularLightingView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glSpecularLightingView);
        });
        mBtn10.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLMaterialView glMaterialView
                    = new GLMaterialView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glMaterialView);
        });
        mBtn11.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDiffuseMapView glDiffuseMap
                    = new GLDiffuseMapView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glDiffuseMap);
        });
        mBtn12.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSpecularMapView glSpecularMap
                    = new GLSpecularMapView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glSpecularMap);
        });
        mBtn13.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDirectionalLightView glDirectionalLight
                    = new GLDirectionalLightView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glDirectionalLight);
        });
        mBtn14.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLAttenuationLightView glAttenuationLight
                    = new GLAttenuationLightView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glAttenuationLight);
        });
        mBtn15.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLFlashLightView glFlashLight
                    = new GLFlashLightView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glFlashLight);
        });
        mBtn16.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLSpotLightView glSpotLightView
                    = new GLSpotLightView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glSpotLightView);
        });
        mBtn17.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLMultiLightView glMultiLightView
                    = new GLMultiLightView(getActivity(), mFounationJniCall);
            mGlShow1.addView(glMultiLightView);
        });
    }

}
