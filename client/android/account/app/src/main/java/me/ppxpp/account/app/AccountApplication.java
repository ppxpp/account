package me.ppxpp.account.app;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;

import me.ppxpp.account.model.Account;
import me.ppxpp.account.push.PushManager;

public class AccountApplication extends Application {

    static {
        System.loadLibrary("grpc-helloworld");
    }

    @Override
    public void onCreate() {
        super.onCreate();
        boolean isMainProcess = getApplicationContext().getPackageName().equals
                (getCurrentProcessName());
        PushManager.getInstance().init(this, isMainProcess);
        if (isMainProcess) {
            Account.init();
        }
    }

    private String getCurrentProcessName() {
        int pid = android.os.Process.myPid();
        String processName = "";
        ActivityManager manager = (ActivityManager) getApplicationContext().getSystemService
                (Context.ACTIVITY_SERVICE);
        for (ActivityManager.RunningAppProcessInfo process : manager.getRunningAppProcesses()) {
            if (process.pid == pid) {
                processName = process.processName;
            }
        }
        return processName;
    }
}
