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
import android.graphics.Color;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.support.v4.widget.SwipeRefreshLayout;

import com.cypress.smartchessapp.Fragments.CommandInputFragment;
import com.cypress.smartchessapp.Fragments.ErrorFragment;
import com.cypress.smartchessapp.Fragments.FragmentNavigation;
import com.cypress.smartchessapp.Fragments.GameSelectionFragment;
import com.cypress.smartchessapp.Fragments.PVPFragment;

import butterknife.BindView;
import butterknife.ButterKnife;

public class GameActivity extends AppCompatActivity {
    // TAG is used for informational messages
    private final static String TAG = GameActivity.class.getSimpleName();

    // Variables to access objects from the layout such as buttons, switches, values
    @BindView(R.id.player_text_view)
    protected TextView player_text_view;
    @BindView(R.id.command_status_text_view)
    protected TextView command_status_text_view;
    @BindView(R.id.fragment_container)
    protected FrameLayout user_input_layout;
    @BindView(R.id.pull_refresh)
    SwipeRefreshLayout swipeRefresh;

    // Variables to manage BLE connection
    private static boolean mConnectState;
    private static boolean mServiceConnected;
    private static PSoCSmartChessService mPSoCSmartChessService;
    private static Handler mHandler;

    // Variable to check if game type was changed
    private int gameTypeNumber = -1;

    // Variable to manage fragment navigation
    private FragmentNavigation fragmentNavigation;

    private static final int REQUEST_ENABLE_BLE = 1;

    //This is required for Android 6.0 (Marshmallow)
    private static final int PERMISSION_REQUEST_COARSE_LOCATION = 1;

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
            ((ApplicationEx) getApplication()).setPSoCSmartChessService(mPSoCSmartChessService);
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
            ((ApplicationEx) getApplication()).setPSoCSmartChessService(null);
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
        setContentView( R.layout.activity_game);

        ButterKnife.bind(this);
        fragmentNavigation = new FragmentNavigation(getSupportFragmentManager());
        fragmentNavigation.setFragment(R.id.fragment_container, new CommandInputFragment(),
                false);

        hideUI();

        // Initialize service and connection state variable
        mServiceConnected = false;
        mConnectState = false;

        mHandler = new Handler();
        startBluetooth(findViewById(android.R.id.content));

        swipeRefresh.setOnRefreshListener( new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                startBluetooth(findViewById(android.R.id.content));
                swipeRefresh.setRefreshing(false);
                swipeRefresh.setEnabled(false);
            }
        } );

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

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // User chose not to enable Bluetooth.
        if (requestCode == REQUEST_ENABLE_BLE && resultCode == Activity.RESULT_CANCELED) {
            finish();
            return;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    private void updateUI() {
        Log.e(TAG, "UI Update");
        updatePlayerTextView();
        updateCommandStatusTextView();
    }

    private void updatePlayerTextView() {
        String player = mPSoCSmartChessService.getPlayerValue();
        switch(player) {
            case "White":
                player_text_view.setBackgroundColor( Color.BLACK);
                player_text_view.setTextColor(Color.WHITE);
                break;
            case "Black":
                player_text_view.setBackgroundColor(Color.WHITE);
                player_text_view.setTextColor(Color.BLACK);
                break;
            default:
                player_text_view.setBackgroundColor(Color.BLUE);
                player_text_view.setTextColor(Color.WHITE);
                break;
        }
        player_text_view.setText(player);
    }

    private void updateCommandStatusTextView() {
        String commandStatus = mPSoCSmartChessService.getCommandStatusValue();
        command_status_text_view.setTextColor(Color.WHITE);
        switch (commandStatus) {
            case "Processing":
                command_status_text_view.setBackgroundColor(Color.BLUE);
                break;
            case "Ready for command":
                command_status_text_view.setBackgroundColor(Color.GREEN);
                break;
            default:
                command_status_text_view.setBackgroundColor(Color.RED);
                break;
        }
        command_status_text_view.setText(commandStatus);
    }

    private void setErrorFragment() {
        fragmentNavigation.setFragment(R.id.main_fragment_container, new ErrorFragment(),
                false);
        swipeRefresh.setEnabled(true);
    }

    private void setMainFragment() {
        if(Constants.GAME_TYPES[gameTypeNumber].equals("None")) {
            fragmentNavigation.setFragment(R.id.main_fragment_container, new GameSelectionFragment(),
                    false);
        } else if(Constants.GAME_TYPES[gameTypeNumber].equals("PVE")) {
            showUI();
            user_input_layout.setVisibility(View.VISIBLE);
            fragmentNavigation.setFragment(R.id.main_fragment_container, new PVPFragment(),
                    false);
        }
    }

    private void hideUI() {
        player_text_view.setVisibility(View.GONE);
        command_status_text_view.setVisibility(View.GONE);
        user_input_layout.setVisibility(View.GONE);
    }

    private void showUI() {
        command_status_text_view.setVisibility(View.VISIBLE);
        player_text_view.setVisibility(View.VISIBLE);
        user_input_layout.setVisibility(View.VISIBLE);
    }

    /**
     * This method handles the start bluetooth button
     *
     * @param view the view object
     */
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
        Log.d(TAG, "Starting BLE Service");
        Intent gattServiceIntent = new Intent(this, PSoCSmartChessService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

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
        }, 500 );


        /* After this we wait for the scan callback to detect that a device has been found */
        /* The callback broadcasts a message which is picked up by the mGattUpdateReceiver */
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
                if(mPSoCSmartChessService.connect()) {
                    discoverServices(view);
                } else {
                    setErrorFragment();
                }
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
                        //showUI();
                        mConnectState = true;
                        Log.d(TAG, "Connected to Device");
                    }
                    break;
               case PSoCSmartChessService.ACTION_DISCONNECTED:
                   hideUI();
                   mConnectState = false;
                   mPSoCSmartChessService.close();
                   Log.d(TAG, "Disconnected");
                   break;
               case PSoCSmartChessService.ACTION_SERVICES_DISCOVERED:
                   Log.d(TAG, "Services Discovered");
                   break;
               case PSoCSmartChessService.ACTION_DATA_RECEIVED:
                   updateUI();
                   int currentGameType = mPSoCSmartChessService.getGameType();
                   // Check if game type changed and is greater than zero if BLE service was recreated
                   if(gameTypeNumber != currentGameType && currentGameType >= 0) {
                       gameTypeNumber = currentGameType;
                       setMainFragment();
                   }
                   break;
                default:
                    break;
            }
        }
    };

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

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Disconnect(findViewById(android.R.id.content));
        // Close and unbind the service when the activity goes away
        mPSoCSmartChessService.close();
        unbindService(mServiceConnection);
        mPSoCSmartChessService = null;
        mServiceConnected = false;
    }
}
