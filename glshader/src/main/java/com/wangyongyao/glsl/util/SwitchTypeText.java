package com.wangyongyao.glsl.util;

import android.annotation.SuppressLint;
import android.widget.Button;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/2/27
 * Descibe : AndroidLearnOpenGL com.wangyongyao.glsl.util
 */
public class SwitchTypeText {

    public static void switchDNTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("2D Noise");
            }
            break;
            case 1: {
                view.setText("Gradient Noise");
            }
            break;
            case 2: {
                view.setText("木头表皮噪音");
            }
            break;
            case 3: {
                view.setText("距离场噪音");
            }
            break;
            case 4: {
                view.setText("形状噪音");
            }
            break;
            case 5: {
                view.setText("水榕灯");
            }
            break;
            case 6: {
                view.setText("噪音形态");
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

    public static void switchDRTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("随机——random");
            }
            break;
            case 1: {
                view.setText("随机——混沌");
            }
            break;
            case 2: {
                view.setText("随机——truchetPattern");
            }
            break;
        }
    }

    public static void switchPFTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("图案内部应用标量");
            }
            break;
            case 1: {
                view.setText("图案内部应用矩阵");
            }
            break;
            case 2: {
                view.setText("偏移图案");
            }
            break;
            case 3: {
                view.setText("Truchet瓷砖");
            }
            break;
        }
    }

    public static void switchMFTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("平移");
            }
            break;
            case 1: {
                view.setText("矩阵旋转");
            }
            break;
            case 2: {
                view.setText("矩阵缩放");
            }
            break;
            case 3: {
                view.setText("YUV矩阵变换");
            }
            break;
            case 4: {
                view.setText("形状——极坐标图形");
            }
            break;

        }
    }


    @SuppressLint("SetTextI18n")
    public static void switchCFTypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("混合颜色 Mix函数");
            }
            break;
            case 1: {
                view.setText("缓动函数");
            }
            break;
            case 2: {
                view.setText("颜色渐变");
            }
            break;
            case 3: {
                view.setText("色相、饱和度、亮度(HSB)");
            }
            break;
            case 4: {
                view.setText("极坐标下的HSB");
            }
            break;
        }
    }

    public static void switchSFTypeText(Button view, int typeSF) {
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

    public static void switchSF1TypeText(Button view, int typeSF) {
        switch (typeSF) {
            case 0: {
                view.setText("形状——正方形");
            }
            break;
            case 1: {
                view.setText("形状——圆");
            }
            break;
            case 2: {
                view.setText("形状——距离场1");
            }
            break;
            case 3: {
                view.setText("形状——距离场2");
            }
            break;
            case 4: {
                view.setText("形状——极坐标图形");
            }
            break;

        }
    }
}
