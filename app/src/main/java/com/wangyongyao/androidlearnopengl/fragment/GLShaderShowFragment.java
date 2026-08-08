package com.wangyongyao.androidlearnopengl.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.ViewModelProviders;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.wangyongyao.androidlearnopengl.R;
import com.wangyongyao.androidlearnopengl.adapter.SideAdapter;
import com.wangyongyao.androidlearnopengl.databinding.FragmentGlShaderBinding;
import com.wangyongyao.androidlearnopengl.model.DemoItem;
import com.wangyongyao.androidlearnopengl.viewmodel.GLViewModel;
import com.wangyongyao.glsl.GLSLCallJni;
import com.wangyongyao.glsl.util.SwitchTypeText;
import com.wangyongyao.glsl.view.GLSLColorFunctionsView;
import com.wangyongyao.glsl.view.GLSLMatricesFunctionsView;
import com.wangyongyao.glsl.view.GLSLPatternsFunctionsView;
import com.wangyongyao.glsl.view.GLSLShapeFunctionsView;
import com.wangyongyao.glsl.view.GLSLShapingFunctionsView;

import java.util.ArrayList;
import java.util.List;

public class GLShaderShowFragment extends BaseFragment {

    private FragmentGlShaderBinding mBinding;
    private GLSLCallJni mGL3DCallJni;
    private GLViewModel mGlViewModel;

    private GLSLShapingFunctionsView mShapingFunctionsView;
    private GLSLColorFunctionsView mColorFunctionsView;
    private GLSLShapeFunctionsView mShapeFunctionsView;
    private GLSLMatricesFunctionsView mMatricesFunctionsView;
    private GLSLPatternsFunctionsView mPatternsFunctionsView;

    private int typeSF;
    private int typeCF;
    private int typeMF;
    private int typePF;
    private int currentDemoId = -1;

    @Override
    public View getLayoutDataBing(@NonNull LayoutInflater inflater
            , @Nullable ViewGroup container
            , @Nullable Bundle savedInstanceState) {
        mBinding = FragmentGlShaderBinding.inflate(inflater);
        return mBinding.getRoot();
    }

    @Override
    public void initView() {
        List<DemoItem> data = new ArrayList<>();
        data.add(new DemoItem(1, "GL 造型函数", R.drawable.img_shader));
        data.add(new DemoItem(2, "GL着色器——Color", R.drawable.img_shader));
        data.add(new DemoItem(3, "GL着色器——形状", R.drawable.img_shader));
        data.add(new DemoItem(4, "GL着色器——二维矩阵", R.drawable.img_shader));
        data.add(new DemoItem(5, "GL着色器——图案", R.drawable.img_shader));

        SideAdapter adapter = new SideAdapter(data, item -> {
            mBinding.glShow.removeAllViews();
            mBinding.btnNextType.setVisibility(View.VISIBLE);
            currentDemoId = item.getId();
            switch (item.getId()) {
                case 1:
                    if (mShapingFunctionsView == null) {
                        mShapingFunctionsView = new GLSLShapingFunctionsView(getActivity(), mGL3DCallJni);
                        typeSF = 0;
                    }
                    mShapingFunctionsView.setType(typeSF);
                    SwitchTypeText.switchSFTypeText(mBinding.btnNextType, mShapingFunctionsView.getType());
                    mBinding.glShow.addView(mShapingFunctionsView);
                    break;
                case 2:
                    if (mColorFunctionsView == null) {
                        mColorFunctionsView = new GLSLColorFunctionsView(getActivity(), mGL3DCallJni);
                        typeCF = 0;
                    }
                    mColorFunctionsView.setType(typeCF);
                    SwitchTypeText.switchCFTypeText(mBinding.btnNextType, mColorFunctionsView.getType());
                    mBinding.glShow.addView(mColorFunctionsView);
                    break;
                case 3:
                    if (mShapeFunctionsView == null) {
                        mShapeFunctionsView = new GLSLShapeFunctionsView(getActivity(), mGL3DCallJni);
                        typeSF = 0;
                    }
                    mShapeFunctionsView.setType(typeSF);
                    SwitchTypeText.switchSF1TypeText(mBinding.btnNextType, mShapeFunctionsView.getType());
                    mBinding.glShow.addView(mShapeFunctionsView);
                    break;
                case 4:
                    if (mMatricesFunctionsView == null) {
                        mMatricesFunctionsView = new GLSLMatricesFunctionsView(getActivity(), mGL3DCallJni);
                        typeMF = 0;
                    }
                    mMatricesFunctionsView.setType(typeMF);
                    SwitchTypeText.switchMFTypeText(mBinding.btnNextType, mMatricesFunctionsView.getType());
                    mBinding.glShow.addView(mMatricesFunctionsView);
                    break;
                case 5:
                    if (mPatternsFunctionsView == null) {
                        mPatternsFunctionsView = new GLSLPatternsFunctionsView(getActivity(), mGL3DCallJni);
                        typePF = 0;
                    }
                    mPatternsFunctionsView.setType(typePF);
                    SwitchTypeText.switchPFTypeText(mBinding.btnNextType, mPatternsFunctionsView.getType());
                    mBinding.glShow.addView(mPatternsFunctionsView);
                    break;
            }
        });

        mBinding.rvSidebar.setLayoutManager(new LinearLayoutManager(getContext()));
        mBinding.rvSidebar.setAdapter(adapter);
    }

    @Override
    public void initData() {
        mGL3DCallJni = new GLSLCallJni();
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

        mBinding.btnNextType.setOnClickListener(view -> {
            switch (currentDemoId) {
                case 1:
                    typeSF++;
                    if (mShapingFunctionsView != null) {
                        mShapingFunctionsView.setType(typeSF);
                        SwitchTypeText.switchSFTypeText(mBinding.btnNextType, mShapingFunctionsView.getType());
                    }
                    break;
                case 2:
                    typeCF++;
                    if (mColorFunctionsView != null) {
                        mColorFunctionsView.setType(typeCF);
                        SwitchTypeText.switchCFTypeText(mBinding.btnNextType, mColorFunctionsView.getType());
                    }
                    break;
                case 3:
                    typeSF++; // Shape functions also use typeSF in original code
                    if (mShapeFunctionsView != null) {
                        mShapeFunctionsView.setType(typeSF);
                        SwitchTypeText.switchSF1TypeText(mBinding.btnNextType, mShapeFunctionsView.getType());
                    }
                    break;
                case 4:
                    typeMF++;
                    if (mMatricesFunctionsView != null) {
                        mMatricesFunctionsView.setType(typeMF);
                        SwitchTypeText.switchMFTypeText(mBinding.btnNextType, mMatricesFunctionsView.getType());
                    }
                    break;
                case 5:
                    typePF++;
                    if (mPatternsFunctionsView != null) {
                        mPatternsFunctionsView.setType(typePF);
                        SwitchTypeText.switchPFTypeText(mBinding.btnNextType, mPatternsFunctionsView.getType());
                    }
                    break;
            }
        });
    }
}
