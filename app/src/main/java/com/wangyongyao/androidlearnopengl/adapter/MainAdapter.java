package com.wangyongyao.androidlearnopengl.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.wangyongyao.androidlearnopengl.R;
import com.wangyongyao.androidlearnopengl.model.DemoItem;

import java.util.List;

public class MainAdapter extends RecyclerView.Adapter<MainAdapter.ViewHolder> {

    private List<DemoItem> mData;
    private OnItemClickListener mListener;

    public interface OnItemClickListener {
        void onItemClick(DemoItem item);
    }

    public MainAdapter(List<DemoItem> data, OnItemClickListener listener) {
        this.mData = data;
        this.mListener = listener;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_main_module, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        DemoItem item = mData.get(position);
        holder.tvTitle.setText(item.getTitle());
        if (item.getImageRes() != 0) {
            holder.ivModule.setImageResource(item.getImageRes());
        }
        holder.itemView.setOnClickListener(v -> {
            if (mListener != null) {
                mListener.onItemClick(item);
            }
        });
    }

    @Override
    public int getItemCount() {
        return mData == null ? 0 : mData.size();
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        TextView tvTitle;
        ImageView ivModule;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            tvTitle = itemView.findViewById(R.id.tv_title);
            ivModule = itemView.findViewById(R.id.iv_module);
        }
    }
}
