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
import com.wangyongyao.androidlearnopengl.databinding.FragmentGlFoundationBinding;
import com.wangyongyao.androidlearnopengl.model.DemoItem;
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

import java.util.ArrayList;
import java.util.List;

public class GLFoundationFragment extends BaseFragment {

    private FragmentGlFoundationBinding mBinding;
    private GLFounationJniCall mFounationJniCall;
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
        List<DemoItem> data = new ArrayList<>();
        data.add(new DemoItem(1, "GL基础", R.drawable.img_foundation));
        data.add(new DemoItem(2, "GL纹理", R.drawable.img_shader));
        data.add(new DemoItem(3, "基础3D显示", R.drawable.img_3d));
        data.add(new DemoItem(4, "立方体3D", R.drawable.img_3d));
        data.add(new DemoItem(5, "多立方体3D", R.drawable.img_3d));
        data.add(new DemoItem(6, "GL摄像机", R.drawable.img_3d));
        data.add(new DemoItem(7, "GL光照场景及环境光照", R.drawable.img_senior));
        data.add(new DemoItem(8, "漫反射光照", R.drawable.img_senior));
        data.add(new DemoItem(9, "镜面光照", R.drawable.img_senior));
        data.add(new DemoItem(10, "GL材质", R.drawable.img_senior));
        data.add(new DemoItem(11, "GL漫反射贴图", R.drawable.img_senior));
        data.add(new DemoItem(12, "镜面光贴图", R.drawable.img_senior));
        data.add(new DemoItem(13, "GL平行光", R.drawable.img_senior));
        data.add(new DemoItem(14, "GL点光源衰减", R.drawable.img_senior));
        data.add(new DemoItem(15, "GL聚光手电筒", R.drawable.img_senior));
        data.add(new DemoItem(16, "GL聚光平滑/软化边缘", R.drawable.img_senior));
        data.add(new DemoItem(17, "GL多光源", R.drawable.img_senior));

        SideAdapter adapter = new SideAdapter(data, item -> {
            mBinding.glShow.removeAllViews();
            switch (item.getId()) {
                case 1:
                    mBinding.glShow.addView(new GL3FoundationView(getActivity(), mFounationJniCall));
                    break;
                case 2:
                    mBinding.glShow.addView(new GL3TextureView(getActivity(), mFounationJniCall));
                    break;
                case 3:
                    mBinding.glShow.addView(new GL3DView(getActivity(), mFounationJniCall));
                    break;
                case 4:
                    mBinding.glShow.addView(new GL3DCubeView(getActivity(), mFounationJniCall));
                    break;
                case 5:
                    mBinding.glShow.addView(new GL3DMultiCubeView(getActivity(), mFounationJniCall));
                    break;
                case 6:
                    mBinding.glShow.addView(new GL3DCameraView(getActivity(), mFounationJniCall));
                    break;
                case 7:
                    mBinding.glShow.addView(new GLLightingView(getActivity(), mFounationJniCall));
                    break;
                case 8:
                    mBinding.glShow.addView(new GLDiffuseReflectionLightingView(getActivity(), mFounationJniCall));
                    break;
                case 9:
                    mBinding.glShow.addView(new GLSpecularLightingView(getActivity(), mFounationJniCall));
                    break;
                case 10:
                    mBinding.glShow.addView(new GLMaterialView(getActivity(), mFounationJniCall));
                    break;
                case 11:
                    mBinding.glShow.addView(new GLDiffuseMapView(getActivity(), mFounationJniCall));
                    break;
                case 12:
                    mBinding.glShow.addView(new GLSpecularMapView(getActivity(), mFounationJniCall));
                    break;
                case 13:
                    mBinding.glShow.addView(new GLDirectionalLightView(getActivity(), mFounationJniCall));
                    break;
                case 14:
                    mBinding.glShow.addView(new GLAttenuationLightView(getActivity(), mFounationJniCall));
                    break;
                case 15:
                    mBinding.glShow.addView(new GLFlashLightView(getActivity(), mFounationJniCall));
                    break;
                case 16:
                    mBinding.glShow.addView(new GLSpotLightView(getActivity(), mFounationJniCall));
                    break;
                case 17:
                    mBinding.glShow.addView(new GLMultiLightView(getActivity(), mFounationJniCall));
                    break;
            }
        });

        mBinding.rvSidebar.setLayoutManager(new LinearLayoutManager(getContext()));
        mBinding.rvSidebar.setAdapter(adapter);
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
        mBinding.btnBack.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.MAIN);
        });
    }
}
