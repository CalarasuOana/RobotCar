package com.example.robotcar;
import com.example.robotcar.MainActivity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class LoginActivity extends AppCompatActivity {
    private EditText editTextUsername;
    private EditText editTextPassword;
    private Button buttonLogin;
    private Button buttonCreateAccount;
    private EditText editTextNewPassword; //camp pentru parola noua
    private EditText editTextConfirmPassword; //camp pentru parola confirmata

    private DatabaseHelper databaseHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        editTextUsername = findViewById(R.id.editTextUsername); //introducere nume utilizator
        editTextPassword = findViewById(R.id.editTextPassword); //parola
        buttonLogin = findViewById(R.id.buttonLogin);
        buttonCreateAccount = findViewById(R.id.buttonCreateAccount); //creare cont
        editTextNewPassword = findViewById(R.id.editTextNewPassword); //parola noua
        editTextConfirmPassword = findViewById(R.id.editTextPasswordConfirm); //parola confirmata
        //campuri invizibile
        editTextNewPassword.setVisibility(View.GONE);
        editTextConfirmPassword.setVisibility(View.GONE);

        databaseHelper = new DatabaseHelper(this);

        buttonLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String username = editTextUsername.getText().toString().trim();
                String password = editTextPassword.getText().toString().trim();

                if (TextUtils.isEmpty(username)) { //verificare camp nume gol
                    Toast.makeText(LoginActivity.this, "Introducere nume", Toast.LENGTH_SHORT).show();
                    return;
                }

                if (TextUtils.isEmpty(password)) { //verificare camp parola gol
                    Toast.makeText(LoginActivity.this, "Introducere parola", Toast.LENGTH_SHORT).show();
                    return;
                }

                if (authenticateUser(username, password)) {
                    Toast.makeText(LoginActivity.this, "Autentificare reușită.", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                    startActivity(intent);
                    finish();
                } else {
                    Toast.makeText(LoginActivity.this, "Nume sau parolă incorecte.", Toast.LENGTH_SHORT).show();
                }
            }
        });
        //interfata de creare cont de utilizator
        buttonCreateAccount.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (editTextNewPassword.getVisibility() == View.VISIBLE) {
                    String username = editTextUsername.getText().toString().trim();
                    String newPassword = editTextNewPassword.getText().toString().trim();
                    String confirmPassword = editTextConfirmPassword.getText().toString().trim();

                    if (TextUtils.isEmpty(username)) {
                        Toast.makeText(LoginActivity.this, "Introducere nume", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (TextUtils.isEmpty(newPassword)) {
                        Toast.makeText(LoginActivity.this, "Introducere noua parola", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (TextUtils.isEmpty(confirmPassword)) {
                        Toast.makeText(LoginActivity.this, "Introducere confirmare parolă", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (!newPassword.equals(confirmPassword)) { //verificare daca parola noua cu cea confirmata coincide
                        Toast.makeText(LoginActivity.this, "Parola noua si confirmarea parolei nu se potrivesc", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (isUsernameTaken(username)) {
                        Toast.makeText(LoginActivity.this, "Numele de utilizator există deja.", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    //restrictii
                    if (newPassword.length() < 6) { //parola mai mica de 6 caractere
                        Toast.makeText(LoginActivity.this, "Parola trebuie să conțină cel puțin 6 caractere", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (!newPassword.matches("^(?=.*[A-Za-z])(?=.*\\d).+$")) { // formatul parolei nu contine cel putin o litera si o cifra
                        Toast.makeText(LoginActivity.this, "Parola trebuie să conțină cel puțin o literă și o cifră", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (username.length() >= 10) { // numele de utilizator mai mare de 10 caractere
                        Toast.makeText(LoginActivity.this, "Numele de utilizator trebuie să aibă mai puțin de 10 caractere", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    if (createUser(username, newPassword, confirmPassword)) {
                        Toast.makeText(LoginActivity.this, "Contul a fost creat cu succes.", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(LoginActivity.this, "A apărut o eroare la crearea contului.", Toast.LENGTH_SHORT).show();
                    }
                    //golire campuri
                    editTextNewPassword.setText("");
                    editTextConfirmPassword.setText("");
                    //campurile devin vizibile
                    editTextNewPassword.setVisibility(View.GONE);
                    editTextConfirmPassword.setVisibility(View.GONE);
                    editTextPassword.setVisibility(View.VISIBLE);
                    buttonCreateAccount.setText("Creează cont");
                } else {
                    editTextNewPassword.setVisibility(View.VISIBLE);
                    editTextConfirmPassword.setVisibility(View.VISIBLE);
                    editTextPassword.setVisibility(View.GONE); //devine invizibil
                    buttonCreateAccount.setText("Finalizează creare cont"); //textul butonului se schimba
                }
            }
        });
    }

    private boolean authenticateUser(String username, String password) {
        SQLiteDatabase db = databaseHelper.getReadableDatabase(); // referinta la baza de date
        String[] projection = {DatabaseHelper.COLUMN_PASSWORD}; //selectia pentru coloana parolei
        //clauza de selectie -> numele de utilizator trebuie sa fie egal cu numele de utilizator furnizat
        String selection = DatabaseHelper.COLUMN_USERNAME + " = ?";
        String[] selectionArgs = {username};
        //interogarea bazei de date
        try (Cursor cursor = db.query( //cursor cu rezultatele interogarii
                DatabaseHelper.TABLE_USERS,
                projection,
                selection,
                selectionArgs,
                null,
                null,
                null
        )) {
            if (cursor != null && cursor.moveToFirst()) {
                //se obtine valoarea stocata a parolei
                String storedPassword = cursor.getString(cursor.getColumnIndexOrThrow(DatabaseHelper.COLUMN_PASSWORD));
                //criptarea parolei
                String hashedPassword = hashPassword(password);
                if (hashedPassword != null && hashedPassword.equals(storedPassword)) {
                    return true;
                }
            }
        } catch (Exception e) {
            Log.e("LoginActivity", "Error authenticating user: " + e.getMessage());
        }

        return false;
    }
    //crearea unui nou utilizator in baza de date
    private boolean createUser(String username, String password, String confirmPassword) {
        if (isUsernameTaken(username)) {
            return false;
        }
        SQLiteDatabase db = databaseHelper.getWritableDatabase();
        ContentValues values = new ContentValues();//înregistrarea unui nou utilizator în tabela TABLE_USERS
        values.put(DatabaseHelper.COLUMN_USERNAME, username);
        values.put(DatabaseHelper.COLUMN_PASSWORD, hashPassword(confirmPassword));
        //id-ul noului rand inserat in baza de date
        long newRowId = db.insert(DatabaseHelper.TABLE_USERS, null, values);
        db.close();

        return newRowId != -1;
    }
    //verificare cont existent in baza de date
    private boolean isUsernameTaken(String username) {
        SQLiteDatabase db = databaseHelper.getReadableDatabase();
        String[] projection = {DatabaseHelper.COLUMN_USERNAME};
        String selection = DatabaseHelper.COLUMN_USERNAME + " = ?";
        String[] selectionArgs = {username};
        try (Cursor cursor = db.query(
                DatabaseHelper.TABLE_USERS,
                projection,
                selection,
                selectionArgs,
                null,
                null,
                null
        )) {
            return cursor != null && cursor.moveToFirst();
        } catch (Exception e) {
            Log.e("LoginActivity", "Error checking username availability: " + e.getMessage());
        }

        return true;
    }
    //criptarea parolei
    private String hashPassword(String password) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] encodedHash = digest.digest(password.getBytes(StandardCharsets.UTF_8)); //convertirea in sir de octeti

            StringBuilder hexString = new StringBuilder();
            for (byte b : encodedHash) {
                String hex = Integer.toHexString(0xff & b); //convertirea parolei intr-un sir hexadecimal
                if (hex.length() == 1) {
                    hexString.append('0');
                }
                hexString.append(hex);
            }
            return hexString.toString();
            //exceptie
        } catch (NoSuchAlgorithmException e) {
            Log.e("LoginActivity", "Error hashing password: " + e.getMessage());
        }
        return null;
    }
}
