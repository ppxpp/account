package me.ppxpp.account.app;

import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;

import com.kaopiz.kprogresshud.KProgressHUD;



public abstract class BaseActivity extends AppCompatActivity {

    private KProgressHUD mLoadingDialog;
    private AlertDialog mMsgDialog;

    protected void showMessage(String msg) {
        mMsgDialog = new AlertDialog.Builder(this)
                .setMessage(msg)
                .setCancelable(true)
                .create();
        mMsgDialog.show();
    }

    private void dismissMessageDialog() {
        if (mMsgDialog != null) {
            if (mMsgDialog.isShowing()) {
                mMsgDialog.dismiss();
            }
            mMsgDialog = null;
        }
    }

    protected void showLoading() {
        dismissLoading();
        mLoadingDialog = KProgressHUD.create(this)
                .setStyle(KProgressHUD.Style.SPIN_INDETERMINATE)
                .setLabel("加载中...")
	            .setCancellable(true)
                .setAnimationSpeed(2)
                .setDimAmount(0.5f)
                .show();
    }

    @Override
    protected void onPause() {
        super.onPause();
        dismissMessageDialog();
        dismissLoading();
    }

    protected void dismissLoading() {
        if (mLoadingDialog != null) {
            mLoadingDialog.dismiss();
            mLoadingDialog = null;
        }
    }

}
