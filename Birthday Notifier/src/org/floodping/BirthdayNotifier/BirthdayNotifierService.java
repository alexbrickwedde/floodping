package org.floodping.BirthdayNotifier;

import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.widget.Toast;

public class BirthdayNotifierService extends Service {

	@Override
	public void onCreate() {
	}

	Timer mTimer = null; 
	@Override
	public void onStart(Intent intent, int startId) {
		Toast.makeText(this, "Birthday Notifier Service started", Toast.LENGTH_SHORT).show();
		
		mTimer = new Timer();
        TimerTask timerTask = new TimerTask(){
            @Override
            public void run(){
            	Intent i3 = new Intent("org.floodping.BirthdayNotifier.BirthdayCheckActivity");
            	i3.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(i3);
            }
        };
        Date dNow = new Date();
        Date dDate = new Date();
        dDate.setHours(12);
        dDate.setMinutes(0);
        if (dNow.after(dDate))
        {
        	long lTime = dDate.getTime();
        	dDate.setTime(lTime + (24 * 60 * 60 * 1000));
        }
        mTimer.schedule(timerTask, dDate, 1000 * 60 * 60 * 24);
	}

	@Override
	public void onDestroy() {
		mTimer.cancel();
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}
}
