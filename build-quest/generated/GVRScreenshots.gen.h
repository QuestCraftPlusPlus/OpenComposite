#pragma once
#include "BaseCommon.h"
#include "interfaces/IVRScreenshots_001.h"
#include "Reimpl/BaseScreenshots.h"
class CVRScreenshots_001 : public vr::IVRScreenshots_001::IVRScreenshots, public CVRCommon {
private:
	const std::shared_ptr<BaseScreenshots> base;
public:
	virtual void** _GetStatFuncList() override;
	virtual void Delete() override;
	CVRScreenshots_001();
	// Interface methods:
	vr::IVRScreenshots_001::EVRScreenshotError RequestScreenshot(vr::ScreenshotHandle_t* pOutScreenshotHandle, vr::EVRScreenshotType type, const char* pchPreviewFilename, const char* pchVRFilename) override;
	vr::IVRScreenshots_001::EVRScreenshotError HookScreenshot(const vr::EVRScreenshotType* pSupportedTypes, int numTypes) override;
	vr::EVRScreenshotType GetScreenshotPropertyType(vr::ScreenshotHandle_t screenshotHandle, vr::IVRScreenshots_001::EVRScreenshotError* pError) override;
	uint32_t GetScreenshotPropertyFilename(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, char* pchFilename, uint32_t cchFilename, vr::IVRScreenshots_001::EVRScreenshotError* pError) override;
	vr::IVRScreenshots_001::EVRScreenshotError UpdateScreenshotProgress(vr::ScreenshotHandle_t screenshotHandle, float flProgress) override;
	vr::IVRScreenshots_001::EVRScreenshotError TakeStereoScreenshot(vr::ScreenshotHandle_t* pOutScreenshotHandle, const char* pchPreviewFilename, const char* pchVRFilename) override;
	vr::IVRScreenshots_001::EVRScreenshotError SubmitScreenshot(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char* pchSourcePreviewFilename, const char* pchSourceVRFilename) override;
};
