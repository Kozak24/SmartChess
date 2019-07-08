package com.cypress.smartchessapp.Fragments;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.cypress.smartchessapp.R;

import butterknife.BindView;
import butterknife.ButterKnife;

public class ErrorFragment extends Fragment {
    @BindView(R.id.error_text_view)
    protected TextView error_text_view;

    public ErrorFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_error, container, false);
        ButterKnife.bind(this, view);
        return view;
    }
}
