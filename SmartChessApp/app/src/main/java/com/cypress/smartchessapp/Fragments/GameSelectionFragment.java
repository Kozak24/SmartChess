package com.cypress.smartchessapp.Fragments;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.cypress.smartchessapp.ApplicationEx;
import com.cypress.smartchessapp.Constants;
import com.cypress.smartchessapp.GameActivity;
import com.cypress.smartchessapp.PSoCSmartChessService;
import com.cypress.smartchessapp.R;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class GameSelectionFragment extends Fragment {

    @BindView(R.id.pve_button)
    protected Button pve_button;
    @BindView(R.id.pvp_button)
    protected Button pvp_button;
    @BindView(R.id.eve_button)
    protected Button eve_button;
    @BindView(R.id.demo_button)
    protected Button demo_button;

    public GameSelectionFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_game_selection, container, false);
        ButterKnife.bind(this, view);
        return view;
    }

    private void startGame(int gameTypeNumber) {
        PSoCSmartChessService psocSmartChessService = ((ApplicationEx) getActivity().
                getApplication()).getPSoCSmartChessService();

        // Write game type into Gatt DB
        psocSmartChessService.writeStartGameCharacteristic(gameTypeNumber);
        // Restart activity
        getActivity().recreate();
    }

    @OnClick(R.id.pve_button)
    protected void pveGame() {
        startGame(Constants.PVE_GAME);
    }

    @OnClick(R.id.pvp_button)
    protected void pvpGame() {

    }

    @OnClick(R.id.eve_button)
    protected void eveGme() {

    }

    @OnClick(R.id.demo_button)
    protected void demoGame() {

    }
}
