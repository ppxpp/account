package me.ppxpp.account.push;

import android.content.Context;
import android.preference.PreferenceManager;
import android.text.TextUtils;
import android.util.Log;

import com.tencent.android.tpush.XGIOperateCallback;
import com.tencent.android.tpush.XGPushConfig;
import com.tencent.android.tpush.XGPushManager;
import com.tencent.android.tpush.common.Constants;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import io.grpc.helloworldexample.cpp.BuildConfig;

public class PushManager {

    private static PushManager sInstance = new PushManager();

    public static PushManager getInstance() {
        return sInstance;
    }

    private static final String KEY_DEVICE_TOKEN = "sp_key_device_token";

    private Context mContext;
    private String mToken;
    private List<PushMessageListener> mLiseners;

    public void init(Context context) {
        if (context == null || mContext != null) {
            return;
        }
        mLiseners = new CopyOnWriteArrayList<>();
        mContext = context.getApplicationContext();
        mToken = PreferenceManager.getDefaultSharedPreferences(context)
                .getString(KEY_DEVICE_TOKEN, null);
        //开启信鸽的日志输出，线上版本不建议调用
        XGPushConfig.enableDebug(context, BuildConfig.DEBUG);
        XGPushConfig.getToken(context);
        /*
        注册信鸽服务的接口
        如果仅仅需要发推送消息调用这段代码即可
        */
        XGPushManager.registerPush(context,
                new XGIOperateCallback() {
                    @Override
                    public void onSuccess(Object data, int flag) {
                        Log.w(Constants.LogTag, "+++ register push sucess. token:" + data + "flag" + flag);
                        String newToken = (String) data;
                        if (!TextUtils.isEmpty(newToken) && !TextUtils.equals(newToken, mToken)) {
                            handleTokenChanged(newToken);
                        }
                    }

                    @Override
                    public void onFail(Object data, int errCode, String msg) {
                        Log.w(Constants.LogTag,
                                "+++ register push fail. token:" + data
                                        + ", errCode:" + errCode + ",msg:"
                                        + msg);
                    }
                });

        // 获取token
        XGPushConfig.getToken(context);
    }

    private void handleTokenChanged(String newToken) {
        mToken = newToken;
        PreferenceManager.getDefaultSharedPreferences(mContext)
                .edit()
                .putString(KEY_DEVICE_TOKEN, mToken)
                .apply();
    }

    public String getDeviceToken() {
        Log.i("Constants.LogTag", "getDeviceToken, token = " + mToken);
        return mToken;
    }

    public void addPushMessageListener(PushMessageListener listener) {
        if (listener != null && !mLiseners.contains(listener)) {
            mLiseners.add(listener);
        }
    }

    public void removePushMessageListener(PushMessageListener listener) {
        if (listener != null) {
            mLiseners.remove(listener);
        }
    }

    public void notifyAccountCanceled(String userName) {
        for (PushMessageListener listener : mLiseners) {
            listener.onAccountCanceled(userName);
        }
    }

    public interface PushMessageListener {
        void onAccountCanceled(String userName);
    }
}
