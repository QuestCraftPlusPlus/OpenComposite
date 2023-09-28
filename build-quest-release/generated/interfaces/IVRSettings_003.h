#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrsettings.h

#include <string>

namespace vr
{
namespace IVRSettings_003
{
	enum EVRSettingsError
	{
		VRSettingsError_None = 0,
		VRSettingsError_IPCFailed = 1,
		VRSettingsError_WriteFailed = 2,
		VRSettingsError_ReadFailed = 3,
		VRSettingsError_JsonParseFailed = 4,
		VRSettingsError_UnsetSettingHasNoDefault = 5, // This will be returned if the setting does not appear in the appropriate default file and has not been set
	};

	// The maximum length of a settings key
	static const uint32_t k_unMaxSettingsKeyLength = 128;

	class IVRSettings
	{
	public:
		virtual const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) = 0;

		virtual void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError = nullptr ) = 0;
		virtual void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError = nullptr ) = 0;

		// Users of the system need to provide a proper default in default.vrsettings in the resources/settings/ directory
		// of either the runtime or the driver_xxx directory. Otherwise the default will be false, 0, 0.0 or ""
		virtual bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr ) = 0;
		virtual int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr ) = 0;
		virtual float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr ) = 0;
		virtual void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError = nullptr ) = 0;

		virtual void RemoveSection( const char *pchSection, EVRSettingsError *peError = nullptr ) = 0;
		virtual void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr ) = 0;
	};

	//-----------------------------------------------------------------------------
	static const char * const IVRSettings_Version = "IVRSettings_003";

	class CVRSettingHelper
	{
		IVRSettings *m_pSettings;
	public:
		CVRSettingHelper( IVRSettings *pSettings )
		{
			m_pSettings = pSettings;
		}

		const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError )
		{
			return m_pSettings->GetSettingsErrorNameFromEnum( eError );
		}

		void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->SetBool( pchSection, pchSettingsKey, bValue, peError );
		}

		void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->SetInt32( pchSection, pchSettingsKey, nValue, peError );
		}
		void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->SetFloat( pchSection, pchSettingsKey, flValue, peError );
		}
		void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->SetString( pchSection, pchSettingsKey, pchValue, peError );
		}
		void SetString( const std::string & sSection, const std::string &  sSettingsKey, const std::string & sValue, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->SetString( sSection.c_str(), sSettingsKey.c_str(), sValue.c_str(), peError );
		}

		bool GetBool( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr )
		{
			return m_pSettings->GetBool( pchSection, pchSettingsKey, peError );
		}
		int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr )
		{
			return m_pSettings->GetInt32( pchSection, pchSettingsKey, peError );
		}
		float GetFloat( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr )
		{
			return m_pSettings->GetFloat( pchSection, pchSettingsKey, peError );
		}
		void GetString( const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->GetString( pchSection, pchSettingsKey, pchValue, unValueLen, peError );
		}
		std::string GetString( const std::string & sSection, const std::string & sSettingsKey, EVRSettingsError *peError = nullptr )
		{
			char buf[4096];
			EVRSettingsError eError;
			m_pSettings->GetString( sSection.c_str(), sSettingsKey.c_str(), buf, sizeof( buf ), &eError );
			if ( peError )
				*peError = eError;
			if ( eError == VRSettingsError_None )
				return buf;
			else
				return "";
		}

		void RemoveSection( const char *pchSection, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->RemoveSection( pchSection, peError );
		}
		void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr )
		{
			m_pSettings->RemoveKeyInSection( pchSection, pchSettingsKey, peError );
		}
	};


	//-----------------------------------------------------------------------------
	// steamvr keys
	static const char * const k_pch_SteamVR_Section = "steamvr";
	static const char * const k_pch_SteamVR_RequireHmd_String = "requireHmd";
	static const char * const k_pch_SteamVR_ForcedDriverKey_String = "forcedDriver";
	static const char * const k_pch_SteamVR_ForcedHmdKey_String = "forcedHmd";
	static const char * const k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
	static const char * const k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
	static const char * const k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
	static const char * const k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
	static const char * const k_pch_SteamVR_SendSystemButtonToAllApps_Bool= "sendSystemButtonToAllApps";
	static const char * const k_pch_SteamVR_LogLevel_Int32 = "loglevel";
	static const char * const k_pch_SteamVR_IPD_Float = "ipd";
	static const char * const k_pch_SteamVR_Background_String = "background";
	static const char * const k_pch_SteamVR_BackgroundUseDomeProjection_Bool = "backgroundUseDomeProjection";
	static const char * const k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
	static const char * const k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
	static const char * const k_pch_SteamVR_GridColor_String = "gridColor";
	static const char * const k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
	static const char * const k_pch_SteamVR_TrackingLossColor_String = "trackingLossColor";
	static const char * const k_pch_SteamVR_ShowStage_Bool = "showStage";
	static const char * const k_pch_SteamVR_DrawTrackingReferences_Bool = "drawTrackingReferences";
	static const char * const k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
	static const char * const k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
	static const char * const k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
	static const char * const k_pch_SteamVR_BaseStationPowerManagement_Int32 = "basestationPowerManagement";
	static const char * const k_pch_SteamVR_ShowBaseStationPowerManagementTip_Int32 = "ShowBaseStationPowerManagementTip";
	static const char * const k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
	static const char * const k_pch_SteamVR_SupersampleScale_Float = "supersampleScale";
	static const char * const k_pch_SteamVR_MaxRecommendedResolution_Int32 = "maxRecommendedResolution";
	static const char * const k_pch_SteamVR_MotionSmoothing_Bool = "motionSmoothing";
	static const char * const k_pch_SteamVR_MotionSmoothingOverride_Int32 = "motionSmoothingOverride";
	static const char * const k_pch_SteamVR_FramesToThrottle_Int32 = "framesToThrottle";
	static const char * const k_pch_SteamVR_AdditionalFramesToPredict_Int32 = "additionalFramesToPredict";
	static const char * const k_pch_SteamVR_DisableAsyncReprojection_Bool = "disableAsync";
	static const char * const k_pch_SteamVR_ForceFadeOnBadTracking_Bool = "forceFadeOnBadTracking";
	static const char * const k_pch_SteamVR_DefaultMirrorView_Int32 = "mirrorView";
	static const char * const k_pch_SteamVR_ShowLegacyMirrorView_Bool = "showLegacyMirrorView";
	static const char * const k_pch_SteamVR_MirrorViewVisibility_Bool = "showMirrorView";
	static const char * const k_pch_SteamVR_MirrorViewDisplayMode_Int32 = "mirrorViewDisplayMode";
	static const char * const k_pch_SteamVR_MirrorViewEye_Int32 = "mirrorViewEye";
	static const char * const k_pch_SteamVR_MirrorViewGeometry_String = "mirrorViewGeometry";
	static const char * const k_pch_SteamVR_MirrorViewGeometryMaximized_String = "mirrorViewGeometryMaximized";
	static const char * const k_pch_SteamVR_PerfGraphVisibility_Bool = "showPerfGraph";
	static const char * const k_pch_SteamVR_StartMonitorFromAppLaunch = "startMonitorFromAppLaunch";
	static const char * const k_pch_SteamVR_StartCompositorFromAppLaunch_Bool = "startCompositorFromAppLaunch";
	static const char * const k_pch_SteamVR_StartDashboardFromAppLaunch_Bool = "startDashboardFromAppLaunch";
	static const char * const k_pch_SteamVR_StartOverlayAppsFromDashboard_Bool = "startOverlayAppsFromDashboard";
	static const char * const k_pch_SteamVR_EnableHomeApp = "enableHomeApp";
	static const char * const k_pch_SteamVR_CycleBackgroundImageTimeSec_Int32 = "CycleBackgroundImageTimeSec";
	static const char * const k_pch_SteamVR_RetailDemo_Bool = "retailDemo";
	static const char * const k_pch_SteamVR_IpdOffset_Float = "ipdOffset";
	static const char * const k_pch_SteamVR_AllowSupersampleFiltering_Bool = "allowSupersampleFiltering";
	static const char * const k_pch_SteamVR_SupersampleManualOverride_Bool = "supersampleManualOverride";
	static const char * const k_pch_SteamVR_EnableLinuxVulkanAsync_Bool = "enableLinuxVulkanAsync";
	static const char * const k_pch_SteamVR_AllowDisplayLockedMode_Bool = "allowDisplayLockedMode";
	static const char * const k_pch_SteamVR_HaveStartedTutorialForNativeChaperoneDriver_Bool = "haveStartedTutorialForNativeChaperoneDriver";
	static const char * const k_pch_SteamVR_ForceWindows32bitVRMonitor = "forceWindows32BitVRMonitor";
	static const char * const k_pch_SteamVR_DebugInputBinding = "debugInputBinding";
	static const char * const k_pch_SteamVR_DoNotFadeToGrid = "doNotFadeToGrid";
	static const char * const k_pch_SteamVR_RenderCameraMode = "renderCameraMode";
	static const char * const k_pch_SteamVR_EnableSharedResourceJournaling = "enableSharedResourceJournaling";
	static const char * const k_pch_SteamVR_EnableSafeMode = "enableSafeMode";
	static const char * const k_pch_SteamVR_PreferredRefreshRate = "preferredRefreshRate";
	static const char * const k_pch_SteamVR_LastVersionNotice = "lastVersionNotice";
	static const char * const k_pch_SteamVR_LastVersionNoticeDate = "lastVersionNoticeDate";
	static const char * const k_pch_SteamVR_HmdDisplayColorGainR_Float = "hmdDisplayColorGainR";
	static const char * const k_pch_SteamVR_HmdDisplayColorGainG_Float = "hmdDisplayColorGainG";
	static const char * const k_pch_SteamVR_HmdDisplayColorGainB_Float = "hmdDisplayColorGainB";
	static const char * const k_pch_SteamVR_CustomIconStyle_String = "customIconStyle";
	static const char * const k_pch_SteamVR_CustomOffIconStyle_String = "customOffIconStyle";
	static const char * const k_pch_SteamVR_CustomIconForceUpdate_String = "customIconForceUpdate";
	static const char * const k_pch_SteamVR_AllowGlobalActionSetPriority = "globalActionSetPriority";
	static const char * const k_pch_SteamVR_OverlayRenderQuality = "overlayRenderQuality_2";
	static const char * const k_pch_SteamVR_BlockOculusSDKOnOpenVRLaunchOption_Bool = "blockOculusSDKOnOpenVRLaunchOption";
	static const char * const k_pch_SteamVR_BlockOculusSDKOnAllLaunches_Bool = "blockOculusSDKOnAllLaunches";
	static const char * const k_pch_SteamVR_HDCPLegacyCompatibility_Bool = "hdcp14legacyCompatibility";
	static const char * const k_pch_SteamVR_UsePrism_Bool = "usePrism";

	//-----------------------------------------------------------------------------
	// direct mode keys
	static const char * const k_pch_DirectMode_Section = "direct_mode";
	static const char * const k_pch_DirectMode_Enable_Bool = "enable";
	static const char * const k_pch_DirectMode_Count_Int32 = "count";
	static const char * const k_pch_DirectMode_EdidVid_Int32 = "edidVid";
	static const char * const k_pch_DirectMode_EdidPid_Int32 = "edidPid";

	//-----------------------------------------------------------------------------
	// lighthouse keys
	static const char * const k_pch_Lighthouse_Section = "driver_lighthouse";
	static const char * const k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
	static const char * const k_pch_Lighthouse_DisableIMUExceptHMD_Bool = "disableimuexcepthmd";
	static const char * const k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
	static const char * const k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";
	static const char * const k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
	static const char * const k_pch_Lighthouse_DBHistory_Bool = "dbhistory";
	static const char * const k_pch_Lighthouse_EnableBluetooth_Bool = "enableBluetooth";
	static const char * const k_pch_Lighthouse_PowerManagedBaseStations_String = "PowerManagedBaseStations";
	static const char * const k_pch_Lighthouse_PowerManagedBaseStations2_String = "PowerManagedBaseStations2";
	static const char * const k_pch_Lighthouse_InactivityTimeoutForBaseStations_Int32 = "InactivityTimeoutForBaseStations";
	static const char * const k_pch_Lighthouse_EnableImuFallback_Bool = "enableImuFallback";

	//-----------------------------------------------------------------------------
	// null keys
	static const char * const k_pch_Null_Section = "driver_null";
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
	// Windows MR keys
	static const char * const k_pch_WindowsMR_Section = "driver_holographic";

	//-----------------------------------------------------------------------------
	// user interface keys
	static const char * const k_pch_UserInterface_Section = "userinterface";
	static const char * const k_pch_UserInterface_StatusAlwaysOnTop_Bool = "StatusAlwaysOnTop";
	static const char * const k_pch_UserInterface_MinimizeToTray_Bool = "MinimizeToTray";
	static const char * const k_pch_UserInterface_HidePopupsWhenStatusMinimized_Bool = "HidePopupsWhenStatusMinimized";
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
	static const char * const k_pch_Perf_PerfGraphInHMD_Bool = "perfGraphInHMD";
	static const char * const k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
	static const char * const k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
	static const char * const k_pch_Perf_TestData_Float = "perfTestData";
	static const char * const k_pch_Perf_GPUProfiling_Bool = "GPUProfiling";

	//-----------------------------------------------------------------------------
	// collision bounds keys
	static const char * const k_pch_CollisionBounds_Section = "collisionBounds";
	static const char * const k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
	static const char * const k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
	static const char * const k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
	static const char * const k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
	static const char * const k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
	static const char * const k_pch_CollisionBounds_WallHeight_Float = "CollisionBoundsWallHeight";
	static const char * const k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
	static const char * const k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
	static const char * const k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
	static const char * const k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";
	static const char * const k_pch_CollisionBounds_EnableDriverImport = "enableDriverBoundsImport";

	//-----------------------------------------------------------------------------
	// camera keys
	static const char * const k_pch_Camera_Section = "camera";
	static const char * const k_pch_Camera_EnableCamera_Bool = "enableCamera";
	static const char * const k_pch_Camera_ShowOnController_Bool = "showOnController";
	static const char * const k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
	static const char * const k_pch_Camera_RoomView_Int32 = "roomView";
	static const char * const k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
	static const char * const k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
	static const char * const k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
	static const char * const k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";
	static const char * const k_pch_Camera_BoundsStrength_Int32 = "cameraBoundsStrength";
	static const char * const k_pch_Camera_RoomViewStyle_Int32 = "roomViewStyle";

	//-----------------------------------------------------------------------------
	// audio keys
	static const char * const k_pch_audio_Section = "audio";
	static const char * const k_pch_audio_SetOsDefaultPlaybackDevice_Bool = "setOsDefaultPlaybackDevice";
	static const char * const k_pch_audio_EnablePlaybackDeviceOverride_Bool = "enablePlaybackDeviceOverride";
	static const char * const k_pch_audio_PlaybackDeviceOverride_String = "playbackDeviceOverride";
	static const char * const k_pch_audio_PlaybackDeviceOverrideName_String = "playbackDeviceOverrideName";
	static const char * const k_pch_audio_SetOsDefaultRecordingDevice_Bool = "setOsDefaultRecordingDevice";
	static const char * const k_pch_audio_EnableRecordingDeviceOverride_Bool = "enableRecordingDeviceOverride";
	static const char * const k_pch_audio_RecordingDeviceOverride_String = "recordingDeviceOverride";
	static const char * const k_pch_audio_RecordingDeviceOverrideName_String = "recordingDeviceOverrideName";
	static const char * const k_pch_audio_EnablePlaybackMirror_Bool = "enablePlaybackMirror";
	static const char * const k_pch_audio_PlaybackMirrorDevice_String = "playbackMirrorDevice";
	static const char * const k_pch_audio_PlaybackMirrorDeviceName_String = "playbackMirrorDeviceName";
	static const char * const k_pch_audio_OldPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
	static const char * const k_pch_audio_ActiveMirrorDevice_String = "activePlaybackMirrorDevice";
	static const char * const k_pch_audio_EnablePlaybackMirrorIndependentVolume_Bool = "enablePlaybackMirrorIndependentVolume";
	static const char * const k_pch_audio_LastHmdPlaybackDeviceId_String = "lastHmdPlaybackDeviceId";
	static const char * const k_pch_audio_VIVEHDMIGain = "viveHDMIGain";
	static const char * const k_pch_audio_DualSpeakerAndJackOutput_Bool = "dualSpeakerAndJackOutput";
	static const char * const k_pch_audio_MuteMicMonitor_Bool = "muteMicMonitor";

	//-----------------------------------------------------------------------------
	// power management keys
	static const char * const k_pch_Power_Section = "power";
	static const char * const k_pch_Power_PowerOffOnExit_Bool = "powerOffOnExit";
	static const char * const k_pch_Power_TurnOffScreensTimeout_Float = "turnOffScreensTimeout";
	static const char * const k_pch_Power_TurnOffControllersTimeout_Float = "turnOffControllersTimeout";
	static const char * const k_pch_Power_ReturnToWatchdogTimeout_Float = "returnToWatchdogTimeout";
	static const char * const k_pch_Power_AutoLaunchSteamVROnButtonPress = "autoLaunchSteamVROnButtonPress";
	static const char * const k_pch_Power_PauseCompositorOnStandby_Bool = "pauseCompositorOnStandby";

	//-----------------------------------------------------------------------------
	// dashboard keys
	static const char * const k_pch_Dashboard_Section = "dashboard";
	static const char * const k_pch_Dashboard_EnableDashboard_Bool = "enableDashboard";
	static const char * const k_pch_Dashboard_ArcadeMode_Bool = "arcadeMode";
	static const char * const k_pch_Dashboard_Position = "position";
	static const char * const k_pch_Dashboard_DesktopScale = "desktopScale";
	static const char * const k_pch_Dashboard_DashboardScale = "dashboardScale";
	static const char * const k_pch_Dashboard_UseStandaloneSystemLayer = "standaloneSystemLayer";

	//-----------------------------------------------------------------------------
	// model skin keys
	static const char * const k_pch_modelskin_Section = "modelskins";

	//-----------------------------------------------------------------------------
	// driver keys - These could be checked in any driver_<name> section
	static const char * const k_pch_Driver_Enable_Bool = "enable";
	static const char * const k_pch_Driver_BlockedBySafemode_Bool = "blocked_by_safe_mode";
	static const char * const k_pch_Driver_LoadPriority_Int32 = "loadPriority";

	//-----------------------------------------------------------------------------
	// web interface keys
	static const char* const k_pch_WebInterface_Section = "WebInterface";

	//-----------------------------------------------------------------------------
	// vrwebhelper keys
	static const char* const k_pch_VRWebHelper_Section = "VRWebHelper";
	static const char* const k_pch_VRWebHelper_DebuggerEnabled_Bool = "DebuggerEnabled";
	static const char* const k_pch_VRWebHelper_DebuggerPort_Int32 = "DebuggerPort";

	//-----------------------------------------------------------------------------
	// tracking overrides - keys are device paths, values are the device paths their
	//  tracking/pose information overrides
	static const char* const k_pch_TrackingOverride_Section = "TrackingOverrides";

	//-----------------------------------------------------------------------------
	// per-app keys - the section name for these is the app key itself. Some of these are prefixed by the controller type
	static const char* const k_pch_App_BindingAutosaveURLSuffix_String = "AutosaveURL";
	static const char* const k_pch_App_BindingLegacyAPISuffix_String = "_legacy";
	static const char* const k_pch_App_BindingSteamVRInputAPISuffix_String = "_steamvrinput";
	static const char* const k_pch_App_BindingCurrentURLSuffix_String = "CurrentURL";
	static const char* const k_pch_App_BindingPreviousURLSuffix_String = "PreviousURL";
	static const char* const k_pch_App_NeedToUpdateAutosaveSuffix_Bool = "NeedToUpdateAutosave";
	static const char* const k_pch_App_DominantHand_Int32 = "DominantHand";
	static const char* const k_pch_App_BlockOculusSDK_Bool = "blockOculusSDK";

	//-----------------------------------------------------------------------------
	// configuration for trackers
	static const char * const k_pch_Trackers_Section = "trackers";

	//-----------------------------------------------------------------------------
	// configuration for desktop UI windows
	static const char * const k_pch_DesktopUI_Section = "DesktopUI";

	//-----------------------------------------------------------------------------
	// Last known keys for righting recovery
	static const char * const k_pch_LastKnown_Section = "LastKnown";
	static const char* const k_pch_LastKnown_HMDManufacturer_String = "HMDManufacturer";
	static const char* const k_pch_LastKnown_HMDModel_String = "HMDModel";

	//-----------------------------------------------------------------------------
	// Dismissed warnings
	static const char * const k_pch_DismissedWarnings_Section = "DismissedWarnings";

	//-----------------------------------------------------------------------------
	// Input Settings
	static const char * const k_pch_Input_Section = "input";
	static const char* const k_pch_Input_LeftThumbstickRotation_Float = "leftThumbstickRotation";
	static const char* const k_pch_Input_RightThumbstickRotation_Float = "rightThumbstickRotation";
	static const char* const k_pch_Input_ThumbstickDeadzone_Float = "thumbstickDeadzone";

	//-----------------------------------------------------------------------------
	// Log of GPU performance
	static const char * const k_pch_GpuSpeed_Section = "GpuSpeed";

} // namespace vr

} // Close custom namespace
