package org.floodping.BirthdayNotifier;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class BootIntentReceiver extends BroadcastReceiver{

	@Override
	public void onReceive(Context context, Intent intent) {
		Intent serviceIntent = new Intent();
		serviceIntent.setAction("org.floodping.BirthdayNotifier.BirthdayNotifierService");
		context.startService(serviceIntent);
	}
}
