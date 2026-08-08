package com.wangyongyao.androidlearnopengl.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.ViewModelProviders;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.wangyongyao.GLSeniorCallJni;
import com.wangyongyao.androidlearnopengl.R;
import com.wangyongyao.androidlearnopengl.adapter.SideAdapter;
import com.wangyongyao.androidlearnopengl.databinding.FragmentGlSeniorBinding;
import com.wangyongyao.androidlearnopengl.model.DemoItem;
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

import java.util.ArrayList;
import java.util.List;

public class GLSeniorFragment extends BaseFragment {

    private FragmentGlSeniorBinding mBinding;
    private GLSeniorCallJni mGLSeniorCallJni;
    private GLViewModel mGlViewModel;
    private GLFBOPostProcessingView mGlView;
    private int switchType;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGlSeniorBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        List<DemoItem> data = new ArrayList<>();
        data.add(new DemoItem(2, "GL深度测试", R.drawable.img_senior));
        data.add(new DemoItem(3, "GL模版测试", R.drawable.img_senior));
        data.add(new DemoItem(4, "GL混合-丢弃", R.drawable.img_senior));
        data.add(new DemoItem(5, "GL混合-半透明", R.drawable.img_senior));
        data.add(new DemoItem(6, "GL帧缓冲FBO", R.drawable.img_senior));
        data.add(new DemoItem(7, "FBO后期处理", R.drawable.img_senior));
        data.add(new DemoItem(9, "立方体贴图", R.drawable.img_senior));
        data.add(new DemoItem(10, "立方体贴图-反射", R.drawable.img_senior));
        data.add(new DemoItem(11, "高级Uniform", R.drawable.img_senior));
        data.add(new DemoItem(13, "实例化Instance", R.drawable.img_senior));
        data.add(new DemoItem(14, "小行星绘制", R.drawable.img_senior));

        SideAdapter adapter = new SideAdapter(data, item -> {
            mBinding.glShow.removeAllViews();
            mBinding.btnSenior8.setVisibility(View.GONE);
            mGlView = null;
            switch (item.getId()) {
                case 2:
                    mBinding.glShow.addView(new GLSeniorDepthTestView(getActivity(), mGLSeniorCallJni));
                    break;
                case 3:
                    mBinding.glShow.addView(new GLSeniorStencilTestView(getActivity(), mGLSeniorCallJni));
                    break;
                case 4:
                    mBinding.glShow.addView(new GLSeniorBlendingDiscardView(getActivity(), mGLSeniorCallJni));
                    break;
                case 5:
                    mBinding.glShow.addView(new GLSeniorBlendingSortView(getActivity(), mGLSeniorCallJni));
                    break;
                case 6:
                    mBinding.glShow.addView(new GLSeniorFBOView(getActivity(), mGLSeniorCallJni));
                    break;
                case 7:
                    mGlView = new GLFBOPostProcessingView(getActivity(), mGLSeniorCallJni);
                    mBinding.glShow.addView(mGlView);
                    mBinding.btnSenior8.setVisibility(View.VISIBLE);
                    break;
                case 9:
                    mBinding.glShow.addView(new GLSeniorCubeMapView(getActivity(), mGLSeniorCallJni));
                    break;
                case 10:
                    mBinding.glShow.addView(new GLCubeMapReflectionView(getActivity(), mGLSeniorCallJni));
                    break;
                case 11:
                    mBinding.glShow.addView(new GLSeniorUniformView(getActivity(), mGLSeniorCallJni));
                    break;
                case 13:
                    mBinding.glShow.addView(new GLSeniorInstanceView(getActivity(), mGLSeniorCallJni));
                    break;
                case 14:
                    mBinding.glShow.addView(new GLSeniorAsteroidView(getActivity(), mGLSeniorCallJni));
                    break;
            }
        });

        mBinding.rvSidebar.setLayoutManager(new LinearLayoutManager(getContext()));
        mBinding.rvSidebar.setAdapter(adapter);
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
        mBinding.btnBack.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.MAIN);
        });

        mBinding.btnSenior8.setOnClickListener(view -> {
            if (mGlView == null) {
                return;
            }
            mGlView.setFBOPostProcessingType(switchType);
            int type = mGlView.getFBOPostProcessingType();
            switchBtnSenior7UI(type);
            switchType++;
            if (switchType > 3) switchType = 0;
        });
    }

    private void switchBtnSenior7UI(int type) {
        switch (type) {
            case 0:
                mBinding.btnSenior8.setText("反相");
                break;
            case 1:
                mBinding.btnSenior8.setText("图像灰度化");
                break;
            case 2:
                mBinding.btnSenior8.setText("灰度化加权");
                break;
            case 3:
                mBinding.btnSenior8.setText("核效果");
                break;
        }
    }
}
