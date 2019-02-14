package me.ppxpp.account.model;

import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;

import me.ppxpp.account.auth.Auth;
import me.ppxpp.account.auth.AuthInfo;
import me.ppxpp.account.auth.AuthReply;
import me.ppxpp.account.auth.UserInfo;
import me.ppxpp.account.push.PushManager;

public class Account {

    private static volatile Auth sAuthImpl;
    private static Account sCurtAct;

    private static Handler sUIHandler = new Handler(Looper.getMainLooper());
    private String mUserName;
    private String mToken;
    private static OfflineCallback sOfflineCallback;
    private static PushManager.PushMessageListener sListener = new PushManager.PushMessageListener() {
        @Override
        public void onAccountCanceled(String userName) {
            OfflineCallback callback = null;
            synchronized (Account.class) {
                Account account = getCurrentAccount();
                if (account != null && TextUtils.equals(userName, account.mUserName)) {
                    sCurtAct = null;
                    callback = sOfflineCallback;
                }
            }
            if (callback != null) {
                callback.onAccountOffline();
            }
        }
    };

    public static void init() {
        PushManager.getInstance().addPushMessageListener(sListener);
    }

    public static Account getCurrentAccount() {
        return sCurtAct;
    }

    public static void setOffLineCallback(OfflineCallback callback) {
        sOfflineCallback = callback;
    }

    public static void signIn(final String userName, final String password, final Callback callback) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                String token = PushManager.getInstance().getDeviceToken();
                if (TextUtils.isEmpty(token)) {
                    if (callback != null) {
                        sUIHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                callback.onDone(false, "请稍候重试");
                            }
                        });
                    }
                    return;
                }
                UserInfo userInfo = new UserInfo(userName, password, token);
                AuthReply reply =getAuthImpl().signIn(userInfo);
                if (reply != null) {
                    final int err = reply.getErr();
                    final String msg = parseErr(err, reply.getMsg());
                    if (err == 0) {
                        Account account = new Account();
                        account.mToken = reply.getData().getToken();
                        account.mUserName = userName;
                        synchronized (Account.class) {
                            sCurtAct = account;
                        }
                    }
                    if (callback != null) {
                        sUIHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                callback.onDone(err == 0, msg);
                            }
                        });
                    }
                }
            }
        }).start();
    }

    public static void signUp(final String userName, final String password, final Callback callback) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                String token = PushManager.getInstance().getDeviceToken();
                if (TextUtils.isEmpty(token)) {
                    if (callback != null) {
                        sUIHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                callback.onDone(false, "请稍候重试");
                            }
                        });
                    }
                    return;
                }
                UserInfo userInfo = new UserInfo(userName, password, token);
                AuthReply reply =getAuthImpl().signUp(userInfo);
                if (reply != null) {
                    final int err = reply.getErr();
                    final String msg = parseErr(err, reply.getMsg());
                    if (err == 0) {
                        Account account = new Account();
                        account.mToken = reply.getData().getToken();
                        account.mUserName = userName;
                        synchronized (Account.class) {
                            sCurtAct = account;
                        }
                    }
                    if (callback != null) {
                        sUIHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                callback.onDone(err == 0, msg);
                            }
                        });
                    }
                }
            }
        }).start();
    }

    public void signOut(final Callback callback) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                AuthInfo info = new AuthInfo(mToken);
                AuthReply reply = getAuthImpl().signOut(info);
                final int err = reply.getErr();
                final String msg = parseErr(err, reply.getMsg());
                if (err == 0) {
                    synchronized (Account.class) {
                        sCurtAct = null;
                    }
                }
                if (callback != null) {
                    sUIHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            callback.onDone(err == 0, msg);
                        }
                    });
                }
            }
        }).start();
    }

    @Override
    public String toString() {
        return mUserName + ", " + mToken;
    }

    public interface Callback {
        void onDone(boolean success, String msg);
    }

    public interface OfflineCallback {
        void onAccountOffline();
    }

    private static final int ERROR = -1;
    private static final int OK = 0;
    private static final int USER_EXIT = 1;
    private static final int USER_NOT_FOUND = 3;
    private static final int SIGN_IN_ERROR = 4;
    private static final int SIGN_UP_ERROR = 5;
    private static final int OTHER = 20;

    private static String parseErr(int err, String msg) {
        switch (err) {
            case USER_EXIT:
                msg = "用户已存在";
                break;
            case USER_NOT_FOUND:
                msg = "用户名或密码错误";
                break;
            case SIGN_IN_ERROR:
                break;
            case SIGN_UP_ERROR:
                break;
            case OTHER:
                break;
        }
        return msg;
    }

    private static Auth getAuthImpl() {
        if (sAuthImpl == null) {
            synchronized (Account.class) {
                if (sAuthImpl == null) {
                    sAuthImpl = Auth.create("192.168.56.101:50051");
                }
            }
        }
        return sAuthImpl;
    }
}
