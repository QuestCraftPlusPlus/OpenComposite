#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrsettings.h
namespace vr
{
namespace IVRSettings_001
{
	enum EVRSettingsError
	{
		VRSettingsError_None = 0,
		VRSettingsError_IPCFailed = 1,
		VRSettingsError_WriteFailed = 2,
		VRSettingsError_ReadFailed = 3,
	};

	// The maximum length of a settings key
	static const uint32_t k_unMaxSettingsKeyLength = 128;

	class IVRSettings
	{
	public:
		virtual const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) = 0;

		// Returns true if file sync occurred (force or settings dirty)
		virtual bool Sync( bool bForce = false, EVRSettingsError *peError = nullptr ) = 0;

		virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, bool bDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, float flDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, const char *pchDefaultValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError = nullptr ) = 0;
		
		virtual void RemoveSection( const char *pchSection, EVRSettingsError *peError = nullptr ) = 0;
		virtual void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr ) = 0;
	};

	//-----------------------------------------------------------------------------
	static const char * const IVRSettings_Version = "IVRSettings_001";

	//-----------------------------------------------------------------------------
	// steamvr keys

	static const char * const k_pch_SteamVR_Section = "steamvr";
	static const char * const k_pch_SteamVR_RequireHmd_String = "requireHmd";
	static const char * const k_pch_SteamVR_ForcedDriverKey_String = "forcedDriver";
	static const char * const k_pch_SteamVR_ForcedHmdKey_String = "forcedHmd";
	static const char * const k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
	static const char * const k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
	static const char * const k_pch_SteamVR_EnableDistortion_Bool = "enableDistortion";
	static const char * const k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
	static const char * const k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
	static const char * const k_pch_SteamVR_SendSystemButtonToAllApps_Bool= "sendSystemButtonToAllApps";
	static const char * const k_pch_SteamVR_LogLevel_Int32 = "loglevel";
	static const char * const k_pch_SteamVR_IPD_Float = "ipd";
	static const char * const k_pch_SteamVR_Background_String = "background";
	static const char * const k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
	static const char * const k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
	static const char * const k_pch_SteamVR_Environment_String = "environment";
	static const char * const k_pch_SteamVR_GridColor_String = "gridColor";
	static const char * const k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
	static const char * const k_pch_SteamVR_ShowStage_Bool = "showStage";
	static const char * const k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
	static const char * const k_pch_SteamVR_PowerOffOnExit_Bool = "powerOffOnExit";
	static const char * const k_pch_SteamVR_StandbyAppRunningTimeout_Float = "standbyAppRunningTimeout";
	static const char * const k_pch_SteamVR_StandbyNoAppTimeout_Float = "standbyNoAppTimeout";
	static const char * const k_pch_SteamVR_DirectMode_Bool = "directMode";
	static const char * const k_pch_SteamVR_DirectModeEdidVid_Int32 = "directModeEdidVid";
	static const char * const k_pch_SteamVR_DirectModeEdidPid_Int32 = "directModeEdidPid";
	static const char * const k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
	static const char * const k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
	static const char * const k_pch_SteamVR_BaseStationPowerManagement_Bool = "basestationPowerManagement";
	static const char * const k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
	static const char * const k_pch_SteamVR_RenderTargetMultiplier_Float = "renderTargetMultiplier";
	static const char * const k_pch_SteamVR_AllowReprojection_Bool = "allowReprojection";
	static const char * const k_pch_SteamVR_ForceReprojection_Bool = "forceReprojection";
	static const char * const k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
	static const char * const k_pch_SteamVR_DefaultMirrorView_Int32 = "defaultMirrorView";
	static const char * const k_pch_SteamVR_ShowMirrorView_Bool = "showMirrorView";
	static const char * const k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
	static const char * const k_pch_SteamVR_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
	static const char * const k_pch_SteamVR_UseGenericGraphcisDevice_Bool = "useGenericGraphicsDevice";


	//-----------------------------------------------------------------------------
	// lighthouse keys

	static const char * const k_pch_Lighthouse_Section = "driver_lighthouse";
	static const char * const k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
	static const char * const k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
	static const char * const k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";

	static const char * const k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
	static const char * const k_pch_Lighthouse_LighthouseName_String = "lighthousename";
	static const char * const k_pch_Lighthouse_MaxIncidenceAngleDegrees_Float = "maxincidenceangledegrees";
	static const char * const k_pch_Lighthouse_UseLighthouseDirect_Bool = "uselighthousedirect";
	static const char * const k_pch_Lighthouse_DBHistory_Bool = "dbhistory";

	//-----------------------------------------------------------------------------
	// null keys

	static const char * const k_pch_Null_Section = "driver_null";
	static const char * const k_pch_Null_EnableNullDriver_Bool = "enable";
	static const char * const k_pch_Null_SerialNumber_String = "serialNumber";
	static const char * const k_pch_Null_ModelNumber_String = "modelNumber";
	static const char * const k_pch_Null_WindowX_Int32 = "windowX";
	static const char * const k_pch_Null_WindowY_Int32 = "windowY";
	static const char * const k_pch_Null_WindowWidth_Int32 = "windowWidth";
	static const char * const k_pch_Null_WindowHeight_Int32 = "windowHeight";
	static const char * const k_pch_Null_RenderWidth_Int32 = "renderWidth";
	static const char * const k_pch_Null_RenderHeight_Int32 = "renderHeight";
	static const char * const k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
	static const char * const k_pch_Null_DisplayFrequency_Float = "displayFrequency";

	//-----------------------------------------------------------------------------
	// user interface keys
	static const char * const k_pch_UserInterface_Section = "userinterface";
	static const char * const k_pch_UserInterface_StatusAlwaysOnTop_Bool = "StatusAlwaysOnTop";
	static const char * const k_pch_UserInterface_Screenshots_Bool = "screenshots";
	static const char * const k_pch_UserInterface_ScreenshotType_Int = "screenshotType";

	//-----------------------------------------------------------------------------
	// notification keys
	static const char * const k_pch_Notifications_Section = "notifications";
	static const char * const k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";

	//-----------------------------------------------------------------------------
	// keyboard keys
	static const char * const k_pch_Keyboard_Section = "keyboard";
	static const char * const k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
	static const char * const k_pch_Keyboard_ScaleX = "ScaleX";
	static const char * const k_pch_Keyboard_ScaleY = "ScaleY";
	static const char * const k_pch_Keyboard_OffsetLeftX = "OffsetLeftX";
	static const char * const k_pch_Keyboard_OffsetRightX = "OffsetRightX";
	static const char * const k_pch_Keyboard_OffsetY = "OffsetY";
	static const char * const k_pch_Keyboard_Smoothing = "Smoothing";

	//-----------------------------------------------------------------------------
	// perf keys
	static const char * const k_pch_Perf_Section = "perfcheck";
	static const char * const k_pch_Perf_HeuristicActive_Bool = "heuristicActive";
	static const char * const k_pch_Perf_NotifyInHMD_Bool = "warnInHMD";
	static const char * const k_pch_Perf_NotifyOnlyOnce_Bool = "warnOnlyOnce";
	static const char * const k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
	static const char * const k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
	static const char * const k_pch_Perf_TestData_Float = "perfTestData";

	//-----------------------------------------------------------------------------
	// collision bounds keys
	static const char * const k_pch_CollisionBounds_Section = "collisionBounds";
	static const char * const k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
	static const char * const k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
	static const char * const k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
	static const char * const k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
	static const char * const k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
	static const char * const k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
	static const char * const k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
	static const char * const k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
	static const char * const k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";

	//-----------------------------------------------------------------------------
	// camera keys
	static const char * const k_pch_Camera_Section = "camera";
	static const char * const k_pch_Camera_EnableCamera_Bool = "enableCamera";
	static const char * const k_pch_Camera_EnableCameraInDashboard_Bool = "enableCameraInDashboard";
	static const char * const k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
	static const char * const k_pch_Camera_EnableCameraForRoomView_Bool = "enableCameraForRoomView";
	static const char * const k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
	static const char * const k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
	static const char * const k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
	static const char * const k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";

	//-----------------------------------------------------------------------------
	// audio keys
	static const char * const k_pch_audio_Section = "audio";
	static const char * const k_pch_audio_OnPlaybackDevice_String = "onPlaybackDevice";
	static const char * const k_pch_audio_OnRecordDevice_String = "onRecordDevice";
	static const char * const k_pch_audio_OnPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
	static const char * const k_pch_audio_OffPlaybackDevice_String = "offPlaybackDevice";
	static const char * const k_pch_audio_OffRecordDevice_String = "offRecordDevice";
	static const char * const k_pch_audio_VIVEHDMIGain = "viveHDMIGain";

	//-----------------------------------------------------------------------------
	// model skin keys
	static const char * const k_pch_modelskin_Section = "modelskins";

} // namespace vr

} // Close custom namespace
