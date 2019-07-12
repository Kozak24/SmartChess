package com.cypress.smartchessapp.Fragments;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.cypress.smartchessapp.Constants;
import com.cypress.smartchessapp.R;

import butterknife.BindView;
import butterknife.ButterKnife;

public class StatusFragment extends Fragment {
    @BindView(R.id.status_text_view)
    protected TextView status_text_view;

    public StatusFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_status, container, false);
        ButterKnife.bind(this, view);

        int statusCode = getBundleArg();
        setStatusText(statusCode);

        return view;
    }

    private int getBundleArg() {
        Bundle bundle = this.getArguments();
        if(bundle != null) {
            return bundle.getInt(Constants.KEY);
        }

        return 0;
    }

    private void setStatusText(int statusCode) {
        switch(statusCode) {
            case Constants.STATUS_CONNECTING:
                status_text_view.setText(getString(R.string.connecting));
                break;
            case Constants.STATUS_ERROR:
                status_text_view.setText(getString(R.string.went_wrong));
                break;
            default:
                break;
        }
    }
}
