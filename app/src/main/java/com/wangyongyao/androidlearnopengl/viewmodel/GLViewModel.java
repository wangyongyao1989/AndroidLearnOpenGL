package com.wangyongyao.androidlearnopengl.viewmodel;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class GLViewModel extends ViewModel {


    private final MutableLiveData<FRAGMENT_STATUS> switchFragment
            = new MutableLiveData<>();

    public enum FRAGMENT_STATUS {
        MAIN,
        GL_FOUNDATION,
        GL_3D,
        GL_SENIOR,
        GL_SHADER,
    }


    public MutableLiveData<FRAGMENT_STATUS> getSwitchFragment() {
        return switchFragment;
    }
}
