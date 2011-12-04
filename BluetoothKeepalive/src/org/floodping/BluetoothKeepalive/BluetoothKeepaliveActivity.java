package org.floodping.BluetoothKeepalive;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class BluetoothKeepaliveActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Intent serviceIntent = new Intent();
		serviceIntent.setAction("org.floodping.BluetoothKeepalive.BluetoothKeepaliveService");
		this.startService(serviceIntent);

		Toast.makeText(this, "BluetoothKeepalive service is being started", Toast.LENGTH_SHORT).show();

		this.finish();

	}
}