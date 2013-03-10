package org.floodping;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.URL;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Formatter;
import java.util.Locale;
import java.util.TimeZone;

public class UdpReceiver
    implements Runnable
{

  @Override
  public void run ()
  {
    while (true)
    {
      try
      {
        internal_run ();
      }
      catch (Exception e)
      {
        e.printStackTrace ();
      }
    }
  }

  public String GetUrl(String sUrl)
  {
	  
	try {
	  URL uUrl;
      uUrl = new URL(sUrl);
	  BufferedReader in = new BufferedReader(new InputStreamReader(uUrl.openStream()));

	  String inputLine;
	  String sRes = "";
	  while ((inputLine = in.readLine()) != null)
	      {
		  	sRes += inputLine;
	      }

	  in.close();	  
	  return sRes;
	} catch (Exception e) {
		e.printStackTrace();
	}
	return null;
  }

  public double calc_dewpoint (int h, int t)
  {
    double H, dew_point;
    H = (Math.log10 (h) - 2.0) / 0.4343 + (17.62 * t) / (243.12 + t);
    dew_point = 243.12 * H / (17.62 - H);
    return Math.round (dew_point * 10) / 10;
  }

  private void internal_run ()
  {
    DatagramSocket serverSocket;
    try
    {
      serverSocket = new DatagramSocket (12345);
    }
    catch (SocketException e1)
    {
      e1.printStackTrace ();
      System.exit (1);
      return;
    }

    final byte[] receiveData = new byte[1024];

    while (true)
    {
      final DatagramPacket receivePacket = new DatagramPacket (receiveData, receiveData.length);
      try
      {
        serverSocket.setSoTimeout (1000);
        serverSocket.receive (receivePacket);
      }
      catch (SocketTimeoutException e1)
      {
        continue;
      }
      catch (SocketException e1)
      {
        e1.printStackTrace ();
        return;
      }
      catch (IOException e)
      {
        e.printStackTrace ();
        return;
      }

      final DataInputStream dis = new DataInputStream (new ByteArrayInputStream (receiveData));

      try
      {
        String airid = "XXXX";
        {
          final Formatter f = new Formatter ();
          airid = f.format ("%c%c%c%c", dis.readByte (), dis.readByte (), dis.readByte (), dis.readByte ()).toString ();
        }

        final byte type = dis.readByte ();
        switch (type)
        {
        case 'g':
        {
          final short x1 = (short) ((dis.readByte () & 0xff) | (dis.readByte () & (0xff << 8)));
          final short y1 = (short) ((dis.readByte () & 0xff) | (dis.readByte () & (0xff << 8)));
          final short z1 = (short) ((dis.readByte () & 0xff) | (dis.readByte () & (0xff << 8)));
          dis.readByte ();
          final short x2 = (short) ((dis.readByte () & 0xff) | (dis.readByte () & (0xff << 8)));
          final short y2 = (short) ((dis.readByte () & 0xff) | (dis.readByte () & (0xff << 8)));
          final short z2 = (short) ((dis.readByte () & 0xff) | (dis.readByte () & (0xff << 8)));
          if ((x1 != x2) || (y1 != y2) || (z1 != z2))
          {
            System.out.println ("error: " + x1 + "!=" + x2 + " || " + y1 + "!=" + y2 + " || " + z1 + "!=" + z2 + "");
            break;
          }
          final double xx = (x1 * 1.0) / 4.6;
          final double yx = (y1 * 1.0) / 4.6;
          final double zx = (z1 * 1.0) / 4.6;

          final double x = xx;
          final int res = x < -9 ? (x < -13 ? 2 : 1) : 0;
          System.out.println ("" + airid + " g:" + xx + "," + yx + "," + zx);

          SimpleDateFormat df = new SimpleDateFormat ("dd.MM HH:mm:ss");
          df.setTimeZone (TimeZone.getDefault ());
          Main.PutValue (airid, new Integer (new Double (x).intValue ()).toString (), df.format (new Date ()));

          try
          {
            final Formatter cmdf = new Formatter ();
            final String command = cmdf.format ("/usr/bin/submit_check_result ned %s %d %+3.1fcm", airid, res, x).toString ();
            System.out.println ("" + command);
            Runtime.getRuntime ().exec (command);
          }
          catch (final Exception e)
          {
            System.err.println ("Errore: " + e.getMessage ());
          }

          try
          {
            final String sFile = "/tmp/airid" + airid;
            final FileWriter fstream = new FileWriter (sFile);
            final BufferedWriter out = new BufferedWriter (fstream);
            final Formatter cmdf = new Formatter ();
            out.write (cmdf.format (Locale.ENGLISH,"%+3.1f", x).toString ());
            out.close ();

            final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "%20" + cmdf.toString () + "&XHR=1";
            System.out.println (this.GetUrl(sUrl));
          }
          catch (final Exception e)
          {
            System.err.println ("Error: " + e.getMessage ());
          }

        }
          break;
        case 'f':
        {
          final int rh1 = ((dis.readByte () & 0xff) | (dis.readByte ()) << 8);
          final int t1 = ((dis.readByte () & 0xff) | (dis.readByte () & 0xff) << 8);
          final int p1 = ((dis.readByte () & 0xff) | (dis.readByte () & 0xff) << 8);
          dis.readByte ();
          final int rh2 = ((dis.readByte () & 0xff) | (dis.readByte ()) << 8);
          final int t2 = ((dis.readByte () & 0xff) | (dis.readByte () & 0xff) << 8);
          final int p2 = ((dis.readByte () & 0xff) | (dis.readByte () & 0xff) << 8);
          if ((p1 != p2) || (t1 != t2) || (rh1 != rh2))
          {
            System.out.println ("error f: " + rh1 + "!=" + rh2 + " || " + t1 + "!=" + t2 + " || " + p1 + "!=" + p2 + "");
            break;
          }
          final double T = (t1 * 1.0) / 10;
          final int P = p1;
          int RH = rh1 + 55;

          if (RH < 0)
          {
            System.out.println ("RH < 0: " + rh1);
            RH = -1;
          }
          if (RH > 100)
          {
            System.out.println ("RH > 100: " + rh1);
            RH = 101;
          }

          System.out.println ("" + airid + " F:" + T + "," + P + "," + RH);

          if ((RH >= 0) && (RH <= 100))
          {

            double Dew = this.calc_dewpoint (RH, new Double (T).intValue ());

            SimpleDateFormat df = new SimpleDateFormat ("dd.MM HH:mm:ss");
            df.setTimeZone (TimeZone.getDefault ());
            Main.PutValue (airid + "T", new Double (T).toString (), df.format (new Date ()));
            Main.PutValue (airid + "D", new Double (Dew).toString (), df.format (new Date ()));
            Main.PutValue (airid + "P", new Integer (P).toString (), df.format (new Date ()));
            Main.PutValue (airid + "RH", new Integer (RH).toString (), df.format (new Date ()));

            try
            {
              final String sFile = "/tmp/airid" + airid + "T";
              final FileWriter fstream = new FileWriter (sFile);
              final BufferedWriter out = new BufferedWriter (fstream);
              final Formatter cmdf = new Formatter ();
              out.write (cmdf.format ("%+3.1f", T).toString ());
              out.close ();

              final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "T%20" + cmdf.toString () + "&XHR=1";
              System.out.println (this.GetUrl(sUrl));
            }
            catch (final Exception e)
            {
              System.err.println ("Error: " + e.getMessage ());
            }
            try
            {
              final Formatter cmdf = new Formatter ();
              final String command = cmdf.format ("/usr/bin/submit_check_result ned %sT 0 %+3.1fdegC", airid, T).toString ();
              System.out.println ("" + command);
              Runtime.getRuntime ().exec (command);
            }
            catch (final Exception e)
            {
              System.err.println ("Errore: " + e.getMessage ());
            }

            try
            {
              final String sFile = "/tmp/airid" + airid + "D";
              final FileWriter fstream = new FileWriter (sFile);
              final BufferedWriter out = new BufferedWriter (fstream);
              final Formatter cmdf = new Formatter ();
              out.write (cmdf.format ("%+3.1f", Dew).toString ());
              out.close ();
              final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "D%20" + cmdf.toString () + "&XHR=1";
              System.out.println (this.GetUrl(sUrl));
            }
            catch (final Exception e)
            {
              System.err.println ("Error: " + e.getMessage ());
            }
            try
            {
              final Formatter cmdf = new Formatter ();
              final String command = cmdf.format ("/usr/bin/submit_check_result ned %sD 0 %+3.1fdegC", airid, Dew).toString ();
              System.out.println ("" + command);
              Runtime.getRuntime ().exec (command);
            }
            catch (final Exception e)
            {
              System.err.println ("Errore: " + e.getMessage ());
            }

            try
            {
              final String sFile = "/tmp/airid" + airid + "P";
              final FileWriter fstream = new FileWriter (sFile);
              final BufferedWriter out = new BufferedWriter (fstream);
              final Formatter cmdf = new Formatter ();
              out.write (cmdf.format ("%+4d", P).toString ());
              out.close ();
              final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "P%20" + cmdf.toString () + "&XHR=1";
              System.out.println (this.GetUrl(sUrl));
            }
            catch (final Exception e)
            {
              System.err.println ("Error: " + e.getMessage ());
            }
            try
            {
              final Formatter cmdf = new Formatter ();
              final String command = cmdf.format ("/usr/bin/submit_check_result ned %sP 0 %+4dhPa", airid, P).toString ();
              System.out.println ("" + command);
              Runtime.getRuntime ().exec (command);
            }
            catch (final Exception e)
            {
              System.err.println ("Errore: " + e.getMessage ());
            }

            
            try
            {
              final String sFile = "/tmp/airid" + airid + "RH";
              final FileWriter fstream = new FileWriter (sFile);
              final BufferedWriter out = new BufferedWriter (fstream);
              final Formatter cmdf = new Formatter ();
              out.write (cmdf.format ("%+3d", RH).toString ());
              out.close ();
              final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "RH%20" + cmdf.toString () + "&XHR=1";
              System.out.println (this.GetUrl(sUrl));
            }
            catch (final Exception e)
            {
              System.err.println ("Error: " + e.getMessage ());
            }

            try
            {
              final Formatter cmdf = new Formatter ();
              final String command = cmdf.format ("/usr/bin/submit_check_result ned %sRH 0 %+3d%%rH", airid, RH).toString ();
              System.out.println ("" + command);
              Runtime.getRuntime ().exec (command);
            }
            catch (final Exception e)
            {
              System.err.println ("Errore: " + e.getMessage ());
            }
            
          }

        }
          break;
        case 'T':
        {
          byte x1 = dis.readByte ();
          byte x2 = dis.readByte ();
          final short temp = (short) (((x2 & 0xff) << 8) | (x1 & 0xff));
          System.out.println ("T:" + temp);
          final double t = (temp * 1.0) / 16;
          final Formatter f = new Formatter ();
          final String id = f.format ("%02x-%02x %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", x1, x2, dis.readByte (), dis.readByte (), dis.readByte (), dis.readByte (), dis.readByte (), dis.readByte (), dis.readByte (), dis.readByte ()).toString ();
          x1 = dis.readByte ();
          x2 = dis.readByte ();
          final short temp2 = (short) (((x2 & 0xff) << 8) | (x1 & 0xff));
          if (temp != temp2)
          {
            break;
          }

          System.out.println ("" + airid + " T:" + t + "," + id);
          SimpleDateFormat df = new SimpleDateFormat ("dd.MM HH:mm:ss");
          df.setTimeZone (TimeZone.getDefault ());
          Main.PutValue (airid, new Double (t).toString (), df.format (new Date ()));
          try
          {
            final Formatter cmdf = new Formatter ();
            final String command = cmdf.format ("/usr/bin/submit_check_result ned %s 0 %+3.1fdegC", airid, t).toString ();
            System.out.println ("" + command);
            Runtime.getRuntime ().exec (command);
          }
          catch (final Exception e)
          {
            System.err.println ("Errore: " + e.getMessage ());
          }

          try
          {
            final String sFile = "/tmp/airid" + airid;
            final FileWriter fstream = new FileWriter (sFile);
            final BufferedWriter out = new BufferedWriter (fstream);
            final Formatter cmdf = new Formatter ();
            out.write (cmdf.format ("%+3.1f", t).toString ());
            out.close ();
            final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "%20" + cmdf.toString () + "&XHR=1";
            System.out.println (this.GetUrl(sUrl));
          }
          catch (final Exception e)
          {// Catch exception if
           // any
            System.err.println ("Error: " + e.getMessage ());
          }
        }
          break;
        case 'M':
        {
          byte x1 = dis.readByte ();
          byte x2 = dis.readByte ();
          final short move = (short) (((x2 & 0xff) << 8) | (x1 & 0xff));
          x1 = dis.readByte ();
          x2 = dis.readByte ();
          final short move2 = (short) (((x2 & 0xff) << 8) | (x1 & 0xff));
          if (move != move2)
          {
//            break;
          }

          System.out.println ("" + airid + " M:" + move);
          SimpleDateFormat df = new SimpleDateFormat ("dd.MM HH:mm:ss");
          df.setTimeZone (TimeZone.getDefault ());
          Main.PutValue (airid, new Integer (move).toString (), df.format (new Date ()));
          try
          {
            final Formatter cmdf = new Formatter ();
            final String command = cmdf.format ("/usr/bin/submit_check_result ned %s 0 %+1ddegC", airid, move).toString ();
            System.out.println ("" + command);
            Runtime.getRuntime ().exec (command);
          }
          catch (final Exception e)
          {
            System.err.println ("Errore: " + e.getMessage ());
          }

          try
          {
            final String sFile = "/tmp/airid" + airid;
            final FileWriter fstream = new FileWriter (sFile);
            final BufferedWriter out = new BufferedWriter (fstream);
            final Formatter cmdf = new Formatter ();
            out.write (cmdf.format ("%+1d", move).toString ());
            out.close ();
            final String sUrl = "http://10.1.0.3:8083/fhem?cmd=set%20airid" + airid + "%20" + cmdf.toString () + "&XHR=1";
            System.out.println (this.GetUrl(sUrl));
          }
          catch (final Exception e)
          {// Catch exception if
           // any
            System.err.println ("Error: " + e.getMessage ());
          }
        }
          break;
        default:
          final String sentence = new String (receivePacket.getData ());
          System.out.println ("RECEIVED: " + sentence);
        }
      }
      catch (IOException e)
      {
        e.printStackTrace ();
      }
    }
  }
}
