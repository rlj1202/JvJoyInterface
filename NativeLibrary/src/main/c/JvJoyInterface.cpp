#include <windows.h>
#include "public.h"
#include "vjoyinterface.h"

#include "jni.h"
#include "redlaboratory_jvjoyinterface_VJoy.h"

JavaVM * javaVM;

jobject objCb;
jobject objData;

JOYSTICK_POSITION_V2 jobjectToJoystickPositionV2(JNIEnv * env, jobject obj) {
	jclass cls = env->GetObjectClass(obj);

	JOYSTICK_POSITION_V2 result;
	result.bDevice = env->GetByteField(obj, env->GetFieldID(cls, "bDevice", "b"));
	result.wThrottle = env->GetLongField(obj, env->GetFieldID(cls, "wThrottle", "j"));
	result.wRudder = env->GetLongField(obj, env->GetFieldID(cls, "wRudder", "j"));
	result.wAileron = env->GetLongField(obj, env->GetFieldID(cls, "wAileron", "j"));
	result.wAxisX = env->GetLongField(obj, env->GetFieldID(cls, "wAxisX", "j"));
	result.wAxisY = env->GetLongField(obj, env->GetFieldID(cls, "wAxisX", "j"));
	result.wAxisZ = env->GetLongField(obj, env->GetFieldID(cls, "wAxisX", "j"));
	result.wAxisXRot = env->GetLongField(obj, env->GetFieldID(cls, "wAxisXRot", "j"));
	result.wAxisYRot = env->GetLongField(obj, env->GetFieldID(cls, "wAxisXRot", "j"));
	result.wAxisZRot = env->GetLongField(obj, env->GetFieldID(cls, "wAxisXRot", "j"));
	result.wSlider = env->GetLongField(obj, env->GetFieldID(cls, "wSlider", "j"));
	result.wDial = env->GetLongField(obj, env->GetFieldID(cls, "wDial", "j"));
	result.wWheel = env->GetLongField(obj, env->GetFieldID(cls, "wWheel", "j"));
	result.wAxisVX = env->GetLongField(obj, env->GetFieldID(cls, "wAxisVX", "j"));
	result.wAxisVY = env->GetLongField(obj, env->GetFieldID(cls, "wAxisVY", "j"));
	result.wAxisVZ = env->GetLongField(obj, env->GetFieldID(cls, "wAxisVZ", "j"));
	result.wAxisVBRX = env->GetLongField(obj, env->GetFieldID(cls, "wAxisVBRX", "j"));
	result.wAxisVBRY = env->GetLongField(obj, env->GetFieldID(cls, "wAxisVBRY", "j"));
	result.wAxisVBRZ = env->GetLongField(obj, env->GetFieldID(cls, "wAxisVBRZ", "j"));
	result.lButtons = env->GetLongField(obj, env->GetFieldID(cls, "lButtons", "j"));
	result.bHats = env->GetLongField(obj, env->GetFieldID(cls, "bHats", "j"));
	result.bHatsEx1 = env->GetLongField(obj, env->GetFieldID(cls, "bHatsEx1", "j"));
	result.bHatsEx2 = env->GetLongField(obj, env->GetFieldID(cls, "bHatsEx2", "j"));
	result.bHatsEx3 = env->GetLongField(obj, env->GetFieldID(cls, "bHatsEx3", "j"));

	return result;
}

void CALLBACK changedCB(BOOL removed, BOOL first, PVOID userData) {
	JNIEnv * env = NULL;
	(javaVM)->AttachCurrentThread((void**) &env, NULL);

	jclass cls = env->FindClass("redlaboratory/jvjoyinterface/RemovalCB");
	jmethodID method = env->GetMethodID(cls, "changedCB", "(ZZLjava/lang/Object;)V");

	env->CallVoidMethod(objCb, method, removed, first, *((jobject) userData));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
	javaVM = vm;

	return JNI_VERSION_1_6;
}

JNIEXPORT jshort JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getvJoyVersion(JNIEnv * env, jobject obj) {
	return GetvJoyVersion();
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_vJoyEnabled(JNIEnv * env, jobject obj) {
	return vJoyEnabled();
}

JNIEXPORT jstring JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getvJoyProductString(JNIEnv * env, jobject obj) {
	return env->NewStringUTF((char*) GetvJoyProductString());
}

JNIEXPORT jstring JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getvJoyManufacturerString(JNIEnv * env, jobject obj) {
	return env->NewStringUTF((char*) GetvJoyManufacturerString());
}

JNIEXPORT jstring JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getvJoySerialNumberString(JNIEnv * env, jobject obj) {
	return env->NewStringUTF((char*) GetvJoySerialNumberString());
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_driverMatch(JNIEnv * env, jobject obj) {
	WORD DllVer = 0, DrvVer = 0;

	return DriverMatch(&DllVer, &DrvVer);
}

JNIEXPORT void JNICALL Java_redlaboratory_jvjoyinterface_VJoy_registerRemovalCB(JNIEnv * env, jobject obj, jobject cb, jobject data) {
	objCb = env->NewGlobalRef(cb);
	objData = env->NewGlobalRef(data);

	RegisterRemovalCB(changedCB, &objData);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_vJoyFfbCap(JNIEnv * env, jobject obj) {// XXX
	BOOL Supported;
	vJoyFfbCap(&Supported);// There is no description to this method. I don't know what it is.

	return Supported;
}

JNIEXPORT jint JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getvJoyMaxDevices(JNIEnv * env, jobject obj) {
	int n;
	GetvJoyMaxDevices(&n);

	return n;
}

JNIEXPORT jint JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getNumberExistingVJD(JNIEnv * env, jobject obj) {
	int n;
	GetNumberExistingVJD(&n);

	return n;
}

JNIEXPORT jint JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDButtonNumber(JNIEnv * env, jobject obj, jint rID) {
	return GetVJDButtonNumber(rID);
}

JNIEXPORT jint JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDDiscPovNumber(JNIEnv * env, jobject obj, jint rID) {
	return GetVJDDiscPovNumber(rID);
}

JNIEXPORT jint JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDContPovNumber(JNIEnv * env, jobject obj, jint rID) {
	return GetVJDContPovNumber(rID);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDAxisExist(JNIEnv * env, jobject obj, jint rID, jint Axis) {
	return GetVJDAxisExist(rID, Axis);
}

JNIEXPORT jlong JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDAxisMax(JNIEnv * env, jobject obj, jint rID, jint Axis) {
	LONG Max;
	GetVJDAxisMax(rID, Axis, &Max);

	return Max;
}

JNIEXPORT jlong JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDAxisMin(JNIEnv * env, jobject obj, jint rID, jint Axis) {
	LONG Min;
	GetVJDAxisMin(rID, Axis, &Min);

	return Min;
}

JNIEXPORT jobject JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getVJDStatus(JNIEnv * env, jobject obj, jint rID) {
	jclass cls = env->FindClass("redlaboratory/jvjoyinterface/VjdStat");

	VjdStat status = GetVJDStatus(rID);

	switch (status) {
	case VJD_STAT_OWN:
		return env->GetStaticObjectField(cls, env->GetStaticFieldID(cls, "VJD_STAT_OWN", "Lredlaboratory/jvjoyinterface/VjdStat;"));
	case VJD_STAT_FREE:
		return env->GetStaticObjectField(cls, env->GetStaticFieldID(cls, "VJD_STAT_FREE", "Lredlaboratory/jvjoyinterface/VjdStat;"));
	case VJD_STAT_BUSY:
		return env->GetStaticObjectField(cls, env->GetStaticFieldID(cls, "VJD_STAT_BUSY", "Lredlaboratory/jvjoyinterface/VjdStat;"));
	case VJD_STAT_MISS:
		return env->GetStaticObjectField(cls, env->GetStaticFieldID(cls, "VJD_STAT_MISS", "Lredlaboratory/jvjoyinterface/VjdStat;"));
	default:
		return env->GetStaticObjectField(cls, env->GetStaticFieldID(cls, "VJD_STAT_UNKN", "Lredlaboratory/jvjoyinterface/VjdStat;"));
	}
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_isVJDExists(JNIEnv * env, jobject obj, jint rID) {
	return isVJDExists(rID);
}

JNIEXPORT jint JNICALL Java_redlaboratory_jvjoyinterface_VJoy_getOwnerPid(JNIEnv * env, jobject obj, jint rID) {
	return GetOwnerPid(rID);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_acquireVJD(JNIEnv * env, jobject obj, jint rID) {
	return AcquireVJD(rID);
}

JNIEXPORT void JNICALL Java_redlaboratory_jvjoyinterface_VJoy_relinquishVJD(JNIEnv * env, jobject obj, jint rID) {
	RelinquishVJD(rID);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_updateVJD(JNIEnv * env, jobject obj, jint rID, jobject pData) {
	JOYSTICK_POSITION_V2 result = jobjectToJoystickPositionV2(env, obj);

	return UpdateVJD(rID, &result);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_resetVJD(JNIEnv * env, jobject obj, jint rID) {
	return ResetVJD(rID);
}

JNIEXPORT void JNICALL Java_redlaboratory_jvjoyinterface_VJoy_resetAll(JNIEnv * env, jobject obj) {
	ResetAll();
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_resetButtons(JNIEnv * env, jobject obj, jint rID) {
	return ResetButtons(rID);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_resetPovs(JNIEnv * env, jobject obj, jint rID) {
	return ResetPovs(rID);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_setAxis(JNIEnv * env, jobject obj, jlong Value, jint rID, jint Axis) {
	return SetAxis(Value, rID, Axis);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_setBtn(JNIEnv * env, jobject obj, jboolean Value, jint rID, jint nBtn) {
	return SetBtn(Value, rID, nBtn);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_setDiscPov(JNIEnv * env, jobject obj, jint Value, jint rID, jint nPov) {
	return SetDiscPov(Value, rID, nPov);
}

JNIEXPORT jboolean JNICALL Java_redlaboratory_jvjoyinterface_VJoy_setContPov(JNIEnv * env, jobject obj, jlong Value, jint rID, jint nPov) {
	return SetContPov(Value, rID, nPov);
}
