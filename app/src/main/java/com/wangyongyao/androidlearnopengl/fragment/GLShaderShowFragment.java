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
import com.wangyongyao.glsl.GLSLCallJni;
import com.wangyongyao.glsl.view.GLSLShapingFunctionsView;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Descibe : AndroidLearnOpenGL com.wangyongyao.androidlearnopengl
 */
public class GLShaderShowFragment extends BaseFragment {

    private FragmentGlShaderBinding mBinding;
    private FrameLayout mGlShow1;
    private GLSLCallJni mGL3DCallJni;
    private Button mBtnBack;
    private GLViewModel mGlViewModel;
    private Button mBtn1;
    private GLSLShapingFunctionsView mShapingFunctionsView;
    private int typeSF;

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
        mBtnBack.setOnClickListener(view -> {
            mGlViewModel.getSwitchFragment().postValue(GLViewModel.FRAGMENT_STATUS.MAIN);
        });

        mBtn1.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mShapingFunctionsView == null) {
                mShapingFunctionsView = new GLSLShapingFunctionsView(getActivity(), mGL3DCallJni);
                typeSF = 0;
            } else {
                typeSF++;
                mShapingFunctionsView.setType(typeSF);
            }
            switchTypeText(mShapingFunctionsView.getType());
            mGlShow1.addView(mShapingFunctionsView);
        });


    }

    private void switchTypeText(int typeSF) {
        switch (typeSF) {
            case 0: {
                mBtn1.setText("造型函数——直线及颜色渐变");
            }
            break;
            case 1: {
                mBtn1.setText("造型函数——step()函数");
            }
            break;
            case 2: {
                mBtn1.setText("造型函数——曲线及颜色渐变");
            }
            break;
            case 3: {
                mBtn1.setText("造型函数——其他有用函数");
            }
            break;
            case 4: {
                mBtn1.setText("多项式造型函数");
            }
            break;
            case 5: {
                mBtn1.setText("指数造型函数");
            }
            break;
            case 6: {
                mBtn1.setText("椭圆造型函数");
            }
            break;
            case 7: {
                mBtn1.setText("赛贝尔造型函数");
            }
            break;
            case 8: {
                mBtn1.setText("Impulse 函数");
            }
            break;
            case 9: {
                mBtn1.setText("CubicPulse 函数");
            }
            break;
            case 10: {
                mBtn1.setText("ExpStep 函数");
            }
            break;
            case 11: {
                mBtn1.setText("Parabola 函数");
            }
            break;
            case 12: {
                mBtn1.setText("Pcurve 函数");
            }
            break;

        }
    }

}
