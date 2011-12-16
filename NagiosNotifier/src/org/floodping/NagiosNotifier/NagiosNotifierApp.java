package org.floodping.NagiosNotifier;

import android.app.Application;
import android.app.PendingIntent;
import android.content.Intent;

public class NagiosNotifierApp extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		
		Intent registrationIntent = new Intent("com.google.android.c2dm.intent.REGISTER");
		registrationIntent.putExtra("app", PendingIntent.getBroadcast(this, 0, new Intent(), 0));
		registrationIntent.putExtra("sender", "alex@nfsroot.de");
		startService(registrationIntent);
	}

	@Override
	public void onTerminate() {
		
		Intent unregIntent = new Intent("com.google.android.c2dm.intent.UNREGISTER");
		unregIntent.putExtra("app", PendingIntent.getBroadcast(this, 0, new Intent(), 0));
		startService(unregIntent);
		
		super.onTerminate();
	}

}
