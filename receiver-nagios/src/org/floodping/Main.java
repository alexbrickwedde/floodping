package org.floodping;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class Main {

	public static void main(String[] args) {
		try {
			MulticastSocket serverSocket;
			serverSocket = new MulticastSocket(12345);
			serverSocket.joinGroup(InetAddress.getByName("235.1.1.1"));
			byte[] receiveData = new byte[1024];
			while (true) {
				DatagramPacket receivePacket = new DatagramPacket(receiveData,
						receiveData.length);
				serverSocket.receive(receivePacket);
				String sentence = new String(receivePacket.getData());
				System.out.println("RECEIVED: " + sentence);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

}
