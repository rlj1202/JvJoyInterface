package redlaboratory.jvjoyinterface;

public class VJoy {
	
	static {
		try {
			String architecture = System.getProperty("sun.arch.data.model");
			
			if (architecture.equals("32")) {
				System.loadLibrary("32/vJoyInterface");
				System.loadLibrary("32/libJvJoyInterfaceNative");
			} else if (architecture.equals("64")) {
				System.loadLibrary("64/vJoyInterface");
				System.loadLibrary("64/libJvJoyInterfaceNative");
			} else {
//				throw new UnexpectedException("Unexpected architecture: " + architecture);
			}
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
		}
	}
	
	public static final int NO_HANDLE_BY_INDEX = -1;
	public static final int BAD_PREPARSED_DATA = -2;
	public static final int NO_CAPS = -3;
	public static final int BAD_N_BTN_CAPS = -4;
	public static final int BAD_CALLOC = -5;
	public static final int BAD_BTN_CAPS = -6;
	public static final int BAD_BTN_RANGE = -7;
	public static final int BAD_N_VAL_CAPS = -8;
	public static final int BAD_ID_RANGE = -9;
	public static final int NO_SUCH_AXIS = -10;
	public static final int BAD_DEV_STAT = -11;
	public static final int NO_DEV_EXIST = -12;
	public static final int NO_FILE_EXIST = -13;
	
	public static final int AXIS_MIN_VALUE = 0;
	public static final int AXIS_MID_VALUE = 16384;
	public static final int AXIS_MAX_VALUE = 32768;
	
	public static final int HID_USAGE_X = 0x30;
	public static final int HID_USAGE_Y = 0x31;
	public static final int HID_USAGE_Z = 0x32;
	public static final int HID_USAGE_RX = 0x33;
	public static final int HID_USAGE_RY = 0x34;
	public static final int HID_USAGE_RZ = 0x35;
	public static final int HID_USAGE_SL0 = 0x36;
	public static final int HID_USAGE_SL1 = 0x37;
	public static final int HID_USAGE_WHL = 0x38;
	public static final int HID_USAGE_POV = 0x39;
	
	public static final int HID_USAGE_CONST = 0x26;
	public static final int HID_USAGE_RAMP = 0x27;
	public static final int HID_USAGE_SQUR = 0x30;
	public static final int HID_USAGE_SINE = 0x31;
	public static final int HID_USAGE_TRNG = 0x32;
	public static final int HID_USAGE_STUP = 0x33;
	public static final int HID_USAGE_STDN = 0x34;
	public static final int HID_USAGE_SPRNG = 0x40;
	public static final int HID_USAGE_DMPR = 0x41;
	public static final int HID_USAGE_INRT = 0x42;
	public static final int HID_USAGE_FRIC = 0x43;
	
	public static final int HID_ID_STATE = 0x02;
	public static final int HID_ID_EFFREP = 0x01;
	public static final int HID_ID_ENVREP = 0x02;
	public static final int HID_ID_CONDREP = 0x03;
	public static final int HID_ID_PRIDREP = 0x04;
	public static final int HID_ID_CONSTREP = 0x05;
	public static final int HID_ID_RAMPREP = 0x06;
	public static final int HID_ID_CSTMREP = 0x07;
	public static final int HID_ID_SMPLREP = 0x08;
	public static final int HID_ID_EFOPREP = 0x0A;
	public static final int HID_ID_BLKFRREP = 0x0B;
	public static final int HID_ID_CTRLREP = 0x0C;
	public static final int HID_ID_GAINREP = 0x0D;
	public static final int HID_ID_SETCREP = 0x0E;
	public static final int HID_ID_NEWEFREP = 0x01;
	public static final int HID_ID_BLKLDREP = 0x02;
	public static final int HID_ID_POOLREP = 0x03;
	
	public VJoy() {
		
	}
	
	public native short getvJoyVersion();
	public native boolean vJoyEnabled();
	public native String getvJoyProductString();
	public native String getvJoyManufacturerString();
	public native String getvJoySerialNumberString();
	public native boolean driverMatch();
	public native void registerRemovalCB(RemovalCB cb, Object data);
	public native boolean vJoyFfbCap();
	public native int getvJoyMaxDevices();
	public native int getNumberExistingVJD();

	public native int getVJDButtonNumber(int rID);
	public native int getVJDDiscPovNumber(int rID);
	public native int getVJDContPovNumber(int rID);
	public native boolean getVJDAxisExist(int rID, int Axis);
	public native long getVJDAxisMax(int rID, int Axis);
	public native long getVJDAxisMin(int rID, int Axis);
	public native VjdStat getVJDStatus(int rID);
	public native boolean isVJDExists(int rID);																			
	public native int getOwnerPid(int rID);

	public native boolean acquireVJD(int rID);
	public native void relinquishVJD(int rID);
	public native boolean updateVJD(int rID, JoystickState pData);

	public native boolean resetVJD(int rID);
	public native void resetAll();
	public native boolean resetButtons(int rID);
	public native boolean resetPovs(int rID);

	public native boolean setAxis(long Value, int rID, int Axis); 
	public native boolean setBtn(boolean Value, int rID, int nBtn); 
	public native boolean setDiscPov(int Value, int rID, int nPov); 
	public native boolean setContPov(long Value, int rID, int nPov);
	
	//
	
//	public native FFBEType ffbGetEffect();
//	public native void ffbRegisterGenCB(FfbGenCB cb, Object data);
//	
//	public native boolean isDeviceFfb(int rID);
//	public native boolean isDeviceFfbEffect(int rID, int Effect);
//	
//	public native long ffb_h_DeviceID(FFB_DATA * Packet, int *DeviceID);
//	public native long ffb_h_Type(FFB_DATA * Packet, FFBPType *Type);
//	public native long ffb_h_Packet(FFB_DATA * Packet, WORD *Type, int *DataSize, byte *Data[]);
//	public native long ffb_h_EBI(FFB_DATA * Packet, int *Index);
//	public native long ffb_h_Eff_Report(FFB_DATA * Packet, FFB_EFF_REPORT*  Effect);
//	public native long ffb_h_Eff_Ramp(FFB_DATA * Packet, FFB_EFF_RAMP*  RampEffect);
//	public native long ffb_h_EffOp(FFB_DATA * Packet, FFB_EFF_OP*  Operation);
//	public native long ffb_h_DevCtrl(FFB_DATA * Packet, FFB_CTRL *  Control);
//	public native long ffb_h_Eff_Period(FFB_DATA * Packet, FFB_EFF_PERIOD*  Effect);
//	public native long ffb_h_Eff_Cond(FFB_DATA * Packet, FFB_EFF_COND*  Condition);
//	public native long ffb_h_DevGain(FFB_DATA * Packet, byte * Gain);
//	public native long ffb_h_Eff_Envlp(FFB_DATA * Packet, FFB_EFF_ENVLP*  Envelope);
//	public native long ffb_h_EffNew(FFB_DATA * Packet, FFBEType * Effect);
//	
//	public native long ffb_h_Eff_Constant(FFB_DATA * Packet, FFB_EFF_CONSTANT *  ConstantEffect);
	
}
