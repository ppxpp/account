package me.ppxpp.account.push;

import android.os.Handler;
import android.os.Looper;

import me.ppxpp.account.auth.Push;

public class RpcPush {

    private static RpcPush sInstance;
    private Push pushImpl;
    private me.ppxpp.account.auth.PushListener listener;

    private RpcPush(String host, String deviceToken, me.ppxpp.account.auth.PushListener listener) {
        this.listener = listener;
        pushImpl = Push.create(host, deviceToken, listener);
        new Thread(new Runnable() {
            @Override
            public void run() {
                pushImpl.connect();
            }
        }).start();
    }

    public static void connect(String host, String deviceToken, PushListener pushListener) {
        if (sInstance == null) {
            synchronized (RpcPush.class) {
                if (sInstance == null) {
                    sInstance = new RpcPush(host, deviceToken, new Listener(pushListener));
                }
            }
        }
    }

    private static class Listener extends me.ppxpp.account.auth.PushListener {

        private PushListener listener;

        private Listener(PushListener listener) {
            this.listener = listener;
        }

        @Override
        public void onNotify(final String pushMsg) {
            new Handler(Looper.getMainLooper()).post(new Runnable() {
                @Override
                public void run() {
                    if (listener != null) {
                        listener.onPushMessage(pushMsg);
                    }
                }
            });
        }
    }

    public interface PushListener {
        void onPushMessage(String pushMsg);
    }
}
