#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "vrtrackedcameratypes.h"
// ivrcontrolpanel.h
namespace vr
{
namespace IVRControlPanel_001
{

class IVRControlPanel
{
public:

	// ------------------------------------
	// Driver enumeration methods
	// ------------------------------------

	/** the number of active drivers */
	virtual uint32_t GetDriverCount() = 0;

	/** The ID of the specified driver as a UTF-8 string. Returns the length of the ID in bytes. If 
	* the buffer is not large enough to fit the ID an empty string will be returned. In general, 128 bytes
	* will be enough to fit any ID. */
	virtual uint32_t GetDriverId( uint32_t unDriverIndex, char *pchBuffer, uint32_t unBufferLen ) = 0;

	// ------------------------------------
	// Display Enumeration Methods
	// ------------------------------------

	/** the number of active displays on the specified driver */
	virtual uint32_t GetDriverDisplayCount( const char *pchDriverId ) = 0;

	/** The ID of the specified display in the specified driver as a UTF-8 string. Returns the 
	* length of the ID in bytes. If the buffer is not large enough to fit the ID an empty
	* string will be returned. In general, 128 bytes will be enough to fit any ID. */
	virtual uint32_t GetDriverDisplayId( const char *pchDriverId, uint32_t unDisplayIndex, char *pchBuffer, uint32_t unBufferLen ) = 0;

	// ------------------------------------
	// Display Detail Methods
	// ------------------------------------

	/** The model name of the specified driver in the specified driver as a UTF-8 string. Returns the 
	* length of the model name in bytes. If the buffer is not large enough to fit the model name an empty
	* string will be returned. In general, 128 bytes will be enough to fit any model name. Returns 0 if
	* the display or driver was not found. */
	virtual uint32_t GetDriverDisplayModelNumber( const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen ) = 0;

	/** The serial number of the specified driver in the specified driver as a UTF-8 string. Returns the 
	* length of the serial number in bytes. If the buffer is not large enough to fit the serial number an empty
	* string will be returned. In general, 128 bytes will be enough to fit any model name. Returns 0 if
	* the display or driver was not found. */
	virtual uint32_t GetDriverDisplaySerialNumber( const char *pchDriverId, const char *pchDisplayId, char *pchBuffer, uint32_t unBufferLen ) = 0;

	/** Returns the IVRSystem interface for the current display that matches the specified version number. 
	* This is usually unnecessary and the return value of VR_Init can be used without calling this method. */
	VR_IGNOREATTR()
	virtual class IVRSystem *GetCurrentDisplayInterface( const char *pchHmdInterfaceVersion ) = 0;

	// ------------------------------------
	// Shared Resource Methods
	// ------------------------------------

	/** Loads the specified resource into the provided buffer if large enough.
	* Returns the size in bytes of the buffer required to hold the specified resource. */
	virtual uint32_t LoadSharedResource( const char *pchResourceName, char *pchBuffer, uint32_t unBufferLen ) = 0;

	// ------------------------------------
	// IPD Methods
	// ------------------------------------

	/** Gets the current IPD (Interpupillary Distance) in meters. */
	virtual float GetIPD() = 0;

	/** Sets the current IPD (Interpupillary Distance) in meters. */
	virtual void SetIPD( float fIPD ) = 0;

	// ------------------------------------
	// Compositor Methods
	// ------------------------------------

	/** Returns the IVRCompositor interface that matches the specified interface version.  This will only
	* return the compositor interface if it has already been initialized by the current process. */
	virtual class IVRCompositor *GetCurrentCompositorInterface( const char *pchInterfaceVersion ) = 0;

	// ------------------------------------
	// Process control Methods
	// ------------------------------------

	/** Tells the specified OpenVR process to quit. If the process ID is 0, all processes will be told to quit,
	* ending with the process submitting the request. Returns false if the request could not be sent. */
	virtual bool QuitProcess( uint32_t pidProcessToQuit ) = 0;

	/** Starts a process and returns the PID or 0 if the process failed to start. */
	virtual uint32_t StartVRProcess( const char *pchExecutable, const char **pchArguments, uint32_t unArgumentCount, const char *pchWorkingDirectory) = 0;

	/** Sets the master process for OpenVR. When the master process exits VRServer will send quit messages to every other process
	* to start the shutdown process */
	virtual void SetMasterProcessToThis() = 0;
	
	/** Tells the application system to start all autolaunched dashboard overlays */
	virtual void StartAutolaunchOverlays() = 0;

	/** Tells the specified OpenVR process to quit. The process ID must be valid. Quitting all processes by passing 0 is not supported.  
	* Returns false if the request could not be sent. */
	virtual bool ForceQuitProcess( uint32_t pidProcessToQuit ) = 0;

	/** Aborts a process quit/application transition at the user's request. */
	virtual void AbortTransition() = 0;

};

static const char * const IVRControlPanel_Version = "IVRControlPanel_001";

}
} // Close custom namespace
