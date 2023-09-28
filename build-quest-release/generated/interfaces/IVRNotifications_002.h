#pragma once
#include "openvr.h"
#include "version.h"
#include "public_vrtypes.h"
#include "vrtypes.h"
#include "vrannotation.h"
// ivrnotifications.h

namespace vr
{
namespace IVRNotifications_002
{

#pragma pack( push, 8 )

// Used for passing graphic data
struct NotificationBitmap_t
{
	NotificationBitmap_t()
		: m_pImageData( nullptr )
		, m_nWidth( 0 )
		, m_nHeight( 0 )
		, m_nBytesPerPixel( 0 )
	{
	}

	void *m_pImageData;
	int32_t m_nWidth;
	int32_t m_nHeight;
	int32_t m_nBytesPerPixel;
};


/** Be aware that the notification type is used as 'priority' to pick the next notification */
enum EVRNotificationType
{
	/** Transient notifications are automatically hidden after a period of time set by the user.
	* They are used for things like information and chat messages that do not require user interaction. */
	EVRNotificationType_Transient = 0,

	/** Persistent notifications are shown to the user until they are hidden by calling RemoveNotification().
	* They are used for things like phone calls and alarms that require user interaction. */
	EVRNotificationType_Persistent = 1,

	/** System notifications are shown no matter what. It is expected, that the ulUserValue is used as ID.
	 * If there is already a system notification in the queue with that ID it is not accepted into the queue
	 * to prevent spamming with system notification */
	EVRNotificationType_Transient_SystemWithUserValue = 2,
};

enum EVRNotificationStyle
{
	/** Creates a notification with minimal external styling. */
	EVRNotificationStyle_None = 0,

	/** Used for notifications about overlay-level status. In Steam this is used for events like downloads completing. */
	EVRNotificationStyle_Application = 100,

	/** Used for notifications about contacts that are unknown or not available. In Steam this is used for friend invitations and offline friends. */
	EVRNotificationStyle_Contact_Disabled = 200,

	/** Used for notifications about contacts that are available but inactive. In Steam this is used for friends that are online but not playing a game. */
	EVRNotificationStyle_Contact_Enabled = 201,

	/** Used for notifications about contacts that are available and active. In Steam this is used for friends that are online and currently running a game. */
	EVRNotificationStyle_Contact_Active = 202,
};

static const uint32_t k_unNotificationTextMaxSize = 256;

typedef uint32_t VRNotificationId;



#pragma pack( pop )

/** Allows notification sources to interact with the VR system
	This current interface is not yet implemented. Do not use yet. */
class IVRNotifications
{
public:
	/** Create a notification and enqueue it to be shown to the user.
	* An overlay handle is required to create a notification, as otherwise it would be impossible for a user to act on it.
	* To create a two-line notification, use a line break ('\n') to split the text into two lines.
	* The pImage argument may be NULL, in which case the specified overlay's icon will be used instead. */
	virtual EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, /* out */ VRNotificationId *pNotificationId ) = 0;

	/** Destroy a notification, hiding it first if it currently shown to the user. */
	virtual EVRNotificationError RemoveNotification( VRNotificationId notificationId ) = 0;

};

static const char * const IVRNotifications_Version = "IVRNotifications_002";

} // namespace vr



} // Close custom namespace
