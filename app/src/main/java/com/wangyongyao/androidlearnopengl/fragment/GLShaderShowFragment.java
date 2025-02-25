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
import com.wangyongyao.glsl.view.GLSLColorFunctionsView;
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
    private Button mBtn2;

    private GLSLShapingFunctionsView mShapingFunctionsView;
    private GLSLColorFunctionsView mColorFunctionsView;

    private int typeSF;
    private int typeCF;

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
            switchSFTypeText(mBtn1, mShapingFunctionsView.getType());
            mGlShow1.addView(mShapingFunctionsView);
        });


        mBtn2.setOnClickListener(view -> {
            mGlShow1.removeAllViews();
            if (mColorFunctionsView == null) {
                mColorFunctionsView = new GLSLColorFunctionsView(getActivity(), mGL3DCallJni);
                typeCF = 0;
            } else {
                typeCF++;
                mColorFunctionsView.setType(typeCF);
            }
            switchCFTypeText(mBtn2, mColorFunctionsView.getType());
            mGlShow1.addView(mColorFunctionsView);
        });
    }

    private void switchCFTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("混合颜色 Mix函数");
            }
            break;
            case 1: {
                view.setText("造型函数——step()函数");
            }
            break;
            case 2: {
                view.setText("造型函数——曲线及颜色渐变");
            }
            break;
            case 3: {
                view.setText("造型函数——其他有用函数");
            }
            break;
            case 4: {
                view.setText("多项式造型函数");
            }
            break;
            case 5: {
                view.setText("指数造型函数");
            }
            break;
            case 6: {
                view.setText("椭圆造型函数");
            }
            break;
            case 7: {
                view.setText("赛贝尔造型函数");
            }
            break;
            case 8: {
                view.setText("Impulse 函数");
            }
            break;
            case 9: {
                view.setText("CubicPulse 函数");
            }
            break;
            case 10: {
                view.setText("ExpStep 函数");
            }
            break;
            case 11: {
                view.setText("Parabola 函数");
            }
            break;
            case 12: {
                view.setText("Pcurve 函数");
            }
            break;

        }
    }

    private void switchSFTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("造型函数——直线及颜色渐变");
            }
            break;
            case 1: {
                view.setText("造型函数——step()函数");
            }
            break;
            case 2: {
                view.setText("造型函数——曲线及颜色渐变");
            }
            break;
            case 3: {
                view.setText("造型函数——其他有用函数");
            }
            break;
            case 4: {
                view.setText("多项式造型函数");
            }
            break;
            case 5: {
                view.setText("指数造型函数");
            }
            break;
            case 6: {
                view.setText("椭圆造型函数");
            }
            break;
            case 7: {
                view.setText("赛贝尔造型函数");
            }
            break;
            case 8: {
                view.setText("Impulse 函数");
            }
            break;
            case 9: {
                view.setText("CubicPulse 函数");
            }
            break;
            case 10: {
                view.setText("ExpStep 函数");
            }
            break;
            case 11: {
                view.setText("Parabola 函数");
            }
            break;
            case 12: {
                view.setText("Pcurve 函数");
            }
            break;

        }
    }

}
