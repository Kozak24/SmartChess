package com.cypress.smartchessapp.Fragments;

import android.graphics.Color;
import android.graphics.PorterDuff;
import android.media.Image;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

import com.cypress.smartchessapp.R;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class CommandInputFragment extends Fragment {
    @BindView(R.id.input_buttons)
    protected Button input_buttons;
    @BindView(R.id.input_speech)
    protected Button input_speech;
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

    public CommandInputFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_command_input, container, false);
        ButterKnife.bind(this, view);
        speech_button.setImageResource(R.drawable.ic_mic_black_24dp);
        return view;
    }

    @OnClick(R.id.input_buttons)
    protected void showInputButtonsUI() {
        resetData();
        hideSpeechUI();
        // Show pieces buttons
        king_button.setVisibility(View.VISIBLE);
        queen_button.setVisibility(View.VISIBLE);
        bishop_button.setVisibility(View.VISIBLE);
        knight_button.setVisibility(View.VISIBLE);
        rook_button.setVisibility(View.VISIBLE);
        pawn_button.setVisibility(View.VISIBLE);
        // Show coordinates letters
        button_a.setVisibility(View.VISIBLE);
        button_b.setVisibility(View.VISIBLE);
        button_c.setVisibility(View.VISIBLE);
        button_d.setVisibility(View.VISIBLE);
        button_e.setVisibility(View.VISIBLE);
        button_f.setVisibility(View.VISIBLE);
        button_g.setVisibility(View.VISIBLE);
        button_h.setVisibility(View.VISIBLE);
        // Show coordinates numbers
        button_1.setVisibility(View.VISIBLE);
        button_2.setVisibility(View.VISIBLE);
        button_3.setVisibility(View.VISIBLE);
        button_4.setVisibility(View.VISIBLE);
        button_5.setVisibility(View.VISIBLE);
        button_6.setVisibility(View.VISIBLE);
        button_7.setVisibility(View.VISIBLE);
        button_8.setVisibility(View.VISIBLE);
    }

    @OnClick(R.id.input_speech)
    protected void showSpeechUI() {
        resetData();
        hideInputButtonsUI();
    }

    private void hideInputButtonsUI() {
        // Hide pieces buttons
        king_button.setVisibility(View.GONE);
        queen_button.setVisibility(View.GONE);
        bishop_button.setVisibility(View.GONE);
        knight_button.setVisibility(View.GONE);
        rook_button.setVisibility(View.GONE);
        pawn_button.setVisibility(View.GONE);
        // Hide coordinates letters
        button_a.setVisibility(View.GONE);
        button_b.setVisibility(View.GONE);
        button_c.setVisibility(View.GONE);
        button_d.setVisibility(View.GONE);
        button_e.setVisibility(View.GONE);
        button_f.setVisibility(View.GONE);
        button_g.setVisibility(View.GONE);
        button_h.setVisibility(View.GONE);
        // Hide coordinates numbers
        button_1.setVisibility(View.GONE);
        button_2.setVisibility(View.GONE);
        button_3.setVisibility(View.GONE);
        button_4.setVisibility(View.GONE);
        button_5.setVisibility(View.GONE);
        button_6.setVisibility(View.GONE);
        button_7.setVisibility(View.GONE);
        button_8.setVisibility(View.GONE);

    }

    private void hideSpeechUI() {

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
    protected void sendCommand() { /*mPSoCSmartChessService.writeCommandCharacteristic(byteValues);*/ }

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
