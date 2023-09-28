#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "driver_ITrackedDeviceServerDriver_005.h"
#include "vrtrackedcameratypes.h"
// itrackeddevicedriverprovider.h
namespace vr
{

/** This interface is provided by vrserver to allow the driver to notify 
* the system when something changes about a device. These changes must
* not change the serial number or class of the device because those values
* are permanently associated with the device's index. */
class IVRDriverContext
{
public:
	/** Returns the requested interface. If the interface was not available it will return NULL and fill
	* out the error. */
	virtual void *GetGenericInterface( const char *pchInterfaceVersion, EVRInitError *peError = nullptr ) = 0;

	/** Returns the property container handle for this driver */
	virtual DriverHandle_t GetDriverHandle() = 0;
};


/** This interface must be implemented in each driver. It will be loaded in vrserver.exe */
class IServerTrackedDeviceProvider
{
public:
	/** initializes the driver. This will be called before any other methods are called.
	* If Init returns anything other than VRInitError_None the driver DLL will be unloaded.
	*
	* pDriverHost will never be NULL, and will always be a pointer to a IServerDriverHost interface
	*
	* pchUserDriverConfigDir - The absolute path of the directory where the driver should store user
	*	config files.
	* pchDriverInstallDir - The absolute path of the root directory for the driver.
	*/
	virtual EVRInitError Init( IVRDriverContext *pDriverContext ) = 0;

	/** cleans up the driver right before it is unloaded */
	virtual void Cleanup() = 0;

	/** Returns the version of the ITrackedDeviceServerDriver interface used by this driver */
	virtual const char * const *GetInterfaceVersions() = 0;

	/** Allows the driver do to some work in the main loop of the server. */
	virtual void RunFrame() = 0;


	// ------------  Power State Functions ----------------------- //

	/** Returns true if the driver wants to block Standby mode. */
	virtual bool ShouldBlockStandbyMode() = 0;

	/** Called when the system is entering Standby mode. The driver should switch itself into whatever sort of low-power
	* state it has. */
	virtual void EnterStandby() = 0;

	/** Called when the system is leaving Standby mode. The driver should switch itself back to
	full operation. */
	virtual void LeaveStandby() = 0;

};


static const char *IServerTrackedDeviceProvider_Version = "IServerTrackedDeviceProvider_004";




/** This interface must be implemented in each driver. It will be loaded in vrclient.dll */
class IVRWatchdogProvider
{
public:
	/** initializes the driver in watchdog mode. */
	virtual EVRInitError Init( IVRDriverContext *pDriverContext ) = 0;

	/** cleans up the driver right before it is unloaded */
	virtual void Cleanup() = 0;
};

static const char *IVRWatchdogProvider_Version = "IVRWatchdogProvider_001";




/** This is an optional interface drivers may implement. It will be loaded in vrcompositor.exe */
class IVRCompositorPluginProvider
{
public:
	/** initializes the driver when used to load compositor plugins */
	virtual EVRInitError Init( IVRDriverContext *pDriverContext ) = 0;

	/** cleans up the driver right before it is unloaded */
	virtual void Cleanup() = 0;

	/** Returns the versions of interfaces used by this driver */
	virtual const char * const *GetInterfaceVersions() = 0;

	/** Requests a component interface of the driver for specific functionality. The driver should return NULL
	* if the requested interface or version is not supported. */
	virtual void *GetComponent( const char *pchComponentNameAndVersion ) = 0;
};

static const char *IVRCompositorPluginProvider_Version = "IVRCompositorPluginProvider_001";

}