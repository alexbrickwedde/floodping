package org.floodping.BluetoothKeepalive;

import org.floodping.BluetoothKeepalive.R;

import android.app.Notification;
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

	private PowerManager.WakeLock wl = null;
	private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			BluetoothKeepaliveService.this.onReceiveBtEvent(context, intent);
		}
	};

	protected void onReceiveBtEvent(Context context, Intent intent) {
		//NotificationManager mNotificationManager = null;
		//mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

		String action = intent.getAction();
		//BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

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

		if (BluetoothDevice.ACTION_ACL_CONNECTED.equals(action)) {
			Toast.makeText(context, R.string.RecogConnect, Toast.LENGTH_SHORT).show();
			if (!wl.isHeld()) {
				Notification notification = null;
				int icon = R.drawable.ic_launcher;
				CharSequence tickerText = getResources().getText(R.string.TickerText);
				long when = System.currentTimeMillis();
				notification = new Notification(icon, tickerText, when);
				notification.flags |= Notification.FLAG_NO_CLEAR;
				CharSequence contentTitle = getResources().getText(R.string.app_name);
				CharSequence contentText = getResources().getText(R.string.GotWakeLock);
				PendingIntent contentIntent = PendingIntent.getActivity(getApplicationContext(), 0, new Intent(), 0);

				notification.setLatestEventInfo(context, contentTitle, contentText, contentIntent);
//				mNotificationManager.notify(1, notification);
				this.startForeground(1, notification);
			}
			wl.acquire();

		} else if (BluetoothDevice.ACTION_ACL_DISCONNECTED.equals(action)) {

			Toast.makeText(context, R.string.BtDisconn, Toast.LENGTH_SHORT).show();
			if (wl.isHeld()) {
				wl.release();
			}
			if (!wl.isHeld()) {
//				mNotificationManager.cancel(1);
				this.stopForeground(true);
			}
		} else if (BluetoothAdapter.ACTION_STATE_CHANGED.equals(action)) {
			int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE, BluetoothAdapter.ERROR);
			switch (state) {
			case BluetoothAdapter.STATE_ON:
				break;
			case BluetoothAdapter.STATE_TURNING_OFF:
				if (wl.isHeld()) {
					wl.release();
				}
				if (!wl.isHeld()) {
					this.stopForeground(true);
				}
				break;
			}
		}
	}

	@Override
	public void onCreate() {
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		super.onStartCommand(intent, flags, startId);
		return START_STICKY;
	}

	@Override
	public void onStart(Intent intent, int startId) {
//		Toast.makeText(this, "BluetoothKeepalive Service started", Toast.LENGTH_SHORT).show();
		IntentFilter filter1 = new IntentFilter(BluetoothDevice.ACTION_ACL_CONNECTED);
		filter1.addAction(BluetoothDevice.ACTION_ACL_DISCONNECT_REQUESTED);
		filter1.addAction(BluetoothDevice.ACTION_ACL_DISCONNECTED);
		filter1.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);
		this.registerReceiver(mReceiver, filter1);
	}

	@Override
	public void onDestroy() {
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}
}
