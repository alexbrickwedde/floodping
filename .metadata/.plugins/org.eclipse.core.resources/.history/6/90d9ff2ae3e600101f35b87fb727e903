package org.floodping;

import java.io.FileInputStream;
import java.util.HashMap;
import java.util.Properties;

public class Main
{
  private static volatile HashMap<String, String> aValues = new HashMap<String, String> ();
  private static volatile HashMap<String, String> aTime = new HashMap<String, String> ();

  public static String GetValue (String sId, String sText, String sUnit)
  {
    synchronized (aValues)
    {
      String sRes = Main.aValues.get (sId);
      if (sRes != null)
      {
        return sText + sRes + sUnit + " @" + Main.aTime.get (sId) + "\r";
      }
      return sText + " unbekannt\r";
    }
  }

  public static void PutValue (String sId, String sText, String sTime)
  {
    synchronized (aValues)
    {
      Main.aValues.put (sId, sText);
      Main.aTime.put (sId, sTime);
    }
  }

  public static void main (final String[] args)
  {
    try
    {
      final Properties p = new Properties ();
      p.load (new FileInputStream ("/etc/receiver-nagios.conf"));

      Thread URT = new Thread (new UdpReceiver ());
      URT.start ();

      ChatReceiver CR = new ChatReceiver ();
      Thread CRT = new Thread (CR);
      CR.m_sUser = p.getProperty ("username");
      CR.m_sPass = p.getProperty ("password");
      CRT.start ();

      while (true)
      {
        Thread.sleep (1000);
      }
    }
    catch (final Exception e)
    {
      e.printStackTrace ();
    }
  }

}
