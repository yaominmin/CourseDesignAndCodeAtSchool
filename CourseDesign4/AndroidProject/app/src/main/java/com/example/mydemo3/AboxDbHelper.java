package com.example.mydemo3;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class AboxDbHelper extends SQLiteOpenHelper {

    private static final String DbName = "IrDb";
    private static final int version = 1;

    public AboxDbHelper(Context context) {
        super(context, DbName, null, version);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {

        String sql = "Create table if not exists IrTable(" +
                "pos int primary key, " +
                "key_name varchar not null, " +
                "flag int not null);";
        db.execSQL(sql);

        for (int i = 0; i < 15; i++) {
            ContentValues values = new ContentValues();
            values.put("pos", i);
            values.put("key_name", Integer.toString(i));
            values.put("flag", 0);
            db.insert("IrTable", null, values);
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        String sql = "drop table if exists IrTable";

        db.execSQL(sql);
        onCreate(db);
    }
}
