package com.wangyongyao.androidlearnopengl.fragment;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;
import androidx.lifecycle.ViewModelProviders;
import androidx.lifecycle.viewmodel.ViewModelInitializer;


import com.wangyongyao.androidlearnopengl.databinding.FragmentMainBinding;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2024/9/12 23:43
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl.fragment
 */
public class MainFragment extends BaseFragment {

    private static final String TAG = MainFragment.class.getSimpleName();
    private FragmentMainBinding mBinding;
    private Button mBtnGlFoundation;
    private GLViewModel mGlViewModel;
    private Button mBtnGl3d;
    private Button mBtnGlSenior;
    private Button mBtnGlShader;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentMainBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        mBtnGlFoundation = mBinding.btnGlFoundation;
        mBtnGl3d = mBinding.btnGl3d;
        mBtnGlSenior = mBinding.btnGlSenior;
        mBtnGlShader = mBinding.btnGlShader;

    }

    @Override
    public void initData() {

    }

    @Override
    public void initObserver() {
        mGlViewModel = ViewModelProviders.of(requireActivity()).get(GLViewModel.class);

    }

    @Override
    public void initListener() {
        mBtnGlFoundation.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.GL_FOUNDATION);
        });

        mBtnGl3d.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.GL_3D);
        });

        mBtnGlSenior.setOnClickListener(View -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.GL_SENIOR);
        });

        mBtnGlShader.setOnClickListener(View -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.GL_SHADER);
        });
    }
}
