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

import com.wangyongyao.androidlearnopengl.databinding.FragmentGlSeniorBinding;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
import com.wangyongyao.gl3d.GL3DCallJni;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/1/8 18:00
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl.fragment
 */
public class GLSeniorFragment extends BaseFragment {

    private FragmentGlSeniorBinding mBinding;
    private FrameLayout mGlShow1;
    private GL3DCallJni mGL3DCallJni;
    private Button mBtnBack;
    private GLViewModel mGlViewModel;
    private Button mBtnSenior1;

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
    }

    @Override
    public void initData() {
        mGL3DCallJni = new GL3DCallJni();
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

    }

}