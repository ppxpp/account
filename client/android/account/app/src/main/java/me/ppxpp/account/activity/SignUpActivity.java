package me.ppxpp.account.activity;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import io.grpc.helloworldexample.cpp.R;
import me.ppxpp.account.app.BaseActivity;
import me.ppxpp.account.model.Account;

public class SignUpActivity extends BaseActivity implements Account.OfflineCallback {

    private TextView mTvInfo;
    private EditText mEtUserName;
    private EditText mEtPassword;
    private Button mBtnSignUp;
    private Button mBtnSignIn;
    private Button mBtnSignOut;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_up);
        mTvInfo = findViewById(R.id.account_info);
        mEtUserName = findViewById(R.id.user_name);
        mEtUserName.setText("Alice");
        mEtPassword = findViewById(R.id.password);
        mEtPassword.setText("123456");
        mBtnSignUp = findViewById(R.id.btn_sign_up);
        mBtnSignUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                signUp();
            }
        });
        mBtnSignIn = findViewById(R.id.btn_sign_in);
        mBtnSignIn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                signIn();
            }
        });
        mBtnSignOut = findViewById(R.id.btn_sign_out);
        mBtnSignOut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                signOut();
            }
        });
        Account.setOffLineCallback(this);
        refreshAccountInfo();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Account.setOffLineCallback(null);
    }

    private void signUp() {
        String userName = mEtUserName.getText().toString();
        String password =mEtPassword.getText().toString();
        if (TextUtils.isEmpty(userName) || TextUtils.isEmpty(password)) {
            Toast.makeText(this, "请输入用户名密码", Toast.LENGTH_SHORT).show();
            return;
        }
        showLoading();
        Account.signUp(userName, password, new Account.Callback() {
            @Override
            public void onDone(boolean success, String msg) {
                if (success) {
                    Account account = Account.getCurrentAccount();
                    if (account != null) {
                        Toast.makeText(SignUpActivity.this, "注册成功", Toast.LENGTH_SHORT).show();
                    }
                } else {
                    Toast.makeText(SignUpActivity.this, "注册失败: " + msg, Toast.LENGTH_SHORT).show();
                }
                refreshAccountInfo();
                dismissLoading();
            }
        });
    }

    private void signIn() {
        String userName = mEtUserName.getText().toString();
        String password =mEtPassword.getText().toString();
        if (TextUtils.isEmpty(userName) || TextUtils.isEmpty(password)) {
            Toast.makeText(this, "请输入用户名密码", Toast.LENGTH_SHORT).show();
            return;
        }
        showLoading();
        Account.signIn(userName, password, new Account.Callback() {
            @Override
            public void onDone(boolean success, String msg) {
                if (success) {
                    Account account = Account.getCurrentAccount();
                    if (account != null) {
                        Toast.makeText(SignUpActivity.this, "登录成功", Toast.LENGTH_SHORT).show();
                    }
                } else {
                    Toast.makeText(SignUpActivity.this, "登录失败: " + msg, Toast.LENGTH_SHORT).show();
                }
                refreshAccountInfo();
                dismissLoading();
            }
        });
    }

    private void signOut() {
        Account account = Account.getCurrentAccount();
        if (account == null) {
            Toast.makeText(this, "你还没有登录", Toast.LENGTH_SHORT).show();
            return;
        }
        showLoading();
        account.signOut(new Account.Callback() {
            @Override
            public void onDone(boolean success, String msg) {
                if (success) {
                    Toast.makeText(SignUpActivity.this, "退出成功", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(SignUpActivity.this, "退出失败: " + msg, Toast.LENGTH_SHORT).show();
                }
                refreshAccountInfo();
                dismissLoading();
            }
        });
    }

    @Override
    public void onAccountOffline() {
        refreshAccountInfo();
        showMessage("你的账号已在其他舍设备登录!");
    }

    public void refreshAccountInfo() {
        Account account = Account.getCurrentAccount();
        if (account != null) {
            mTvInfo.setText("当前登录账号:\n" + account.toString());
        } else {
            mTvInfo.setText("当前未登录");
        }
        mBtnSignIn.setEnabled(account == null);
        mBtnSignUp.setEnabled(account == null);
        mBtnSignOut.setEnabled(account != null);
    }
}
