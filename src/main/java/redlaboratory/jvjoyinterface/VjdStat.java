package redlaboratory.jvjoyinterface;

public enum VjdStat {
	/** The vJoy Device is owned by this application. */
	VJD_STAT_OWN,
	/** The vJoy Device is NOT owned by any application (including this one). */
	VJD_STAT_FREE,
	/** The vJoy Device is owned by another application. It cannot be acquired by this application. */
	VJD_STAT_BUSY,
	/** The vJoy Device is missing. It either does not exist or the driver is down. */
	VJD_STAT_MISS,
	/** Unknown */
	VJD_STAT_UNKN;
}
