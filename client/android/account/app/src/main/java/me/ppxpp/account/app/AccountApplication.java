package me.ppxpp.account.app;

import android.app.Application;

import me.ppxpp.account.model.Account;
import me.ppxpp.account.push.PushManager;

public class AccountApplication extends Application {

    static {
        System.loadLibrary("grpc-helloworld");
    }

    @Override
    public void onCreate() {
        super.onCreate();
        PushManager.getInstance().init(this);
        Account.init();
    }
}
