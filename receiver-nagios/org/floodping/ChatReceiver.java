package org.floodping;

import org.jivesoftware.smack.Chat;
import org.jivesoftware.smack.ChatManager;
import org.jivesoftware.smack.ChatManagerListener;
import org.jivesoftware.smack.ConnectionConfiguration;
import org.jivesoftware.smack.MessageListener;
import org.jivesoftware.smack.XMPPConnection;
import org.jivesoftware.smack.XMPPException;
import org.jivesoftware.smack.packet.Message;
import org.jivesoftware.smack.packet.Presence;

public class ChatReceiver
    implements MessageListener, ChatManagerListener, Runnable
{
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
          sResult += Main.GetValue ("0101", "Wasserstand:", "cm");
          sResult += Main.GetValue ("0102T", "Temperatur:", "°C");
          sResult += Main.GetValue ("0102P", "Luftdruck:", "hPa");
          sResult += Main.GetValue ("0102RH", "Luftfeuchte:", "%");
          sResult += Main.GetValue ("0102D", "Taupunkt:", "°C");
          sResult += Main.GetValue ("0201", "Bewegung:", "");
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

  public String m_sUser;
  public String m_sPass;

  public void run ()
  {
    while (true)
    {
      {
        final ConnectionConfiguration connConfig = new ConnectionConfiguration ("talk.google.com", 5222, "gmail.com");
        final XMPPConnection connection = new XMPPConnection (connConfig);

        try
        {
          connection.connect ();
          System.out.println ("Connected to " + connection.getHost ());

          System.out.println ("Logging in as " + this.m_sUser);
          connection.login (this.m_sUser, this.m_sPass);
          System.out.println ("Logged in as " + connection.getUser ());

          final Presence presence = new Presence (Presence.Type.available);
          connection.sendPacket (presence);

        }
        catch (final XMPPException ex)
        {
          System.out.println ("Failed to log in as " + connection.getUser ());
          continue;
        }

        final ChatManager chatmanager = connection.getChatManager ();
        chatmanager.addChatListener (this);

        while (connection.isConnected ())
        {
          try
          {
            Thread.sleep (100);
          }
          catch (InterruptedException e)
          {
            e.printStackTrace ();
            return;
          }
        }

        chatmanager.removeChatListener (this);
        connection.disconnect ();
      }
    }
  }
}
