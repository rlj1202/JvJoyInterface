package redlaboratory.jvjoyinterface.test;

import static org.junit.Assert.*;

import org.junit.Test;

import redlaboratory.jvjoyinterface.VJoy;
import redlaboratory.jvjoyinterface.VjdStat;

public class JvJoyTest {
	
	@Test
	public void vJoyTest() {
		VJoy vJoy = new VJoy();
		int rID = 1;
		
		assertTrue(vJoy.vJoyEnabled());
		if (!vJoy.vJoyEnabled()) {
			System.out.println("vJoy driver not enabled: Failed Getting vJoy attributes.");
			
			return;
		} else {
			System.out.println("Vender: " + vJoy.getvJoyManufacturerString());
			System.out.println("Product: " + vJoy.getvJoyProductString());
			System.out.println("Version Number: " + vJoy.getvJoyVersion());
		}
		
		assertTrue(vJoy.driverMatch());
		if (vJoy.driverMatch()) {
			System.out.println("Version of Driver Matches DLL Version {0}");
		} else {
			System.out.println("Version of Driver {0} does NOT match DLL Version {1}");
		}
		
		VjdStat status = vJoy.getVJDStatus(rID);
		if ((status == VjdStat.VJD_STAT_OWN) ||
				((status == VjdStat.VJD_STAT_FREE) && (!vJoy.acquireVJD(rID)))) {
			System.out.println("Failed to acquire vJoy device number " + rID);
		} else {
			System.out.println("Acquired: vJoy device number "+ rID);
		}
		
		System.out.println("number of buttons: " + vJoy.getVJDButtonNumber(rID));
		
		assertTrue(vJoy.setAxis(0, rID, VJoy.HID_USAGE_X));
		assertTrue(vJoy.setAxis(16384, rID, VJoy.HID_USAGE_Y));
		assertTrue(vJoy.setAxis(32768, rID, VJoy.HID_USAGE_Z));
		
		assertTrue(vJoy.setAxis(0, rID, VJoy.HID_USAGE_RX));
		assertTrue(vJoy.setAxis(16384, rID, VJoy.HID_USAGE_RY));
		assertTrue(vJoy.setAxis(32768, rID, VJoy.HID_USAGE_RZ));
		
		assertTrue(vJoy.setAxis(0, rID, VJoy.HID_USAGE_SL0));
		assertTrue(vJoy.setAxis(16384, rID, VJoy.HID_USAGE_SL1));
		
		for (int i = 1; i <= 32; i++) vJoy.setBtn(Math.random() > 0.5 ? true : false, rID, i);
		
		return;
	}
	
}
