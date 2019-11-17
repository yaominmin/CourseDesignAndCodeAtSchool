package com.example.mydemo3;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Toast;

import com.dhc.absdk.ABRet;
import com.dhc.absdk.ABSDK;

public class LoginActivity extends AppCompatActivity {

    private CheckBox checkRememberMe;
    private EditText edUsr;
    private EditText edPwd;
    private String usr;
    private String pwd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        edUsr = this.findViewById(R.id.edUsr);
        edPwd = this.findViewById(R.id.edPwd);

        checkRememberMe = this.findViewById(R.id.checkBox);
    }

    public void onLoginButtonClicked(View view) {
        usr = edUsr.getText().toString();
        pwd = edPwd.getText().toString();
        LoginTask loginTask = new LoginTask();
        loginTask.execute();
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
            String code = abRet.getCode();
            // Toast.makeText(LoginActivity.this, code, Toast.LENGTH_SHORT).show();

            // Check code returned (if - else)
            if(code.equals("00000")) {

                // Save data to file
                if (checkRememberMe.isChecked()) {
                    SharedPreferences sharedPreferences =
                            getSharedPreferences(ConstValues.SP_FILE, MODE_PRIVATE);
                    sharedPreferences.edit().putString(ConstValues.SP_USR, usr)
                            .putString(ConstValues.SP_PWD, pwd).apply();
                }
                // Toast.makeText(LoginActivity.this, "Done", Toast.LENGTH_SHORT);
                // Switch to menu
                Intent intent =
                        new Intent(LoginActivity.this, MainActivity.class);
                startActivity(intent);
                finish();
            }
            else {
                Toast.makeText(LoginActivity.this,
                        ConstValues.getInfo(code), Toast.LENGTH_SHORT).show();
            }
        }
    }
}
