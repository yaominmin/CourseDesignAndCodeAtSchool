package com.example.mydemo3;

import android.content.ContentValues;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class RenameActivity extends AppCompatActivity {
    Button btnchange;
    TextView tvpos;
    TextView tvkeyName;
    SQLiteDatabase sqLiteDatabase;
    int pos;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        AboxDbHelper aboxDbHelper = new AboxDbHelper(this);
            sqLiteDatabase = aboxDbHelper.getWritableDatabase();

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rename);
        Intent intent = getIntent();
        pos = intent.getIntExtra("pos",0);
        btnchange=findViewById(R.id. btnchange);
        tvpos=findViewById(R.id.edt_pos);
        tvpos.setText(Integer.toString(pos));
        tvkeyName=findViewById(R.id.edt_keyname);

        btnchange.setOnClickListener(new View.OnClickListener(){

            public void onClick(View v){
                String pos=tvpos.getText().toString();
                String keyname=tvkeyName.getText().toString();

                ContentValues values = new ContentValues();

                values.put("key_name", keyname);
                values.put("flag", 1);
                String where = "pos=?";
                String[] whereArgs ={pos};
                sqLiteDatabase.update("IrTable", values, where, whereArgs);

                    Intent intent=new Intent();
                    intent.setClass(RenameActivity.this,RemoteActivity.class);
                    startActivity(intent);
                    finish();
            };
        });


    }
}
