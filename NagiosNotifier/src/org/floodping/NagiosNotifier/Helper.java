package org.floodping.NagiosNotifier;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;

public class Helper {

	public static void Register(Context context) {
		Intent registrationIntent = new Intent("com.google.android.c2dm.intent.REGISTER");
		registrationIntent.putExtra("app", PendingIntent.getBroadcast(context, 0, new Intent(), 0));
		registrationIntent.putExtra("sender", "alex@nfsroot.de");
		context.startService(registrationIntent);
	}
	
	public static void UnRegister(Context context)
	{
		Intent unregIntent = new Intent("com.google.android.c2dm.intent.UNREGISTER");
		unregIntent.putExtra("app", PendingIntent.getBroadcast(context, 0, new Intent(), 0));
		context.startService(unregIntent);
	}
}
