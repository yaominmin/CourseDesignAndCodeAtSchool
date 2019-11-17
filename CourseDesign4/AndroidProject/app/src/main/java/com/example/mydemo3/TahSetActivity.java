package com.example.mydemo3;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;

public class TahSetActivity extends AppCompatActivity {

    private static String minTem = "23", maxTem = "28", minHum = "45", maxHum = "65";
    EditText etminTem;
    EditText etmaxTem;
    EditText etminHum;
    EditText etmaxHum;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tah_set);
        etminTem = findViewById(R.id.etMinTem);
        etmaxTem = findViewById(R.id.etMaxTem);
        etminHum = findViewById(R.id.etMinHum);
        etmaxHum = findViewById(R.id.etMaxHum);
        etminTem.setText(minTem);
        etmaxTem.setText(maxTem);
        etminHum.setText(minHum);
        etmaxHum.setText(maxHum);
    }

    public void onConfirmButtonClicked(View view) {
        minTem = etminTem.getText().toString();
        maxTem = etmaxTem.getText().toString();
        minHum = etminHum.getText().toString();
        maxHum = etmaxHum.getText().toString();
        Intent intent = new Intent();
        intent.putExtra("mintem", minTem);
        intent.putExtra("maxtem", maxTem);
        intent.putExtra("minHum", minHum);
        intent.putExtra("maxHum", maxHum);
        intent.setClass(TahSetActivity.this, ShowTempHumActivity.class);
        startActivity(intent);
        finish();
    }
}
