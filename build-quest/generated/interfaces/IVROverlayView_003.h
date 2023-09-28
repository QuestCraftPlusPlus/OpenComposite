#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivroverlayview.h

namespace vr
{
namespace IVROverlayView_003
{
	struct VROverlayView_t
	{
		VROverlayHandle_t overlayHandle;
		Texture_t texture;
		VRTextureBounds_t textureBounds;
	};

	enum EDeviceType
	{
		DeviceType_Invalid           = -1, // Invalid handle
		DeviceType_DirectX11         = 0, // Handle is an ID3D11Device
		DeviceType_Vulkan            = 1, // Handle is a pointer to a VRVulkanDevice_t structure
	};

	struct VRVulkanDevice_t
	{
		VkInstance_T *m_pInstance;
		VkDevice_T *m_pDevice;
		VkPhysicalDevice_T *m_pPhysicalDevice;
		VkQueue_T *m_pQueue;
		uint32_t m_uQueueFamilyIndex;
	};

	struct VRNativeDevice_t
	{
		void *handle; // See EDeviceType definition above
		EDeviceType eType;
	};

	class IVROverlayView
	{
	public:
		/** Acquire an OverlayView_t from an overlay handle
		*
		* The overlay view can be used to sample the contents directly by a native API. The
		* contents of the OverlayView_t will remain unchanged through the lifetime of the
		* OverlayView_t.
		*
		* The caller acquires read privileges over the OverlayView_t, but should not
		* write to it.
		*
		* AcquireOverlayView() may be called on the same ulOverlayHandle multiple times to
		* refresh the image contents. In this case the caller is strongly encouraged to re-use
		* the same pOverlayView for all re-acquisition calls.
		*
		* If the producer has not yet queued an image, AcquireOverlayView will return success,
		* and the Texture_t will have the expected ETextureType. However, the Texture_t->handle
		* will be nullptr. Once the producer generates the first overlay frame, Texture_t->handle
		* will become a valid handle.
		*/
		virtual EVROverlayError AcquireOverlayView(VROverlayHandle_t ulOverlayHandle, VRNativeDevice_t *pNativeDevice, VROverlayView_t *pOverlayView, uint32_t unOverlayViewSize ) = 0;

		/** Release an acquired OverlayView_t
		*
		* Denotes that pOverlayView will no longer require access to the resources it acquired in
		* all previous calls to AcquireOverlayView().
		*
		* All OverlayView_t*'s provided to AcquireOverlayView() as pOverlayViews must be
		* passed into ReleaseOverlayView() in order for the underlying GPU resources to be freed.
		*/
		virtual EVROverlayError ReleaseOverlayView(VROverlayView_t *pOverlayView) = 0;

		/** Posts an overlay event */
		virtual void PostOverlayEvent(VROverlayHandle_t ulOverlayHandle, const VREvent_t *pvrEvent) = 0;

		/** Determines whether this process is permitted to view an overlay's content. */
		virtual bool IsViewingPermitted( VROverlayHandle_t ulOverlayHandle ) = 0;

	};

	static const char * const IVROverlayView_Version = "IVROverlayView_003";

}

} // Close custom namespace
