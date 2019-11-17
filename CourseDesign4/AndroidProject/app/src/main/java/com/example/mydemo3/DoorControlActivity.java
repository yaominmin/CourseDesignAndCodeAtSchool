package com.example.mydemo3;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;
import com.example.mydemo3.ConstantValues_bk;
import com.example.mydemo3.R;

import java.util.Map;

public class DoorControlActivity extends AppCompatActivity {

    ImageView ivDoor;
    String status;
    Map<String,Object> dicDatas;
    TextView txDoor;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_door_control);
        ivDoor = findViewById(R.id.iv_Door);
        txDoor = findViewById(R.id.tv_door);
        ActionBar actionBar = getSupportActionBar();
        if(actionBar != null){
            actionBar.setHomeButtonEnabled(true);
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                this.finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public class DoorTask extends AsyncTask<Void,Void, ABRet>{
        @Override
        protected ABRet doInBackground(Void... voids) {
            ABRet abRet = ABSDK.getInstance().getDoorStatus("门磁传感器");
            return abRet;
        }

        @Override
        protected void onPostExecute(ABRet abRet) {
            super.onPostExecute(abRet);
            String retCode=abRet.getCode();
            if(retCode.equals("00000")){

                dicDatas = abRet.getDicDatas();
                status = dicDatas.get("status").toString();
                //Toast.makeText(DoorControlActivity.this, abRet.getCode()+"  "+abRet.getMsg()+
                        //"门磁状态"+ status,Toast.LENGTH_SHORT).show();
                if(status.equals("0")){
                    ivDoor.setImageResource(R.drawable.door_off);
                    Toast.makeText(DoorControlActivity.this,"门磁状态关闭",Toast.LENGTH_SHORT).show();
                    txDoor.setText("门磁已关闭");

                }
                else if(status.equals("1")){
                    ivDoor.setImageResource(R.drawable.door_on);
                    Toast.makeText(DoorControlActivity.this,"门磁状态开启",Toast.LENGTH_SHORT).show();
                    txDoor.setText("门磁已开启");
                }
                else{
                    ivDoor.setImageResource(R.drawable.remote_button1a_a);
                }
            }
            else{
                Toast.makeText(DoorControlActivity.this, ConstantValues_bk.codeMaps.get(retCode),Toast.LENGTH_SHORT).show();
            }
        }
    }

    public void onDoorButtonClicked(View view){
        DoorTask doorTask = new DoorTask();
        doorTask.execute();
    }

    public void onBtnBackClicked(View view){
        Intent intent = new Intent();
        intent.setClass(DoorControlActivity.this, MainActivity.class);
        startActivity(intent);
        finish();
    }
}
