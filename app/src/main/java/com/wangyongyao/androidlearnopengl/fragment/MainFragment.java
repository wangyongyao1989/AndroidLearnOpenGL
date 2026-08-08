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


import androidx.recyclerview.widget.GridLayoutManager;

import com.wangyongyao.androidlearnopengl.R;
import com.wangyongyao.androidlearnopengl.adapter.MainAdapter;
import com.wangyongyao.androidlearnopengl.databinding.FragmentMainBinding;
import com.wangyongyao.androidlearnopengl.model.DemoItem;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;

import java.util.ArrayList;
import java.util.List;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2024/9/12 23:43
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl.fragment
 */
public class MainFragment extends BaseFragment {

    private static final String TAG = MainFragment.class.getSimpleName();
    private FragmentMainBinding mBinding;
    private GLViewModel mGlViewModel;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentMainBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        List<DemoItem> data = new ArrayList<>();
        data.add(new DemoItem(GLViewModel.FRAGMENT_STATUS.GL_FOUNDATION.ordinal(), "OpenGL基础", R.drawable.img_foundation));
        data.add(new DemoItem(GLViewModel.FRAGMENT_STATUS.GL_3D.ordinal(), "OpenGL 3D", R.drawable.img_3d));
        data.add(new DemoItem(GLViewModel.FRAGMENT_STATUS.GL_SENIOR.ordinal(), "OpenGL高级", R.drawable.img_senior));
        data.add(new DemoItem(GLViewModel.FRAGMENT_STATUS.GL_SHADER.ordinal(), "GLShader着色器编程", R.drawable.img_shader));

        MainAdapter adapter = new MainAdapter(data, item -> {
            GLViewModel.FRAGMENT_STATUS[] statuses = GLViewModel.FRAGMENT_STATUS.values();
            if (item.getId() >= 0 && item.getId() < statuses.length) {
                mGlViewModel.getSwitchFragment().postValue(statuses[item.getId()]);
            }
        });

        mBinding.rvMain.setLayoutManager(new GridLayoutManager(getContext(), 2));
        mBinding.rvMain.setAdapter(adapter);
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
    }
}
