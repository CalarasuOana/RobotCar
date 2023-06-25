package com.example.robotcar;
import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    private final String DEVICE_ADDRESS = "00:21:11:01:E0:86"; // adresa MAC a modulului Bluetooth
    private final UUID PORT_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); // portul UUID al modulului Bluetooth
    private BluetoothAdapter bluetoothAdapter;
    private BluetoothSocket socket;
    private boolean isConnected = false;
    private String connectionStatus = "";
    private static final int REQUEST_ENABLE_BT = 1;
    private OutputStream outputStream;
    private InputStream inputStream;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);

            bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
            //verificare compatibilitate Bluetooth
            if (bluetoothAdapter == null) {
                Toast.makeText(this, "Dispozitivul nu suportă Bluetooth", Toast.LENGTH_SHORT).show();
                finish();
                return;
            }
            //verificarea permisiunilor Bluetooth
            if ((ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH) != PackageManager.PERMISSION_GRANTED)
                    || (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_ADMIN) != PackageManager.PERMISSION_GRANTED)) {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.BLUETOOTH, Manifest.permission.BLUETOOTH_ADMIN}, REQUEST_ENABLE_BT);
                return;
            }
        }
        //cerere pentru permisiunile Bluetooth
        @Override
        public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
            if (requestCode == REQUEST_ENABLE_BT) {
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    connectBluetooth();
                    return;
                }
            }
            Toast.makeText(this, "Permisiunile Bluetooth nu sunt acordate", Toast.LENGTH_SHORT).show();
            finish();
        }

        //conectarea la dispozitivul Bluetooth
        private void connectBluetooth() {
            //verificarea permisiunilor necesare pentru a utiliza Bluetooth-ul
            if ((ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH) != PackageManager.PERMISSION_GRANTED)
                    || (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_ADMIN) != PackageManager.PERMISSION_GRANTED)) {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.BLUETOOTH, Manifest.permission.BLUETOOTH_ADMIN}, REQUEST_ENABLE_BT);
            } else {
                BluetoothDevice device = bluetoothAdapter.getRemoteDevice(DEVICE_ADDRESS); //adresa modulului Bluetooth

                try {
                    socket = device.createRfcommSocketToServiceRecord(PORT_UUID); //serviciul catre care se realizeaza conexiunea Bluetooth
                    socket.connect();
                    ////trimiterea si primirea datelor de la de la dispozitivul Bluetooth
                    outputStream = socket.getOutputStream();
                    inputStream = socket.getInputStream();
                    //conexiune stabilita cu succes
                    isConnected = true;
                    //afisare mesaj
                    Toast.makeText(this, "Conexiune stabilită", Toast.LENGTH_SHORT).show();
                    //afisarea erorilor
                } catch (IOException e) {
                    e.printStackTrace();
                    Toast.makeText(this, "Eroare la conectarea Bluetooth-ului", Toast.LENGTH_SHORT).show();
                }
            }
        }

        public void onClickConnect(View view) {
            if (isConnected) {
                Toast.makeText(this, "Dispozitivul este deja conectat prin Bluetooth", Toast.LENGTH_SHORT).show();
            } else {
                connectBluetooth();
            }
        }


    public void onClickStraightButton(View view) { // butonul inainte
        Straight();
    } //click pe butonul „ÎNAINTE”
    private void Straight() {
        if (isConnected) { //verificare conexiune Bluetooth activă
            Log.d("MainActivity", "Sending 'S' command");  //se afiseaza in Logcat daca a fost trimisa comanda S
            sendCommand("S"); //trimiterea comenzii către modulul Bluetooth
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    public void onclickTurnRightButton(View view) { // butonul dreapta
        TurnRight();
    } //click pe butonul „DREAPTA”
    private void TurnRight() {
        if (isConnected) {  //verificare conexiune Bluetooth activă
            Log.d("MainActivity", "Sending 'R' command"); //se afiseaza in Logcat daca a fost trimisa comanda R
            sendCommand("R"); //trimiterea comenzii către modulul Bluetooth
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    public void onClickBackButton(View view) { // butonul inapoi
        Back();
    } //click pe butonul „ÎNAPOI”
    private void Back() {
        if (isConnected) { //verificare conexiune Bluetooth activă
            Log.d("MainActivity", "Sending 'B' command");//se afiseaza in Logcat daca a fost trimisa comanda B
            sendCommand("B"); //trimiterea comenzii către modulul Bluetooth
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    public void onclickTurnLeftButton(View view) { // butonul stanga
        TurnLeft();
    }

    private void TurnLeft() {
        if (isConnected) {
            Log.d("MainActivity", "Sending 'L' command");
            sendCommand("L");
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    public void onClickStoppButton(View view) { // butonul stop
        stop();
    }

    private void stop() {
        if (isConnected) {
            Log.d("MainActivity", "Sending 'X' command");
            sendCommand("X");
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    public void onClickBackParkingButton(View view) { // butonul garare
        backparking();
    }

    private void backparking() {
        if (isConnected) {
            Log.d("MainActivity", "Sending 'P' command");
            sendCommand("P");
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    public void onClickLateralParkingButton(View view) { // butonul parcare laterala
        lateralparking();
    }

    private void lateralparking() {
        if (isConnected) {
            Log.d("MainActivity", "Sending 'T' command");
            sendCommand("T");
        } else {
            showToast("Nu există o conectare Bluetooth");
        }
    }

    @Override
    // inchiderea conexiunii Bluetooth
    protected void onDestroy() {
        super.onDestroy();
        if (socket != null) {
            try {
                isConnected = false;
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    private void sendCommand(String command) {
        try {
            outputStream.write(command.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }
}
