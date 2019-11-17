package com.example.mydemo3;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
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

public class SocketControlActivity extends AppCompatActivity {

    static  final String sockName = "Zigbee插座控制器2";
    static  final String on = "1";
    static  final String off = "0";
    static  final String success= "00000";
    ImageView image_sock;
    TextView textViewSockStatus;
    String status;
    private static final int COMPLETED = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_socket_control);
        ActionBar actionBar = getSupportActionBar();
        if(actionBar != null){
            actionBar.setHomeButtonEnabled(true);
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
        GetSockStatusTask getSockStatusTask = new GetSockStatusTask();
        getSockStatusTask.execute();
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                this.finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    //获取状态的task
    public class GetSockStatusTask extends AsyncTask<Void,Void, ABRet> {

        @Override//后台
        protected ABRet doInBackground(Void... voids) {
            ABRet tokenStatus = ABSDK.getInstance().isValidateToken();
            String retCode = tokenStatus.getCode();
            ABRet ret = new ABRet();
            //如果成功验证
            if (retCode.equals(success)) {
                //如果token有效
                if (tokenStatus.getDicDatas().get("status").toString().equals(on)) {
                    ret = ABSDK.getInstance().getSockStatus(sockName);
                    //获得插座详细状态
                    Map<String, Object> statusMap = ret.getDicDatas();
                    status = statusMap.get("status").toString();
                    System.out.println(status);
                    //设置图片
                    if (status.equals(on)) {
                        setSockOn();
                    }
                }
            } else
                Toast.makeText(SocketControlActivity.this, retCode+ConstantValues_bk.codeMaps.get(retCode), Toast.LENGTH_SHORT).show();
            return ret;
        }

        @Override//前台
        protected void onPostExecute(ABRet abRet) {
            super.onPostExecute(abRet);
        }
    }

    //控制task
    public class SwitchTask extends AsyncTask<Void,Void, ABRet> {

        @Override//后端
        protected ABRet doInBackground(Void... voids) {
            ABRet ret = ABSDK.getInstance().getSockStatus(sockName);
            Map statusMap =ret.getDicDatas();
            status = statusMap.get("status").toString();
            //如果关闭，就开启
            if(status.equals(off)){
                Log.d("ymm","turn on");
                ret = ABSDK.getInstance().sockCtrl(sockName,on);
                setSockOn();
            }
            //如果开启，就关闭
            else if(status.equals(on)){
                Log.d("ymm","turn off");
                ret = ABSDK.getInstance().sockCtrl(sockName,off);
                setSockOff();
            }
            return  ret;
        }

        @Override//前台
        protected void onPostExecute(ABRet abRet) {
            super.onPostExecute(abRet);
            String ctrlCode = abRet.getCode();
            if(ctrlCode.equals(success)){
                Toast.makeText(SocketControlActivity.this, "成功", Toast.LENGTH_SHORT).show();
            }else{
                Toast.makeText(SocketControlActivity.this, "错误："+ctrlCode+ConstantValues_bk.codeMaps.get(ctrlCode), Toast.LENGTH_SHORT).show();
            }
        }
    }

    //点击按钮执行
    public void onPushImageSock(View view){
        SwitchTask switchTask = new SwitchTask();
        switchTask.execute();
    }

    //进程间通信
    private Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            if (msg.what == COMPLETED) {
                if(status.equals(off)){
                    image_sock = findViewById(R.id.imageView_sock);
                    image_sock.setImageResource(R.drawable.sock_on);
                    textViewSockStatus = findViewById( R.id.textView_Sock_Status );
                    textViewSockStatus.setText( "插座开启" );
                }else{
                    image_sock = findViewById(R.id.imageView_sock);
                    image_sock.setImageResource(R.drawable.sock_off);
                    textViewSockStatus = findViewById( R.id.textView_Sock_Status );
                    textViewSockStatus.setText( "插座关闭" );
                }
            }
        }
    };

    public void setSockOn(){
        Message message = new Message();
        message.what = COMPLETED;
        handler.sendMessage(message);
    }

    public void setSockOff(){
        Message message = new Message();
        message.what = COMPLETED;
        handler.sendMessage(message);
    }

    public void onBtnBackClicked(View view){
        Intent intent = new Intent();
        intent.setClass(SocketControlActivity.this, MainActivity.class);
        startActivity(intent);
        finish();
    }

}