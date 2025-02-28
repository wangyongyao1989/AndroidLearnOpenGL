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

import com.wangyongyao.androidlearnopengl.databinding.FragmentGlShaderBinding;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
import com.wangyongyao.glsl.GLSLADCallJni;
import com.wangyongyao.glsl.GLSLDGCallJni;
import com.wangyongyao.glsl.util.SwitchTypeText;
import com.wangyongyao.glsl.view.algoritmdrawing.GLSLColorFunctionsView;
import com.wangyongyao.glsl.view.algoritmdrawing.GLSLMatricesFunctionsView;
import com.wangyongyao.glsl.view.algoritmdrawing.GLSLPatternsFunctionsView;
import com.wangyongyao.glsl.view.algoritmdrawing.GLSLShapeFunctionsView;
import com.wangyongyao.glsl.view.algoritmdrawing.GLSLShapingFunctionsView;
import com.wangyongyao.glsl.view.designgeneration.GLSLRandomFunctionsView;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl
 */
public class GLShaderShowFragment extends BaseFragment {

    private FragmentGlShaderBinding mBinding;
    private FrameLayout mGlShow1;
    private GLSLADCallJni mGLADCallJni;
    private GLSLDGCallJni mGLDGCallJni;

    private Button mBtnBack;
    private GLViewModel mGlViewModel;
    private Button mBtn1;
    private Button mBtn2;
    private Button mBtn3;
    private Button mBtn4;
    private Button mBtn5;
    private Button mBtn6;

    private GLSLShapingFunctionsView mShapingFunctionsView;
    private GLSLColorFunctionsView mColorFunctionsView;
    private GLSLShapeFunctionsView mShapeFunctionsView;
    private GLSLMatricesFunctionsView mMatricesFunctionsView;
    private GLSLPatternsFunctionsView mPatternsFunctionsView;
    private GLSLRandomFunctionsView mRandomFunctionsView;
    private int typeSF;
    private int typeCF;
    private int typeMF;
    private int typePF;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGlShaderBinding.inflate(inflater);
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

    }

    @Override
    public void initData() {
        mGLADCallJni = new GLSLADCallJni();
        mGLDGCallJni = new GLSLDGCallJni();
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
            if (mShapingFunctionsView == null) {
                mShapingFunctionsView = new GLSLShapingFunctionsView(getActivity(), mGLADCallJni);
                typeSF = 0;
            } else {
                typeSF++;
                mShapingFunctionsView.setType(typeSF);
            }
            SwitchTypeText.switchSFTypeText(mBtn1, mShapingFunctionsView.getType());
            mGlShow1.addView(mShapingFunctionsView);
        });


        mBtn2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mColorFunctionsView == null) {
                mColorFunctionsView = new GLSLColorFunctionsView(getActivity(), mGLADCallJni);
                typeCF = 0;
            } else {
                typeCF++;
                mColorFunctionsView.setType(typeCF);
            }
            SwitchTypeText.switchCFTypeText(mBtn2, mColorFunctionsView.getType());
            mGlShow1.addView(mColorFunctionsView);
        });

        mBtn3.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mShapeFunctionsView == null) {
                mShapeFunctionsView = new GLSLShapeFunctionsView(getActivity(), mGLADCallJni);
                typeSF = 0;
            } else {
                typeSF++;
                mShapeFunctionsView.setType(typeSF);
            }
            SwitchTypeText.switchSF1TypeText(mBtn3, mShapeFunctionsView.getType());
            mGlShow1.addView(mShapeFunctionsView);
        });

        mBtn4.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mMatricesFunctionsView == null) {
                mMatricesFunctionsView = new GLSLMatricesFunctionsView(getActivity(), mGLADCallJni);
                typeMF = 0;
            } else {
                typeMF++;
                mMatricesFunctionsView.setType(typeMF);
            }
            SwitchTypeText.switchMFTypeText(mBtn4, mMatricesFunctionsView.getType());
            mGlShow1.addView(mMatricesFunctionsView);
        });

        mBtn5.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mPatternsFunctionsView == null) {
                mPatternsFunctionsView = new GLSLPatternsFunctionsView(getActivity(), mGLADCallJni);
                typePF = 0;
            } else {
                typePF++;
                mPatternsFunctionsView.setType(typePF);
            }
            SwitchTypeText.switchPFTypeText(mBtn5, mPatternsFunctionsView.getType());
            mGlShow1.addView(mPatternsFunctionsView);
        });

        mBtn6.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mRandomFunctionsView == null) {
                mRandomFunctionsView = new GLSLRandomFunctionsView(getActivity(), mGLDGCallJni);
                typePF = 0;
            } else {
                typePF++;
                mRandomFunctionsView.setType(typePF);
            }
            SwitchTypeText.switchPFTypeText(mBtn6, mRandomFunctionsView.getType());
            mGlShow1.addView(mRandomFunctionsView);
        });

    }


}
