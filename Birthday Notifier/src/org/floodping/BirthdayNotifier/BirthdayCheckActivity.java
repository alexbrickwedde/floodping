package org.floodping.BirthdayNotifier;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Iterator;

import org.floodping.BirthdayNotifier.R;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.provider.ContactsContract.Data;
import android.provider.ContactsContract.CommonDataKinds.Event;

public class BirthdayCheckActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		test(this);
		this.finish();
	}

	public static Cursor getList(Context context) {
		ContentResolver cr = context.getContentResolver();

		String[] projection = new String[] { ContactsContract.CommonDataKinds.Event.START_DATE, ContactsContract.CommonDataKinds.Event._ID };
		String where = Data.MIMETYPE + "=? AND " + ContactsContract.CommonDataKinds.Event.TYPE + "=?";
		String[] selectionArgs = new String[] { Event.CONTENT_ITEM_TYPE, Integer.toString(ContactsContract.CommonDataKinds.Event.TYPE_BIRTHDAY) };

		Cursor managedCursor = cr.query(ContactsContract.Data.CONTENT_URI, projection, where, selectionArgs, null);
		return managedCursor;
	}

	public static Cursor getContact(Context context, String sId) {
		ContentResolver cr = context.getContentResolver();

		String[] projection = new String[] { ContactsContract.Contacts.DISPLAY_NAME, ContactsContract.Contacts._ID };
		String where = ContactsContract.Contacts._ID + "= ?";
		String[] selectionArgs = new String[] { sId };

		Cursor managedCursor = cr.query(ContactsContract.Data.CONTENT_URI, projection, where, selectionArgs, null);
		return managedCursor;
	}

	public static void test(Context context) {
		Cursor cursor = getList(context);
		if (!cursor.moveToFirst()) {
			return;
		}
		Calendar dNow = GregorianCalendar.getInstance();
		int uiMonth = dNow.get(GregorianCalendar.MONTH);
		int uiDay = dNow.get(GregorianCalendar.DAY_OF_MONTH);

		ArrayList<String> sContactIds = new ArrayList<String>();

		while (cursor.moveToNext()) {
			final int dateColumn = cursor.getColumnIndex(ContactsContract.CommonDataKinds.Event.START_DATE);
			do {
				try {
					final String sDate = cursor.getString(dateColumn);
					SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
					Date dDate = formatter.parse(sDate);
					Calendar cDate = GregorianCalendar.getInstance();
					cDate.setTime(dDate);
					int uiMonth2 = cDate.get(GregorianCalendar.MONTH);
					int uiDay2 = cDate.get(GregorianCalendar.DAY_OF_MONTH);
					if ((uiMonth == uiMonth2) && (uiDay == uiDay2)) {
						final String sId = cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Event._ID));
						Cursor cContact = getContact(context, sId);
						if (cContact.moveToFirst()) {
							String sName = cContact.getString(cContact.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
							if (!sContactIds.contains(sName)) {
								sContactIds.add(sName);
							}
						}
					}
				} catch (ParseException e) {
					e.printStackTrace();
				}

			} while (cursor.moveToNext());
		}

		Iterator<String> itS = sContactIds.iterator();
		String sNames = new String();
		if (itS.hasNext()) {
			while (itS.hasNext()) {
				String sName = itS.next();
				sNames += sName + " ";
			}

			NotificationManager mNotificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
			// Toast.makeText(context, sNames, Toast.LENGTH_LONG).show();
			Notification notification = null;
			int icon = R.drawable.ic_launcher;
			CharSequence tickerText = "Birthdays today!";
			long when = System.currentTimeMillis();
			notification = new Notification(icon, tickerText, when);
			notification.flags |= Notification.FLAG_INSISTENT;
			notification.defaults |= Notification.DEFAULT_SOUND;
			notification.defaults |= Notification.DEFAULT_VIBRATE;
			CharSequence contentTitle = "Birthdays today!";
			CharSequence contentText = sNames;
			PendingIntent contentIntent = PendingIntent.getActivity(context, 0, new Intent(), 0);
			notification.setLatestEventInfo(context, contentTitle, contentText, contentIntent);
			mNotificationManager.notify(1, notification);
		}
	}

}