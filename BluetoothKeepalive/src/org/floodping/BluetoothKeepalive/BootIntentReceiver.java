package org.floodping.BluetoothKeepalive;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class BootIntentReceiver extends BroadcastReceiver{

	@Override
	public void onReceive(Context context, Intent intent) {
		Intent serviceIntent = new Intent();
		serviceIntent.setAction("org.floodping.BluetoothKeepalive.BluetoothKeepaliveService");
		context.startService(serviceIntent);
	}
}
