package com.cypress.smartchessapp.Fragments;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import com.cypress.smartchessapp.ApplicationEx;
import com.cypress.smartchessapp.PSoCSmartChessService;
import com.cypress.smartchessapp.R;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class CommandInputFragment extends Fragment {
    // Piece choosing
    @BindView(R.id.king_button)
    protected Button king_button;
    @BindView(R.id.queen_button)
    protected Button queen_button;
    @BindView(R.id.bishop_button)
    protected Button bishop_button;
    @BindView(R.id.knight_button)
    protected Button knight_button;
    @BindView(R.id.rook_button)
    protected Button rook_button;
    @BindView(R.id.pawn_button)
    protected Button pawn_button;
    // Letter coordinates
    @BindView(R.id.button_a)
    protected Button button_a;
    @BindView(R.id.button_b)
    protected Button button_b;
    @BindView(R.id.button_c)
    protected Button button_c;
    @BindView(R.id.button_d)
    protected Button button_d;
    @BindView(R.id.button_e)
    protected Button button_e;
    @BindView(R.id.button_f)
    protected Button button_f;
    @BindView(R.id.button_g)
    protected Button button_g;
    @BindView(R.id.button_h)
    protected Button button_h;
    // Number coordinates
    @BindView(R.id.button_1)
    protected Button button_1;
    @BindView(R.id.button_2)
    protected Button button_2;
    @BindView(R.id.button_3)
    protected Button button_3;
    @BindView(R.id.button_4)
    protected Button button_4;
    @BindView(R.id.button_5)
    protected Button button_5;
    @BindView(R.id.button_6)
    protected Button button_6;
    @BindView(R.id.button_7)
    protected Button button_7;
    @BindView(R.id.button_8)
    protected Button button_8;
    // Text view to display command
    @BindView(R.id.command_text_view)
    protected TextView command_text_view;
    // Speech button
    @BindView(R.id.speech_button)
    protected ImageButton speech_button;

    // Array for keeping command value
    byte[] byteValue = new byte[3];
    // BLE Service
    PSoCSmartChessService mPSoCSmartChessService;

    public CommandInputFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_command_input, container, false);
        ButterKnife.bind(this, view);
        speech_button.setImageResource(R.drawable.ic_mic_black_24dp);

        mPSoCSmartChessService = ((ApplicationEx) getActivity().getApplication())
                .getPSoCSmartChessService();

        return view;
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case 10:
                if (resultCode == Activity.RESULT_OK && data != null) {
                    // Getting result from speech
                    ArrayList<String> result =
                            data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    String string = result.get(0);
                    List<String> items = Arrays.asList(string.split("\\s* \\s*"));
                    try {
                        byte[] bytes = {(byte) items.get(0).toLowerCase().charAt(0),
                                (byte) items.get( 1 ).toLowerCase().charAt(0)};
                    } catch (Exception exception) {
                        Toast.makeText(getContext(), "Exception", Toast.LENGTH_SHORT).show();
                    }

                    // Hardcoded value, will be changed later
                    byteValue[0] = 'N';
                    byteValue[1] = 'a';
                    byteValue[2] = '4';
                    updateCommandTextView();
                }
                break;
            default:
                break;
        }
    }

    @OnClick(R.id.speech_button)
    public void getSpeechInput() {

        Intent intent = new Intent( RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());

        if (intent.resolveActivity(getContext().getPackageManager()) != null) {
            startActivityForResult(intent, 10);
        } else {
            Toast.makeText(getContext(), "Your Device Don't Support Speech Input",
                    Toast.LENGTH_SHORT).show();
        }
    }

    private void updateCommandTextView() {
        command_text_view.setText(String.format("Command is: %c%c%c",
                byteValue[0], byteValue[1], byteValue[2]));
    }

    private void assignButtonValue(Button btn, int btn_row) {
        setDefaultBackground(btn_row);
        byteValue[btn_row-1] = (byte) btn.getText().charAt(0);
        btn.getBackground().setColorFilter(Color.CYAN, PorterDuff.Mode.MULTIPLY);
        updateCommandTextView();
    }

    private void setDefaultBackground(int btn_row) {
        switch (btn_row) {
            case 1:
                king_button.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                queen_button.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                bishop_button.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                knight_button.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                rook_button.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                pawn_button.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                break;
            case 2:
                button_a.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_b.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_c.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_d.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_e.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_f.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_g.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_h.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                break;
            case 3:
                button_1.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_2.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_3.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_4.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_5.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_6.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_7.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                button_8.getBackground().setColorFilter(Color.LTGRAY, PorterDuff.Mode.MULTIPLY);
                break;
            default:
                break;
        }
    }

    private void resetData() {
        // Reset command data
        byteValue = new byte[3];
        // Reset highlighted buttons
        setDefaultBackground(1);
        setDefaultBackground(2);
        setDefaultBackground(3);
        // Update command string
        updateCommandTextView();
    }

    @OnClick(R.id.send_command)
    protected void sendCommand() {
        if(mPSoCSmartChessService == null) {
            mPSoCSmartChessService = ((ApplicationEx) getActivity().getApplication())
                    .getPSoCSmartChessService();
        }
        mPSoCSmartChessService.writeCommandCharacteristic(byteValue);
        resetData();
    }

    @OnClick(R.id.king_button)
    protected void kingPiece() { assignButtonValue(king_button, 1); }

    @OnClick(R.id.queen_button)
    protected void queenPiece() { assignButtonValue(queen_button, 1); }

    @OnClick(R.id.bishop_button)
    protected void bishopPiece() { assignButtonValue(bishop_button, 1); }

    @OnClick(R.id.knight_button)
    protected void knightPiece() { assignButtonValue(knight_button, 1); }

    @OnClick(R.id.rook_button)
    protected void rookPiece() { assignButtonValue(rook_button, 1); }

    @OnClick(R.id.pawn_button)
    protected void pawnPiece() { assignButtonValue(pawn_button, 1); }

    @OnClick(R.id.button_a)
    protected void coordinateA() { assignButtonValue(button_a, 2); }

    @OnClick(R.id.button_b)
    protected void coordinateB() { assignButtonValue(button_b, 2); }

    @OnClick(R.id.button_c)
    protected void coordinateC() { assignButtonValue(button_c, 2); }

    @OnClick(R.id.button_d)
    protected void coordinateD() { assignButtonValue(button_d, 2); }

    @OnClick(R.id.button_e)
    protected void coordinateE() { assignButtonValue(button_e, 2); }

    @OnClick(R.id.button_f)
    protected void coordinateF() { assignButtonValue(button_f, 2); }

    @OnClick(R.id.button_g)
    protected void coordinateG() { assignButtonValue(button_g, 2); }

    @OnClick(R.id.button_h)
    protected void coordinateH() { assignButtonValue(button_h, 2); }

    @OnClick(R.id.button_1)
    protected void coordinate1() { assignButtonValue(button_1, 3); }

    @OnClick(R.id.button_2)
    protected void coordinate2() { assignButtonValue(button_2, 3); }

    @OnClick(R.id.button_3)
    protected void coordinate3() { assignButtonValue(button_3, 3); }

    @OnClick(R.id.button_4)
    protected void coordinate4() { assignButtonValue(button_4, 3); }

    @OnClick(R.id.button_5)
    protected void coordinate5() { assignButtonValue(button_5, 3); }

    @OnClick(R.id.button_6)
    protected void coordinate6() { assignButtonValue(button_6, 3); }

    @OnClick(R.id.button_7)
    protected void coordinate7() { assignButtonValue(button_7, 3); }

    @OnClick(R.id.button_8)
    protected void coordinate8() { assignButtonValue(button_8, 3); }
}
