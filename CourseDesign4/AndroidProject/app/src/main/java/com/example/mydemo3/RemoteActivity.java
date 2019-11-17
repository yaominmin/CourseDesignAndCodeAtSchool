package com.example.mydemo3;

import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;


import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;

import java.util.ArrayList;

public class RemoteActivity extends AppCompatActivity{

    GridView gridViewRemoteLayout;
    RemoteAdapter remoteAdapter;
    SQLiteDatabase sqLiteDatabase;
    RemoteButtonBean remoteButtonBean;
    static ArrayList<RemoteButtonBean> remoteButtonList = new ArrayList<>();
    String buttonName;
    int buttonPos;
    int funcChoice;

    String deviceName = "红外控制器";



@Override
    protected void onCreate(Bundle savedInstanceState) {
        AboxDbHelper aboxDbHelper = new AboxDbHelper(this);
        try {
            sqLiteDatabase = aboxDbHelper.getWritableDatabase();
        }
        catch (Exception e) {
            Toast.makeText(this,
                    "由于内存不足，数据库无法写入，只可读取。", Toast.LENGTH_SHORT);
        }

        Cursor cur = sqLiteDatabase.query(
                "IrTable",
                new String[]{"pos", "key_name", "flag"},
                null, null, null,
                null, null);
        while (cur.moveToNext()) {
            int pos = cur.getInt(0);
            String keyName = cur.getString(1);
            int flag = cur.getInt(2);
            RemoteButtonBean r = new RemoteButtonBean(pos, keyName, 1, flag);
            remoteButtonList.add(r);
        }

        super.onCreate(savedInstanceState);
        setContentView(R.layout.remote_layout);



        gridViewRemoteLayout =(GridView) findViewById(R.id.gridViewRemote);
        remoteAdapter = new RemoteAdapter();
        gridViewRemoteLayout.setAdapter(remoteAdapter);
        gridViewRemoteLayout.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                // remote button click event
                Log.e("pos:", String.valueOf(position));
                buttonPos = position;
                if (remoteButtonList.get(buttonPos).getLearnFlag() == 0) {
                    Toast.makeText(RemoteActivity.this,
                            "开始学习，请输入红外信号", Toast.LENGTH_SHORT).show();
                    LearnTask learnTask = new LearnTask();
                    learnTask.execute();
                }
                else {
                    SendTask sendTask = new SendTask();
                    sendTask.execute();
                }
            }
        });

        gridViewRemoteLayout.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {

            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                buttonPos = position;
                Intent intent = new Intent(RemoteActivity.this, Rename2Activity.class);
                intent.putExtra("pos", buttonPos);
                intent.putExtra("name", remoteButtonList.get(buttonPos).getKeyName());
                intent.putExtra("dev", deviceName);
                startActivity(intent);
                finish();
                return true;
            }
        });

    }

    public class RemoteAdapter extends BaseAdapter{

        @Override
        public int getCount() {
            return 15;
        }

        @Override
        public Object getItem(int position) {
            return position;
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            View view;
            TextView textViewKeyName = null;
            ImageView imageViewRemoteButton = null;
            if(convertView==null){
                LayoutInflater layoutInflater= getLayoutInflater();
                view = layoutInflater.inflate(R.layout.remote_button_layout,null);
                convertView = view;
                textViewKeyName = view.findViewById(R.id.textViewKeyName);

                imageViewRemoteButton = view.findViewById(R.id.imageViewRemoteButton);
            }
            else{
                textViewKeyName = convertView.findViewById(R.id.textViewKeyName);
                imageViewRemoteButton = convertView.findViewById(R.id.imageViewRemoteButton);
            }
            if(remoteButtonList.get(position).getLearnFlag()==0){
                imageViewRemoteButton.setImageResource(R.drawable.remote_button1a_a);
            } else  {
                imageViewRemoteButton.setImageResource(R.drawable.remote_button1a_b);
            }
            textViewKeyName.setText(remoteButtonList.get(position).keyName);
            return convertView;
        }
    }

        public class LearnTask extends AsyncTask<Void,Void, ABRet> {
            @Override
            protected ABRet doInBackground(Void... voids) {

                ABRet abRet = ABSDK.getInstance().
                        studyIrByIrDevName(deviceName,Integer.toString(buttonPos));

                return abRet;
            }

            @Override
            protected void onPostExecute(ABRet abRet) {
                super.onPostExecute(abRet);
                String retCode = abRet.getCode();
                if(retCode.equals("00000")){
                    Toast.makeText(RemoteActivity.this,
                            "学习成功",Toast.LENGTH_SHORT).show();

                    remoteButtonList.get(buttonPos).setLearnFlag(1);;
                    // Update data
                    ContentValues values = new ContentValues();
                    values.put("key_name", remoteButtonList.get(buttonPos).getKeyName() + "已学习");
                    values.put("flag", 1);
                    String where = "pos=?";
                    String[] whereArgs = {Integer.toString(buttonPos)};
                    sqLiteDatabase.update("IrTable", values, where, whereArgs);

//                    Intent intent = new Intent();
//                    intent.setClass(RemoteActivity.this, RenameActivity.class);
//                    intent.putExtra("pos",buttonPos);
//                    startActivity(intent);
//                    finish();
                }else{
                    Toast.makeText(RemoteActivity.this,
                            "(" + retCode + ")" + ConstValues.getInfo(retCode),
                            Toast.LENGTH_SHORT).show();
                }

            }

        }

        public class SendTask extends AsyncTask<Void, Void, ABRet> {
            @Override
            protected ABRet doInBackground(Void... voids) {
                return ABSDK.getInstance().sendIr(deviceName, Integer.toString(buttonPos));
            }

            @Override
            protected void onPostExecute(ABRet abRet) {
                super.onPostExecute(abRet);
                String code = abRet.getCode();
                if(code.equals("00000")) {
                    Toast.makeText(RemoteActivity.this,
                            "信号发送成功", Toast.LENGTH_SHORT).show();
                }
                else {
                    Toast.makeText(RemoteActivity.this,
                            ConstValues.getInfo(code) + "(" + code + ")",
                            Toast.LENGTH_SHORT).show();
                }
            }
        }


    public void onButtonToLogin(View view){
        Intent intent = new Intent();
        intent.setClass(RemoteActivity.this, MainActivity.class);
        startActivity(intent);
        finish();
    }


}
