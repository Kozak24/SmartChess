package com.cypress.smartchessapp.Fragments;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.cypress.smartchessapp.ApplicationEx;
import com.cypress.smartchessapp.PSoCSmartChessService;
import com.cypress.smartchessapp.R;

public class PVPFragment extends Fragment {
    private boolean mConnectState = false;
    private TextView textView;

    private PSoCSmartChessService mPSoCSmartChessService;

    public PVPFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate( savedInstanceState );
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate( R.layout.fragment_pvp, container, false);

        textView = view.findViewById(R.id.text_view);

        setPSoCSmartChessService();
        if(mPSoCSmartChessService != null) {
            // Update UI
        }

        return view;
    }

    private void setPSoCSmartChessService() {
        mPSoCSmartChessService = ((ApplicationEx) getActivity().getApplication())
                .getPSoCSmartChessService();
    }

    @Override
    public void onResume() {
        super.onResume();
        IntentFilter filter = new IntentFilter();
        filter.addAction(PSoCSmartChessService.ACTION_DATA_RECEIVED);
        filter.addAction(PSoCSmartChessService.ACTION_DISCONNECTED);
        filter.addAction(PSoCSmartChessService.ACTION_CONNECTED);

        getActivity().registerReceiver(mBleUpdateReceiver, filter);
    }

    @Override
    public void onPause() {
        super.onPause();
        getActivity().unregisterReceiver(mBleUpdateReceiver);

    }

    private final BroadcastReceiver mBleUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(mPSoCSmartChessService == null) {
               setPSoCSmartChessService();
            }

            final String action = intent.getAction();
            switch (action) {

                case PSoCSmartChessService.ACTION_CONNECTED:
                    if (!mConnectState) {
                        mConnectState = true;
                    }
                    textView.setText("Connected");
                    break;
                case PSoCSmartChessService.ACTION_DISCONNECTED:
                    // Disable the disconnect, discover svc, discover char button, and enable the search button
                    mConnectState = false;
                    break;
                case PSoCSmartChessService.ACTION_DATA_RECEIVED:
                    //updateUI();
                    textView.setText(mPSoCSmartChessService.getPlayerValue());
                    break;
                default:
                    break;
            }
        }
    };
}
