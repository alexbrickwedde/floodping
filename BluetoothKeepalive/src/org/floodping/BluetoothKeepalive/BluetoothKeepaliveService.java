package org.floodping.BluetoothKeepalive;

import org.floodping.BluetoothKeepalive.R;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
import android.os.PowerManager;
import android.widget.Toast;

public class BluetoothKeepaliveService extends Service {

	private final BroadcastReceiver mReceiver = new BroadcastReceiver() {

		private PowerManager.WakeLock wl = null;

		@Override
		public void onReceive(Context context, Intent intent) {
			NotificationManager mNotificationManager = null;
			mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

			String action = intent.getAction();
			BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

			if (wl == null) {
				PowerManager pm = null;
				pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
				if (pm == null) {
					return;
				}
				wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "org.floodping.BluetoothKeepalive.BluetoothKeepaliveService");
				if (wl == null) {
					return;
				}
			}

			if (BluetoothDevice.ACTION_FOUND.equals(action)) {
				// Device found
			} else if (BluetoothDevice.ACTION_ACL_CONNECTED.equals(action)) {
				Toast.makeText(context, "BluetoothKeepalive recognized connect", Toast.LENGTH_SHORT).show();
				if (!wl.isHeld()) {
					Notification notification = null;
					int icon = R.drawable.ic_launcher;
					CharSequence tickerText = "BTKA got Wakelock";
					long when = System.currentTimeMillis();
					notification = new Notification(icon, tickerText, when);
					notification.flags |= Notification.FLAG_NO_CLEAR;
					CharSequence contentTitle = "BluetoothKeepalive";
					CharSequence contentText = "Wakelock is being held by BluetoothKeepalive Service";
					PendingIntent contentIntent = PendingIntent.getActivity(getApplicationContext(), 0, new Intent(), 0);

					notification.setLatestEventInfo(context, contentTitle, contentText, contentIntent);
					mNotificationManager.notify(1, notification);
				}
				wl.acquire();

			} else if (BluetoothDevice.ACTION_ACL_DISCONNECTED.equals(action)) {

				Toast.makeText(context, "BluetoothKeepalive recognized BT disconnect", Toast.LENGTH_SHORT).show();
				if (wl.isHeld()) {
					wl.release();
				}
				if (!wl.isHeld()) {
					mNotificationManager.cancel(1);
				}
			} else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
			} else if (BluetoothDevice.ACTION_ACL_DISCONNECT_REQUESTED.equals(action)) {
			}
		}

	};

	@Override
	public void onCreate() {
	}

	@Override
	public void onStart(Intent intent, int startId) {
		Toast.makeText(this, "BluetoothKeepalive Service started", Toast.LENGTH_SHORT).show();
		IntentFilter filter1 = new IntentFilter(BluetoothDevice.ACTION_ACL_CONNECTED);
		IntentFilter filter2 = new IntentFilter(BluetoothDevice.ACTION_ACL_DISCONNECT_REQUESTED);
		IntentFilter filter3 = new IntentFilter(BluetoothDevice.ACTION_ACL_DISCONNECTED);
		this.registerReceiver(mReceiver, filter1);
		this.registerReceiver(mReceiver, filter2);
		this.registerReceiver(mReceiver, filter3);
	}

	@Override
	public void onDestroy() {
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}
}
