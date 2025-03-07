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

import com.wangyongyao.androidlearnopengl.databinding.FragmentGl3dBinding;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
import com.wangyongyao.gl3d.GL3DCallJni;
import com.wangyongyao.gl3d.view.GL3DAnimationView;
import com.wangyongyao.gl3d.view.GL3DFlashLightView;
import com.wangyongyao.gl3d.view.GL3DShowView;
import com.wangyongyao.gl3d.view.GLDrawTextView;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2024/10/23 23:37
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl
 */
public class GL3DShowFragment extends BaseFragment {

    private FragmentGl3dBinding mBinding;
    private FrameLayout mGlShow1;
    private GL3DCallJni mGL3DCallJni;
    private Button mBtnBack;
    private GLViewModel mGlViewModel;
    private Button mBtn3D1;
    private Button mBtn3D2;
    private Button mBtn3D3;
    private Button mBtn3D4;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGl3dBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        mGlShow1 = mBinding.glShow;
        mBtnBack = mBinding.btnBack;
        mBtn3D1 = mBinding.btn3d1;
        mBtn3D2 = mBinding.btn3d2;
        mBtn3D3 = mBinding.btn3d3;
        mBtn3D4 = mBinding.btn3d4;

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

        mBtn3D1.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DFlashLightView gl3DFlashLightView = new GL3DFlashLightView(getActivity(), mGL3DCallJni);
            mGlShow1.addView(gl3DFlashLightView);
        });

        mBtn3D2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DShowView gl3DShowView = new GL3DShowView(getActivity(), mGL3DCallJni);
            mGlShow1.addView(gl3DShowView);
        });

        mBtn3D3.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GLDrawTextView glView = new GLDrawTextView(getActivity(), mGL3DCallJni);
            mGlShow1.addView(glView);
        });

        mBtn3D4.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            GL3DAnimationView glView = new GL3DAnimationView(getActivity(), mGL3DCallJni);
            mGlShow1.addView(glView);
        });

    }

}
