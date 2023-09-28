#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "vrtrackedcameratypes.h"
// ivrapplications.h
namespace vr
{
namespace IVRApplications_002
{

	/** Used for all errors reported by the IVRApplications interface */
	enum EVRApplicationError
	{
		VRApplicationError_None = 0,

		VRApplicationError_AppKeyAlreadyExists = 100,	// Only one application can use any given key
		VRApplicationError_NoManifest = 101,			// the running application does not have a manifest
		VRApplicationError_NoApplication = 102,			// No application is running
		VRApplicationError_InvalidIndex = 103,
		VRApplicationError_UnknownApplication = 104,	// the application could not be found
		VRApplicationError_IPCFailed = 105,				// An IPC failure caused the request to fail
		VRApplicationError_ApplicationAlreadyRunning = 106, 
		VRApplicationError_InvalidManifest = 107,
		VRApplicationError_InvalidApplication = 108,
		VRApplicationError_LaunchFailed = 109,			// the process didn't start
		VRApplicationError_ApplicationAlreadyStarting = 110, // the system was already starting the same application
		VRApplicationError_LaunchInProgress = 111,		// The system was already starting a different application
		VRApplicationError_OldApplicationQuitting = 112, 
		VRApplicationError_TransitionAborted = 113,

		VRApplicationError_BufferTooSmall = 200,		// The provided buffer was too small to fit the requested data
		VRApplicationError_PropertyNotSet = 201,		// The requested property was not set
		VRApplicationError_UnknownProperty = 202,
	};

	/** The maximum length of an application key */
	static const uint32_t k_unMaxApplicationKeyLength = 128;

	/** these are the properties available on applications. */
	enum EVRApplicationProperty
	{
		VRApplicationProperty_Name_String				= 0,

		VRApplicationProperty_LaunchType_String			= 11,
		VRApplicationProperty_WorkingDirectory_String	= 12,
		VRApplicationProperty_BinaryPath_String			= 13,
		VRApplicationProperty_Arguments_String			= 14,
		VRApplicationProperty_URL_String				= 15,

		VRApplicationProperty_Description_String		= 50,
		VRApplicationProperty_NewsURL_String			= 51,
		VRApplicationProperty_ImagePath_String			= 52,
		VRApplicationProperty_Source_String				= 53,

		VRApplicationProperty_IsDashboardOverlay_Bool	= 60,
	};

	/** These are states the scene application startup process will go through. */
	enum EVRApplicationTransitionState
	{
		VRApplicationTransition_None = 0,

		VRApplicationTransition_OldAppQuitSent = 10,
		VRApplicationTransition_WaitingForExternalLaunch = 11,
		
		VRApplicationTransition_NewAppLaunched = 20,
	};


	class IVRApplications
	{
	public:

		// ---------------  Application management  --------------- //

		/** Adds an application manifest to the list to load when building the list of installed applications. 
		* Temporary manifests are not automatically loaded */
		virtual EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary = false ) = 0;

		/** Removes an application manifest from the list to load when building the list of installed applications. */
		virtual EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath ) = 0;

		/** Returns true if an application is installed */
		virtual bool IsApplicationInstalled( const char *pchAppKey ) = 0;

		/** Returns the number of applications available in the list */
		virtual uint32_t GetApplicationCount() = 0;

		/** Returns the key of the specified application. The index is at least 0 and is less than the return 
		* value of GetApplicationCount(). The buffer should be at least k_unMaxApplicationKeyLength in order to 
		* fit the key. */
		virtual EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Returns the key of the application for the specified Process Id. The buffer should be at least 
		* k_unMaxApplicationKeyLength in order to fit the key. */
		virtual EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Launches the application. The existing scene application will exit and then the new application will start.
		* This call is not valid for dashboard overlay applications. */
		virtual EVRApplicationError LaunchApplication( const char *pchAppKey ) = 0;

		/** Launches the dashboard overlay application if it is not already running. This call is only valid for 
		* dashboard overlay applications. */
		virtual EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey ) = 0;

		/** Identifies a running application. OpenVR can't always tell which process started in response
		* to a URL. This function allows a URL handler (or the process itself) to identify the app key 
		* for the now running application. Passing a process ID of 0 identifies the calling process. 
		* The application must be one that's known to the system via a call to AddApplicationManifest. */
		virtual EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey ) = 0;

		/** Returns the process ID for an application. Return 0 if the application was not found or is not running. */
		virtual uint32_t GetApplicationProcessId( const char *pchAppKey ) = 0;

		/** Returns a string for an applications error */
		virtual const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error ) = 0;

		// ---------------  Application properties  --------------- //

		/** Returns a value for an application property. The required buffer size to fit this value will be returned. */
		virtual uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError = nullptr ) = 0;

		/** Returns a value for an application property. The required buffer size to fit this value will be returned. */
		virtual bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError = nullptr ) = 0;

		/** Sets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
		virtual EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch ) = 0;

		/** Gets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
		virtual bool GetApplicationAutoLaunch( const char *pchAppKey ) = 0;

		// ---------------  Transition methods --------------- //

		/** Returns the app key for the application that is starting up */
		virtual EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) = 0;

		/** Returns the application transition state */
		virtual EVRApplicationTransitionState GetTransitionState() = 0;

		/** Returns errors that would prevent the specified application from launching immediately. Calling this function will
		* cause the current scene application to quit, so only call it when you are actually about to launch something else.
		* What the caller should do about these failures depends on the failure:
		*   VRApplicationError_OldApplicationQuitting - An existing application has been told to quit. Wait for a VREvent_ProcessQuit
		*                                               and try again.
		*   VRApplicationError_ApplicationAlreadyStarting - This application is already starting. This is a permanent failure.
		*   VRApplicationError_LaunchInProgress	      - A different application is already starting. This is a permanent failure.
		*   VRApplicationError_None                   - Go ahead and launch. Everything is clear.
		*/
		virtual EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) = 0;

		/** Returns a string for an application transition state */
		virtual const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) = 0;

		/** Returns true if the outgoing scene app has requested a save prompt before exiting */
		virtual bool IsQuitUserPromptRequested() = 0;

	};

	static const char * const IVRApplications_Version = "IVRApplications_002";

	/** Returns the current IVRApplications pointer or NULL the interface could not be found. */
	VR_INTERFACE IVRApplications *VR_CALLTYPE VRApplications();

} // namespace vr

} // Close custom namespace
