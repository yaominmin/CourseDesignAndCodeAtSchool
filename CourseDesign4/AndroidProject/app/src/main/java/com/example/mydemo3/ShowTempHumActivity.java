package com.example.mydemo3;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;

public class ShowTempHumActivity extends AppCompatActivity {
    static String minTem = "23",maxTem = "28",minHum = "45",maxHum = "65";
    TextView tvtem;
    TextView tvhum;
    Button btn_set;
    ImageView ivTem,ivHum;
    Intent intent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tah);
        intent = this.getIntent();
        ShowTempHumTask showTempHumTask = new ShowTempHumTask();
        showTempHumTask.execute();
    }

//    @Override
//    protected void onRestart() {
//        super.onRestart();
//        setContentView(R.layout.activity_tah);
//        intent = this.getIntent();
//        ShowTempHumTask showTempHumTask = new ShowTempHumTask();
//        showTempHumTask.execute();
//    }

    public class ShowTempHumTask extends AsyncTask<Void,Void, Void> {
        @Override
        protected Void doInBackground(Void... voids) {
            btn_set = findViewById(R.id.button_set);
            ivTem = findViewById(R.id.iv_tem);
            ivHum = findViewById(R.id.iv_hum);
            tvhum = findViewById(R.id.tvhum);
            tvtem = findViewById(R.id.tvtem);
            tvtem.setText(MainActivity.tem);
            tvhum.setText(MainActivity.hum);

            if (intent.getStringExtra("mintem") != null) {
                minTem = intent.getStringExtra("mintem");
                maxTem = intent.getStringExtra("maxtem");
                minHum = intent.getStringExtra("minHum");
                maxHum = intent.getStringExtra("maxHum");
            }
            if(Double.parseDouble(MainActivity.tem) < Double.parseDouble(maxTem)
                    && Double.parseDouble(MainActivity.tem)>Double.parseDouble(minTem)){
                ivTem.setImageResource(R.drawable.smile);
            }else{
                ivTem.setImageResource(R.drawable.sad);
            }
            if(Double.parseDouble(MainActivity.hum)<Double.parseDouble(maxHum)
                    &&Double.parseDouble(MainActivity.hum)>Double.parseDouble(minHum)){
                ivHum.setImageResource(R.drawable.smile);
            }else{
                ivHum.setImageResource(R.drawable.sad);
            }

            btn_set.setOnClickListener(new View.OnClickListener(){

                @Override
                public void onClick(View v) {
                    Intent intent = new Intent();
                    intent.setClass(ShowTempHumActivity.this,TahSetActivity.class);
                    startActivity(intent);
                    finish();
                }
            });

            return null;
        }

        protected void onPostExecute() {
            super.onPostExecute(null);
        }
    }

    public void onBtnBackClicked(View view){
        Intent intent = new Intent();
        intent.setClass(ShowTempHumActivity.this, MainActivity.class);
        startActivity(intent);
        finish();
    }
}
