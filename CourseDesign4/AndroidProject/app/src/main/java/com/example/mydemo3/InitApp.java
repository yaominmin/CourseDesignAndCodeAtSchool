package com.example.mydemo3;

import android.app.Application;
import android.content.Intent;
import android.content.SharedPreferences;

public class InitApp extends Application {

    private Intent intent = new Intent(); // Decide which page to go

    @Override
    public void onCreate() {
        super.onCreate();
        intent.setClass(InitApp.this, InitActivity.class);
        intent.addFlags(intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }
}
