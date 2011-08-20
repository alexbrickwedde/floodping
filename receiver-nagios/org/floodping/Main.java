package org.floodping;

import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Formatter;
import java.util.HashMap;
import java.util.Properties;
import java.util.TimeZone;

import org.jivesoftware.smack.Chat;
import org.jivesoftware.smack.ChatManager;
import org.jivesoftware.smack.ChatManagerListener;
import org.jivesoftware.smack.ConnectionConfiguration;
import org.jivesoftware.smack.MessageListener;
import org.jivesoftware.smack.XMPPConnection;
import org.jivesoftware.smack.XMPPException;
import org.jivesoftware.smack.packet.Message;
import org.jivesoftware.smack.packet.Presence;

public class Main
    implements MessageListener, ChatManagerListener
{
  public static volatile HashMap<String, String> aValues = new HashMap<String, String> ();
  public static volatile HashMap<String, String> aTime = new HashMap<String, String> ();

  public static String GetValue (String sId, String sText, String sUnit)
  {
    String sRes = Main.aValues.get (sId);
    if (sRes != null)
    {
      return sText + sRes + sUnit + " @" + Main.aTime.get (sId) + "\r";
    }
    return sText + " unbekannt\r";
  }

  @Override
  public void processMessage (final Chat chat, final Message message)
  {
    if (message.getType ().equals (org.jivesoftware.smack.packet.Message.Type.chat) && (message.getBody () != null))
    {
      try
      {
        String sResult = "\r";
        switch (message.getBody ().charAt (0))
        {
        default:
          sResult += Main.GetValue ("0001", "Wohnen:", "°C");
          sResult += Main.GetValue ("0002", "Bad:", "°C");
          sResult += Main.GetValue ("0003", "Küche:", "°C");
          sResult += Main.GetValue ("0004", "Terasse:", "°C");
          sResult += Main.GetValue ("0005", "Schlafen:", "°C");
          sResult += Main.GetValue ("0101", "Wasserstand:", "°C");
          final Message msg = new org.jivesoftware.smack.packet.Message (message.getFrom (), org.jivesoftware.smack.packet.Message.Type.chat);
          msg.setBody (sResult);
          chat.sendMessage (msg);
        }
      }
      catch (final Exception ex)
      {
        System.out.println ("Failed to send message");
        ex.printStackTrace ();
      }
    }
    else
    {
      System.out.println ("I got a message I didn''t understand");
    }
  }

  @Override
  public void chatCreated (final Chat arg0, final boolean arg1)
  {
    arg0.addMessageListener (this);
  }

  void run (final String user, final String pass)
  {

    while (true)
    {
      try
      {
        final ConnectionConfiguration connConfig = new ConnectionConfiguration ("talk.google.com", 5222, "gmail.com");
        final XMPPConnection connection = new XMPPConnection (connConfig);

        try
        {
          connection.connect ();
          System.out.println ("Connected to " + connection.getHost ());
        }
        catch (final XMPPException ex)
        {
          System.out.println ("Failed to connect to " + connection.getHost ());
        }
        try
        {
          System.out.println ("Logging in as " + user);
          connection.login (user, pass);
          System.out.println ("Logged in as " + connection.getUser ());

          final Presence presence = new Presence (Presence.Type.available);
          connection.sendPacket (presence);

        }
        catch (final XMPPException ex)
        {
          System.out.println ("Failed to log in as " + connection.getUser ());
          System.exit (1);
        }

        final ChatManager chatmanager = connection.getChatManager ();
        chatmanager.addChatListener (this);

        DatagramSocket serverSocket;
        serverSocket = new DatagramSocket (12345);
        final byte[] receiveData = new byte[1024];
        boolean bLoop = true;
        while (bLoop)
        {
          try
          {
            if (!connection.isConnected ())
            {
              bLoop = false;
            }
            final DatagramPacket receivePacket = new DatagramPacket (receiveData, receiveData.length);
            serverSocket.setSoTimeout (1000);
            serverSocket.receive (receivePacket);

            final DataInputStream dis = new DataInputStream (new ByteArrayInputStream (receiveData));

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

              Main.aValues.put (airid, new Integer (new Double (x).intValue ()).toString ());

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
                out.write (cmdf.format ("%+3.1f", x).toString ());
                out.close ();
              }
              catch (final Exception e)
              {// Catch exception if
               // any
                System.err.println ("Error: " + e.getMessage ());
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

              SimpleDateFormat df = new SimpleDateFormat ("dd.MM HH:mm:ss");
              df.setTimeZone (TimeZone.getDefault ());
              System.out.println ("" + airid + " T:" + t + "," + id);
              Main.aValues.put (airid, new Double (t).toString ());
              Main.aTime.put (airid, df.format (new Date ()));
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
          catch (final Exception e)
          {

          }
        }
        connection.disconnect ();
      }
      catch (final Exception e)
      {
        e.printStackTrace ();
      }
    }
  }

  public static void main (final String[] args)
  {
    final Properties p = new Properties ();
    try
    {
      p.load (new FileInputStream ("/etc/receiver-nagios.conf"));
      new Main ().run (p.getProperty ("username"), p.getProperty ("password"));
    }
    catch (final Exception e)
    {
      e.printStackTrace ();
    }
  }

}
