/*
Copyright (c) 2016, Cypress Semiconductor Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



For more information on Cypress BLE products visit:
http://www.cypress.com/products/bluetooth-low-energy-ble
 */

package com.cypress.smartchessapp;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothManager;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.speech.RecognizerIntent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    // TAG is used for informational messages
    private final static String TAG = MainActivity.class.getSimpleName();

    // Variables to access objects from the layout such as buttons, switches, values
    private Button start_button;
    private ImageButton speech_button;
    private Button send_data_button;
    private Button disconnect_button;
    private TextView command_text_view;

    // Variables to manage BLE connection
    private static boolean mConnectState;
    private static boolean mServiceConnected;
    private static PSoCSmartChessService mPSoCSmartChessService;
    private static Handler mHandler;

    private static final int REQUEST_ENABLE_BLE = 1;

    //This is required for Android 6.0 (Marshmallow)
    private static final int PERMISSION_REQUEST_COARSE_LOCATION = 1;
    private int tempCounter = 0;
    private byte[] bytes;


    /**
     * This manages the lifecycle of the BLE service.
     * When the service starts we get the service object and initialize the service.
     */
    private final ServiceConnection mServiceConnection = new ServiceConnection() {

        /**
         * This is called when the PSoCSmartChessService is connected
         *
         * @param componentName the component name of the service that has been connected
         * @param service service being bound
         */
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            Log.i(TAG, "onServiceConnected");
            mPSoCSmartChessService = ((PSoCSmartChessService.LocalBinder) service).getService();
            mServiceConnected = true;
            mPSoCSmartChessService.initialize();
        }

        /**
         * This is called when the PSoCCapSenseService is disconnected.
         *
         * @param componentName the component name of the service that has been connected
         */
        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            Log.i(TAG, "onServiceDisconnected");
            mPSoCSmartChessService = null;
        }
    };

    /**
     * This is called when the main activity is first created
     *
     * @param savedInstanceState is any state saved from prior creations of this activity
     */
    @TargetApi(Build.VERSION_CODES.M) // This is required for Android 6.0 (Marshmallow) to work
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Set up variables for accessing buttons and slide switches
        start_button = findViewById(R.id.start_button);
        speech_button = findViewById(R.id.speech_button);
        send_data_button = findViewById(R.id.send_data);
        disconnect_button = findViewById(R.id.disconnect_button);
        command_text_view = findViewById(R.id.command_text_view);

        // Initialize service and connection state variable
        mServiceConnected = false;
        mConnectState = false;

        speech_button.setImageResource(R.drawable.ic_mic_black_24dp);

        mHandler = new Handler();

        //This section required for Android 6.0 (Marshmallow)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Android M Permission check 
            if (this.checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                final AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setTitle("This app needs location access ");
                builder.setMessage("Please grant location access so this app can detect devices.");
                builder.setPositiveButton(android.R.string.ok, null);
                builder.setOnDismissListener(new DialogInterface.OnDismissListener() {
                    public void onDismiss(DialogInterface dialog) {
                        requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, PERMISSION_REQUEST_COARSE_LOCATION);
                    }
                });
                builder.show();
            }
        } //End of section for Android 6.0 (Marshmallow)
    }

    //This method required for Android 6.0 (Marshmallow)
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String permissions[], @NonNull int[] grantResults) {
        switch (requestCode) {
            case PERMISSION_REQUEST_COARSE_LOCATION: {
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Log.d("Permission for 6.0:", "Coarse location permission granted");
                } else {
                    final AlertDialog.Builder builder = new AlertDialog.Builder(this);
                    builder.setTitle("Functionality limited");
                    builder.setMessage("Since location access has not been granted, this app will not be able to discover beacons when in the background.");
                    builder.setPositiveButton(android.R.string.ok, null);
                    builder.setOnDismissListener(new DialogInterface.OnDismissListener() {
                        @Override
                        public void onDismiss(DialogInterface dialog) {
                        }
                    });
                    builder.show();
                }
            }
        }
    } //End of section for Android 6.0 (Marshmallow)

    public void getSpeechInput(View view) {

        Intent intent = new Intent( RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());

        if (intent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(intent, 10);
        } else {
            Toast.makeText(this, "Your Device Don't Support Speech Input",
                    Toast.LENGTH_SHORT).show();
        }
    }



    @Override
    protected void onResume() {
        super.onResume();
        // Register the broadcast receiver. This specified the messages the main activity looks for from the PSoCSmartChessService
        final IntentFilter filter = new IntentFilter();
        filter.addAction( PSoCSmartChessService.ACTION_BLESCAN_CALLBACK);
        filter.addAction( PSoCSmartChessService.ACTION_CONNECTED);
        filter.addAction( PSoCSmartChessService.ACTION_DISCONNECTED);
        filter.addAction( PSoCSmartChessService.ACTION_SERVICES_DISCOVERED);
        filter.addAction( PSoCSmartChessService.ACTION_DATA_RECEIVED);
        registerReceiver(mBleUpdateReceiver, filter);
    }

/*    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);


    }*/

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // User chose not to enable Bluetooth.
        switch (requestCode) {
            case 10:
                if (resultCode == RESULT_OK && data != null) {
                    ArrayList<String> result =
                            data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    String string = result.get(0);
                    List<String> items = Arrays.asList(string.split("\\s* \\s*"));
                    byte[] bytes = { (byte) items.get(0).toLowerCase().charAt(0),
                            (byte) items.get(1).toLowerCase().charAt(0)};
                    String commandString = new String(bytes);
                    setBytes(bytes);
                    command_text_view.setText( String.format( "Command is: %s", commandString ) );
                }
                break;
        }

        if (requestCode == REQUEST_ENABLE_BLE && resultCode == Activity.RESULT_CANCELED) {
            finish();
            return;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    private void setBytes(byte[] bytes) {
        this.bytes = bytes;
    }

    private byte[] getBytes() {
        return bytes;
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mBleUpdateReceiver);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Close and unbind the service when the activity goes away
        mPSoCSmartChessService.close();
        unbindService(mServiceConnection);
        mPSoCSmartChessService = null;
        mServiceConnected = false;
    }

    /**
     * This method handles the start bluetooth button
     *
     * @param view the view object
     */
    public void startBluetooth(View view) {

        // Find BLE service and adapter
        final BluetoothManager bluetoothManager =
                (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        BluetoothAdapter mBluetoothAdapter = bluetoothManager.getAdapter();

        // Ensures Bluetooth is enabled on the device.  If Bluetooth is not currently enabled,
        // fire an intent to display a dialog asking the user to grant permission to enable it.
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BLE);
        }

        // Start the BLE Service
        Log.d(TAG, "Starting BLE Service");
        Intent gattServiceIntent = new Intent(this, PSoCSmartChessService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        // Disable the start button and turn on the search  button
        start_button.setEnabled(false);
        //search_button.setEnabled(true);
        Log.d(TAG, "Bluetooth is Enabled");

        searchBluetooth(view);
    }

    /**
     * This method handles the Search for Device button
     *
     * @param view the view object
     */
    public void searchBluetooth(final View view) {
        mHandler.postDelayed( new Runnable() {
            @Override
            public void run() {
                if(mServiceConnected) {
                    mPSoCSmartChessService.scan();
                }
                connectBluetooth(view);
            }
        }, 2500 );


        /* After this we wait for the scan callback to detect that a device has been found */
        /* The callback broadcasts a message which is picked up by the mGattUpdateReceiver */
    }

    public void sendData(View view) {
        byte[] byteValues = getBytes();
        tempCounter++;
        /*byteValues[0] = (byte) chars[0];
        byteValues[1] = (byte) chars[1];*/
        /*if(tempCounter == 1) {
            byteValues[0] = (byte) (97);
            byteValues[1] = (byte) (49);
        } else if(tempCounter == 2) {
            byteValues[0] = (byte) (98);
            byteValues[1] = (byte) (50);
            tempCounter = 0;
        }*/

        mPSoCSmartChessService.writeCommandCharacteristic(byteValues);
    }

    /**
     * This method handles the Connect to Device button
     *
     * @param view the view object
     */
    public void connectBluetooth(final View view) {
        mHandler.postDelayed( new Runnable() {
            @Override
            public void run() {
                mPSoCSmartChessService.connect();
                discoverServices(view);
            }
        }, 500 );

        /* After this we wait for the gatt callback to report the device is connected */
        /* That event broadcasts a message which is picked up by the mGattUpdateReceiver */
    }

    /**
     * This method handles the Discover Services and Characteristics button
     *
     * @param view the view object
     */
    public void discoverServices(View view) {
        /* This will discover both services and characteristics */
        mHandler.postDelayed( new Runnable() {
            @Override
            public void run() {
                mPSoCSmartChessService.discoverServices();
            }
        }, 500);


        /* After this we wait for the gatt callback to report the services and characteristics */
        /* That event broadcasts a message which is picked up by the mGattUpdateReceiver */
    }

    /**
     * This method handles the Disconnect button
     *
     * @param view the view object
     */
    public void Disconnect(View view) {
        mPSoCSmartChessService.disconnect();
        start_button.setEnabled(true);
        /* After this we wait for the gatt callback to report the device is disconnected */
        /* That event broadcasts a message which is picked up by the mGattUpdateReceiver */
    }

    /**
     * Listener for BLE event broadcasts
     */
    private final BroadcastReceiver mBleUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            switch (action) {
                case PSoCSmartChessService.ACTION_BLESCAN_CALLBACK:
                    break;

                case PSoCSmartChessService.ACTION_CONNECTED:
                    if (!mConnectState) {
                        disconnect_button.setEnabled(true);
                        send_data_button.setEnabled(true);
                        //speech_button.setEnabled(true);
                        mConnectState = true;
                        Log.d(TAG, "Connected to Device");
                    }
                    break;
                case PSoCSmartChessService.ACTION_DISCONNECTED:
                    // Disable the disconnect, discover svc, discover char button, and enable the search button
                    disconnect_button.setEnabled(false);
                    send_data_button.setEnabled(false);
                    //speech_button.setEnabled(false);
                    mConnectState = false;
                    Log.d(TAG, "Disconnected");
                    break;
                case PSoCSmartChessService.ACTION_SERVICES_DISCOVERED:
                    Log.d(TAG, "Services Discovered");
                    break;
                case PSoCSmartChessService.ACTION_DATA_RECEIVED:
                default:
                    break;
            }
        }
    };
}