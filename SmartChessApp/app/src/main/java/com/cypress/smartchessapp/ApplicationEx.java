package com.cypress.smartchessapp;

import android.app.Application;

public class ApplicationEx extends Application {
    private PSoCSmartChessService mPSoCSmartChessService;

    public PSoCSmartChessService getPSoCSmartChessService() {
        return mPSoCSmartChessService;
    }

    public void setPSoCSmartChessService(PSoCSmartChessService psocSmartChessService) {
        mPSoCSmartChessService = psocSmartChessService;
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }
}
