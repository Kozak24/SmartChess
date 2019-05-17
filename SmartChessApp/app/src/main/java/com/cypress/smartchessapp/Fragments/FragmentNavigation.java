package com.cypress.smartchessapp.Fragments;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;

import com.cypress.smartchessapp.R;

public class FragmentNavigation {
    private FragmentManager fragmentManager;

    public FragmentNavigation(FragmentManager fragmentManager) {
        this.fragmentManager = fragmentManager;
    }

    public void setFragment(final Fragment fragment, final boolean addToBackStack) {
        final FragmentTransaction transaction = fragmentManager.beginTransaction()
                .replace( R.id.fragment_container, fragment);

        if (addToBackStack) {
            transaction.addToBackStack( null );
        }
        transaction.commit();
    }
}
