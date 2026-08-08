package com.wangyongyao.androidlearnopengl.model;

public class DemoItem {
    private String title;
    private int id;
    private int imageRes;

    public DemoItem(int id, String title) {
        this.id = id;
        this.title = title;
    }

    public DemoItem(int id, String title, int imageRes) {
        this.id = id;
        this.title = title;
        this.imageRes = imageRes;
    }

    public String getTitle() {
        return title;
    }

    public int getId() {
        return id;
    }

    public int getImageRes() {
        return imageRes;
    }
}
