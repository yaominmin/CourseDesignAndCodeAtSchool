package com.example.mydemo3;

import android.content.ContentValues;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;

public class Rename2Activity extends AppCompatActivity {

    Button btnConfirm;
    Button btnCancel;
    Button btnRedo;
    SQLiteDatabase db;
    int pos;
    String name;
    String deviceName;
    EditText edPos;
    EditText edName;
    Intent intent;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rename2);
        intent = new Intent(Rename2Activity.this, RemoteActivity.class);
        db = new AboxDbHelper(this).getWritableDatabase();
        edPos = findViewById(R.id.edPos);
        edName = findViewById(R.id.edName);
        pos = getIntent().getIntExtra("pos", 0);
        name = getIntent().getStringExtra("name");
        deviceName = getIntent().getStringExtra("dev");
        edPos.setText(Integer.toString(pos));
        edName.setText(name);
        btnConfirm = findViewById(R.id.btnConfirm);
        btnConfirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RemoteActivity.remoteButtonList.get(pos).setKeyName(edName.getText().toString());
                ContentValues values = new ContentValues();

                values.put("key_name", edName.getText().toString());
//                values.put("flag", 1);
                String where = "pos=?";
                String[] whereArgs ={Integer.toString(pos)};
                db.update("IrTable", values, where, whereArgs);
                startActivity(intent);
                finish();
            }
        });
        btnCancel = findViewById(R.id.btnCancel);
        btnCancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(intent);
                finish();
            }
        });
        btnRedo = findViewById(R.id.btnRelearn);
        btnRedo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LearnTask learnTask = new LearnTask();
                learnTask.execute();
            }
        });
    }

    public class LearnTask extends AsyncTask<Void,Void, ABRet> {
        @Override
        protected ABRet doInBackground(Void... voids) {

            ABRet abRet = ABSDK.getInstance().
                    studyIrByIrDevName(deviceName,Integer.toString(pos));

            return abRet;
        }

        @Override
        protected void onPostExecute(ABRet abRet) {
            super.onPostExecute(abRet);
            String retCode = abRet.getCode();
            if(retCode.equals("00000")){
                Toast.makeText(Rename2Activity.this,
                        "学习成功",Toast.LENGTH_SHORT).show();

                RemoteActivity.remoteButtonList.get(pos).setLearnFlag(1);
                // Update data
                    ContentValues values = new ContentValues();
                    values.put("key_name", edName.getText().toString());
                    values.put("flag", 1);
                    String where = "pos=?";
                    String[] whereArgs = {Integer.toString(pos)};
                    db.update("IrTable", values, where, whereArgs);

                Intent intent = new Intent();
                intent.setClass(Rename2Activity.this, RemoteActivity.class).putExtra("pos",pos);
                startActivity(intent);
                finish();
            }else{
                Toast.makeText(Rename2Activity.this,
                        "(" + retCode + ")" + ConstValues.getInfo(retCode),
                        Toast.LENGTH_SHORT).show();
            }

        }

    }


}
