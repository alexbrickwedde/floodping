package org.floodping.BluetoothKeepalive;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Toast;

public class BluetoothKeepaliveActivity extends Activity {
	
	private Handler mHandler = new Handler();
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mHandler.postDelayed(new Runnable() {
			@Override
			public void run() {
				BluetoothKeepaliveActivity.this.finish();
			}
		},20000);
		
		Intent serviceIntent = new Intent();
		serviceIntent.setAction("org.floodping.BluetoothKeepalive.BluetoothKeepaliveService");
		this.startService(serviceIntent);

		setContentView(R.layout.splashscreen);
		
		Toast.makeText(this, R.string.StartingService, Toast.LENGTH_SHORT).show();
	}
}