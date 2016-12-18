package redlaboratory.jvjoyinterface;

public class JoystickState {
	/** Index of device. 1-based. */
	public byte bDevice;
	public long wThrottle;
	public long wRudder;
	public long wAileron;
	public long wAxisX;
	public long wAxisY;
	public long wAxisZ;
	public long wAxisXRot;
	public long wAxisYRot;
	public long wAxisZRot;
	public long wSlider;
	public long wDial;
	public long wWheel;
	public long wAxisVX;
	public long wAxisVY;
	public long wAxisVZ;
	public long wAxisVBRX;
	public long wAxisVBRY;
	public long wAxisVBRZ;
	/** 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed */
	public long lButtons;
	/** Lower 4 bits: HAT switch or 16-bit of continuous HAT switch */
	public long bHats;
	/** Lower 4 bits: HAT switch or 16-bit of continuous HAT switch */
	public long bHatsEx1;
	/** Lower 4 bits: HAT switch or 16-bit of continuous HAT switch */
	public long bHatsEx2;
	/** Lower 4 bits: HAT switch or 16-bit of continuous HAT switch long lButtonsEx1; */
	public long bHatsEx3;
	
	/** Buttons 33-64 */
	public long lButtonsEx1;
	/** Buttons 65-96 */
	public long lButtonsEx2;
	/** Buttons 97-128 */
	public long lButtonsEx3;
}
