package com.example.mydemo3;

import android.content.ContentValues;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;

import java.util.Map;


public class MainActivity extends AppCompatActivity {

    ImageView temAndHum;
    ImageView remoteControl;
    ImageView doorControl;
    ImageView socketControl;
    public static String tem = "", hum = "";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }


    public void onButtonTempAndHum(View view) {
        TestTask testTask = new TestTask();
        testTask.execute();
    }

    public void onButtonRemoteControl(View view) {
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, RemoteActivity.class);
        startActivity(intent);
        finish();
    }

    public void onButtonDoorControl(View view) {
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, DoorControlActivity.class);
        startActivity(intent);
        finish();
    }

    public void onButtonSocketControl(View view) {
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, SocketControlActivity.class);
        startActivity(intent);
        finish();
    }

    public void onButtonLogout(View view) {
        ConstantValues_bk.SP_USERNAME = "null";
        ConstantValues_bk.SP_USERPWD = "null";
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, LoginActivity.class);
        startActivity(intent);
        finish();
    }

    public void onButtonToLogin(View view){
        Intent intent = new Intent();
        intent.setClass(MainActivity.this, LoginActivity.class);
        startActivity(intent);
        finish();
    }

    public class TestTask extends AsyncTask<Void, Void, ABRet> {
        @Override
        protected ABRet doInBackground(Void... voids) {
            ABRet abRet = ABSDK.getInstance().getThStatus("温湿度传感器");
            return abRet;
        }

        protected void onPostExecute(ABRet abRet) {
            super.onPostExecute(abRet);
            String code = abRet.getCode();
            if (code.equals("00000")) {
                Map retMap = abRet.getDicDatas();
                tem = retMap.get("temperature").toString();
                hum = retMap.get("humidity").toString();
                Intent intent = new Intent();
                intent.setClass(MainActivity.this, ShowTempHumActivity.class);
                startActivity(intent);
                finish();
            } else if (code.equals("20000")) {
                Toast.makeText(MainActivity.this, "超时", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(MainActivity.this, ConstantValues_bk.codeMaps.get(code), Toast.LENGTH_SHORT).show();
            }
        }

    }
}



