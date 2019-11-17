package com.example.mydemo3;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;

public class InitActivity extends AppCompatActivity {

    String usr;
    String pwd;
    private Intent intent = new Intent(); // Decide which page to go

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_init);

        SharedPreferences sharedPreferences =
                getSharedPreferences(ConstValues.SP_FILE, MODE_PRIVATE);
        usr = sharedPreferences.getString(ConstValues.SP_USR, "null");
        pwd = sharedPreferences.getString(ConstValues.SP_PWD, "null");
        new Thread(){
            @Override
            public void run() {
                super.run();
                try {
                    sleep(3000);
                    Log.i("Info", "User: " + usr + "Pwd: " + pwd);
                    if (usr != null && pwd != null) {
                        // Select page
                        if (!usr.equals("null") && !pwd.equals("null")) {
                            LoginTask loginTask = new LoginTask();
                            loginTask.execute();
                            intent.setClass(
                                    InitActivity.this, MainActivity.class);
                        }
                        else {
                            intent.setClass(
                                    InitActivity.this, LoginActivity.class);
                        }
                    }
                    else {
                        intent.setClass(
                                InitActivity.this, LoginActivity.class);
                    }

                    // Jump to target page
                    startActivity(intent);
                    finish();
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }

    @SuppressLint("StaticFieldLeak")
    public class LoginTask extends AsyncTask<Void, Void, ABRet> {

        @Override
        protected ABRet doInBackground(Void... voids) {

            // Avoid error caused by redundant spaces
            usr = usr.trim();
            pwd = pwd.trim();

            return ABSDK.getInstance().loginWithUsername(usr, pwd);
        }

        @Override
        protected void onPostExecute(ABRet abRet) {
            super.onPostExecute(abRet);
        }
    }
}
