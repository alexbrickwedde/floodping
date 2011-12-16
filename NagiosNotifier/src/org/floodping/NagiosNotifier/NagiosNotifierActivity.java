package org.floodping.NagiosNotifier;

import android.app.Activity;
import android.os.Bundle;

public class NagiosNotifierActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
		Helper.Register(this);
		this.finish();
    }
}