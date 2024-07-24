package com.wangyongyao.androidlearnopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.wangyongyao.androidlearnopengl.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {



    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
    }


}