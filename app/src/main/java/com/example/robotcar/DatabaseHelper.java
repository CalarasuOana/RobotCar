package com.example.robotcar;
import android.content.Context;
import android.content.res.AssetManager;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
    public class DatabaseHelper extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "users.sql"; //numele bazei de date
    private static final int DATABASE_VERSION = 1;
    private final Context context;
    static final String TABLE_USERS = "users"; //numele tabelului
    //numele coloanelor
    static final String COLUMN_ID = "id";
    static final String COLUMN_USERNAME = "username";
    static final String COLUMN_PASSWORD = "password";

    //gestionarea bazei de date
    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
        this.context = context;
        copyDatabase();
    }
    //crearea tabelului users
    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTableQuery = "CREATE TABLE " + TABLE_USERS + "("
                + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                + COLUMN_USERNAME + " TEXT,"
                + COLUMN_PASSWORD + " TEXT)";
        db.execSQL(createTableQuery);
    }

    @Override
    //crearea unei noi versiuni a tabelei
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_USERS);
        onCreate(db);
    }

    private void copyDatabase() {
        if (!checkDatabaseExists()) {
            //verificare existenta baza de date in directorul aplicatiei
            try {
                InputStream inputStream = context.getAssets().open(DATABASE_NAME);
                //calea catre fisierul de iesire
                String outFileName = context.getDatabasePath(DATABASE_NAME).getPath();
                OutputStream outputStream = new FileOutputStream(outFileName);

                byte[] buffer = new byte[1024];
                int length;
                while ((length = inputStream.read(buffer)) > 0) {
                    outputStream.write(buffer, 0, length);
                }

                outputStream.flush();
                outputStream.close();
                inputStream.close();
            } catch (IOException e) {
                Log.e("DatabaseHelper", "Error copying database: " + e.getMessage());
            }
        }
    }

    public boolean checkDatabaseExists() {
        File databaseFile = context.getDatabasePath(DATABASE_NAME);
        return databaseFile.exists();
    }
}
