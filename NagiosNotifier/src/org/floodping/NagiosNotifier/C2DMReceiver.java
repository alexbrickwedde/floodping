package org.floodping.NagiosNotifier;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class C2DMReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		if (intent.getAction().equals("com.google.android.c2dm.intent.REGISTRATION")) {
			handleRegistration(context, intent);
		} else if (intent.getAction().equals("com.google.android.c2dm.intent.RECEIVE")) {
			handleMessage(context, intent);
		}
	}

	private void handleRegistration(Context context, Intent intent) {
		String registration = intent.getStringExtra("registration_id");
		if (intent.getStringExtra("error") != null) {
			// Registration failed, should try again later.
			Log.d("c2dm", "registration failed");
			String error = intent.getStringExtra("error");
			if (error == "SERVICE_NOT_AVAILABLE") {
				Log.d("c2dm", "SERVICE_NOT_AVAILABLE");
				Helper.Register(context);
			} else if (error == "ACCOUNT_MISSING") {
				Log.d("c2dm", "ACCOUNT_MISSING");
			} else if (error == "AUTHENTICATION_FAILED") {
				Log.d("c2dm", "AUTHENTICATION_FAILED");
			} else if (error == "TOO_MANY_REGISTRATIONS") {
				Log.d("c2dm", "TOO_MANY_REGISTRATIONS");
			} else if (error == "INVALID_SENDER") {
				Log.d("c2dm", "INVALID_SENDER");
			} else if (error == "PHONE_REGISTRATION_ERROR") {
				Log.d("c2dm", "PHONE_REGISTRATION_ERROR");
			}
		} else if (intent.getStringExtra("unregistered") != null) {
			// unregistration done, new messages from the authorized sender will
			// be rejected
			Log.d("c2dm", "unregistered");

		} else if (registration != null) {
			Log.d("c2dm", registration);
//			Editor editor = context.getSharedPreferences(KEY, Context.MODE_PRIVATE).edit();
//			editor.putString(REGISTRATION_KEY, registration);
//			editor.commit();
			// Send the registration ID to the 3rd party site that is sending
			// the messages.
			// This should be done in a separate thread.
			// When done, remember that all registration is done.
			URI uri;
			try {
				uri = new URI("http://www.brickwedde.de/nagiosnotifier.php?cmd=key&key=" + registration);
		        HttpGet get = new HttpGet(uri);
		        DefaultHttpClient client = new DefaultHttpClient();
		        HttpResponse res = client.execute(get);
		        Log.d("c2dm", res.toString());
			} catch (URISyntaxException e) {
				e.printStackTrace();
			} catch (ClientProtocolException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	private void handleMessage(Context context, Intent intent) {
		String s = intent.getStringExtra("message");
		
		NotificationManager mNotificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
		Notification notification = null;
		int icon = R.drawable.ic_launcher;
		CharSequence tickerText = "Nagios Message!";
		long when = System.currentTimeMillis();
		notification = new Notification(icon, tickerText, when);
		notification.flags |= Notification.FLAG_INSISTENT;
		notification.defaults |= Notification.DEFAULT_SOUND;
		CharSequence contentTitle = "Nagios Message!";
		CharSequence contentText = s;
		PendingIntent contentIntent = PendingIntent.getActivity(context, 0, new Intent(), 0);
		notification.setLatestEventInfo(context, contentTitle, contentText, contentIntent);
		mNotificationManager.notify(1, notification);

		Log.d("c2dm", "handleMessage:"+s);
	}

}