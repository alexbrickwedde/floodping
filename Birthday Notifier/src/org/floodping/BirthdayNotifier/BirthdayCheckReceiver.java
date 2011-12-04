package org.floodping.BirthdayNotifier;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class BirthdayCheckReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		Helper.test(context);
	}

}
