package com.cypress.smartchessapp;

import android.Manifest;
import android.annotation.TargetApi;
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
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.cypress.smartchessapp.Fragments.FragmentNavigation;
import com.cypress.smartchessapp.Fragments.PVPFragment;

public class TestActivity extends AppCompatActivity {
    private final static String TAG = TestActivity.class.getSimpleName();

    private FragmentNavigation fragmentNavigation;
    private static PSoCSmartChessService mPSoCSmartChessService;
    private static boolean mServiceConnected;
    private static boolean mConnectState;
    private static Handler mHandler;

    private static final int REQUEST_ENABLE_BLE = 1;
    private static final int PERMISSION_REQUEST_COARSE_LOCATION = 1;


    private final ServiceConnection mServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mPSoCSmartChessService = ((PSoCSmartChessService.LocalBinder) service).getService();
            mServiceConnected = true;
            mPSoCSmartChessService.initialize();
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mPSoCSmartChessService = null;
        }
    };

    @TargetApi(Build.VERSION_CODES.M) // This is required for Android 6.0 (Marshmallow) to work
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
        setContentView( R.layout.activity_test );
        fragmentNavigation = new FragmentNavigation(getSupportFragmentManager());
        fragmentNavigation.setFragment(new PVPFragment(), false);

        mHandler = new Handler();
        startBluetooth(findViewById(android.R.id.content));

        //This section required for Android 6.0 (Marshmallow)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Android M Permission check 
            if (this.checkSelfPermission( Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
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

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mBleUpdateReceiver);
    }

    public void startBluetooth(View view) {

        // Find BLE service and adapter
        final BluetoothManager bluetoothManager =
                (BluetoothManager) getSystemService( Context.BLUETOOTH_SERVICE);
        BluetoothAdapter mBluetoothAdapter = bluetoothManager.getAdapter();

        // Ensures Bluetooth is enabled on the device.  If Bluetooth is not currently enabled,
        // fire an intent to display a dialog asking the user to grant permission to enable it.
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BLE);
        }

        // Start the BLE Service
        Intent gattServiceIntent = new Intent(this, PSoCSmartChessService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        searchBluetooth(view);
    }

    public void searchBluetooth(final View view) {
        mHandler.postDelayed( new Runnable() {
            @Override
            public void run() {
                if(mServiceConnected) {
                    mPSoCSmartChessService.scan();
                }
                connectBluetooth(view);
            }
        }, 500 );
    }

    public void connectBluetooth(final View view) {
        mHandler.postDelayed( new Runnable() {
            @Override
            public void run() {
                if(mPSoCSmartChessService.connect()) {
                    discoverServices( view );
                }
            }
        }, 500 );

        /* After this we wait for the gatt callback to report the device is connected */
        /* That event broadcasts a message which is picked up by the mGattUpdateReceiver */
    }

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

    private final BroadcastReceiver mBleUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            switch (action) {
                case PSoCSmartChessService.ACTION_BLESCAN_CALLBACK:
                    break;

                case PSoCSmartChessService.ACTION_CONNECTED:
                    if (!mConnectState) {
                        mConnectState = true;
                        Log.d(TAG, "Connected to Device");
                    }
                    break;
                case PSoCSmartChessService.ACTION_DISCONNECTED:
                    mConnectState = false;
                    mPSoCSmartChessService.close();
                    Log.d(TAG, "Disconnected");
                    break;
                case PSoCSmartChessService.ACTION_SERVICES_DISCOVERED:
                    Log.d(TAG, "Services Discovered");
                    break;
                case PSoCSmartChessService.ACTION_DATA_RECEIVED:
                    break;
                default:
                    break;
            }
        }
    };
}
