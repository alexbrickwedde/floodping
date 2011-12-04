package org.floodping.BirthdayNotifier;


import android.app.Activity;
import android.os.Bundle;

public class BirthdayNotifierActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Helper.Schedule(this);
		
		this.finish();
	}
	
}