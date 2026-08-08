package com.wangyongyao.androidlearnopengl.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.ViewModelProviders;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.wangyongyao.androidlearnopengl.R;
import com.wangyongyao.androidlearnopengl.adapter.SideAdapter;
import com.wangyongyao.androidlearnopengl.databinding.FragmentGl3dBinding;
import com.wangyongyao.androidlearnopengl.model.DemoItem;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
import com.wangyongyao.gl3d.GL3DCallJni;
import com.wangyongyao.gl3d.view.GL3DAnimationView;
import com.wangyongyao.gl3d.view.GL3DFlashLightView;
import com.wangyongyao.gl3d.view.GL3DShowView;
import com.wangyongyao.gl3d.view.GLDrawTextView;

import java.util.ArrayList;
import java.util.List;

public class GL3DShowFragment extends BaseFragment {

    private FragmentGl3dBinding mBinding;
    private GL3DCallJni mGL3DCallJni;
    private GLViewModel mGlViewModel;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGl3dBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        List<DemoItem> data = new ArrayList<>();
        data.add(new DemoItem(1, "GL聚光手电筒", R.drawable.img_senior));
        data.add(new DemoItem(2, "3D模型显示", R.drawable.img_3d));
        data.add(new DemoItem(3, "GL绘制文本", R.drawable.img_foundation));
        data.add(new DemoItem(4, "GL骨骼动画", R.drawable.img_3d));

        SideAdapter adapter = new SideAdapter(data, item -> {
            mBinding.glShow.removeAllViews();
            switch (item.getId()) {
                case 1:
                    mBinding.glShow.addView(new GL3DFlashLightView(getActivity(), mGL3DCallJni));
                    break;
                case 2:
                    mBinding.glShow.addView(new GL3DShowView(getActivity(), mGL3DCallJni));
                    break;
                case 3:
                    mBinding.glShow.addView(new GLDrawTextView(getActivity(), mGL3DCallJni));
                    break;
                case 4:
                    mBinding.glShow.addView(new GL3DAnimationView(getActivity(), mGL3DCallJni));
                    break;
            }
        });

        mBinding.rvSidebar.setLayoutManager(new LinearLayoutManager(getContext()));
        mBinding.rvSidebar.setAdapter(adapter);
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
        mBinding.btnBack.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.MAIN);
        });
    }

}
