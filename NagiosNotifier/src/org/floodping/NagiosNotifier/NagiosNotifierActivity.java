package org.floodping.NagiosNotifier;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class NagiosNotifierActivity extends Activity implements OnClickListener {
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Helper.Register(this);

		LinearLayout mainPanel = new LinearLayout(this);
		mainPanel.setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		mainPanel.setOrientation(LinearLayout.VERTICAL);
		mainPanel.setBackgroundColor(0);
		
		TextView text1 = new TextView(this);
		text1.setText("Die Notifizierung wird jetzt und bei jedem Neustart aktiviert. Sie können 'Close' betätigen...");
		mainPanel.addView(text1);

		Button button = new Button(this);
		button.setText("Close");
		mainPanel.addView(button);
		button.setClickable(true);
		button.setOnClickListener(this);
		
		this.setContentView(mainPanel);
	}

	@Override
	public void onClick(View v) {
		this.finish();
	}
}