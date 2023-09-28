#pragma once
#include "openvr.h"
#include "vrtypes.h"
#include "vrannotation.h"
#include "vrtrackedcameratypes.h"
// ivrrendermodels.h
namespace vr
{
namespace IVRRenderModels_002
{

static const char * const k_pch_Controller_Component_GDC2015 = "gdc2015";   // Canonical coordinate system of the gdc 2015 wired controller, provided for backwards compatibility
static const char * const k_pch_Controller_Component_Base = "base";         // For controllers with an unambiguous 'base'.
static const char * const k_pch_Controller_Component_Tip = "tip";           // For controllers with an unambiguous 'tip' (used for 'laser-pointing')
static const char * const k_pch_Controller_Component_HandGrip = "handgrip"; // Neutral, ambidextrous hand-pose when holding controller. On plane between neutrally posed index finger and thumb

#if defined(__linux__) || defined(__APPLE__) 
// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
// The 64-bit version of gcc has the alignment requirement for these types set to
// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
#pragma pack( push, 4 )
#else
#pragma pack( push, 8 )
#endif

typedef uint32_t VRComponentProperties;

enum EVRComponentProperty
{
	VRComponentProperty_IsStatic = (1 << 0),
	VRComponentProperty_IsVisible = (1 << 1),
	VRComponentProperty_IsTouched = (1 << 2),
	VRComponentProperty_IsPressed = (1 << 3),
};

/** Describes state information about a render-model component, including transforms and other dynamic properties
*/
struct RenderModel_ComponentState_t
{
	HmdMatrix34_t mTrackingToComponentRenderModel;  // Transform required when drawing the component render model
	HmdMatrix34_t mTrackingToComponentLocal;        // Transform available for attaching to a local component coordinate system (-Z out from surface )
	VRComponentProperties uProperties;
};

/** a single vertex in a render model */
struct RenderModel_Vertex_t
{
	HmdVector3_t vPosition;		// position in meters in device space
	HmdVector3_t vNormal;
	float rfTextureCoord[2];
};

/** A texture map for use on a render model */
struct RenderModel_TextureMap_t
{
	uint16_t unWidth, unHeight; // width and height of the texture map in pixels
	const uint8_t *rubTextureMapData;	// Map texture data. All textures are RGBA with 8 bits per channel per pixel. Data size is width * height * 4ub
};

/**  Session unique texture identifier. Rendermodels which share the same texture will have the same id.
IDs <0 denote the texture is not present
*/

typedef int32_t TextureID_t;

struct RenderModel_t
{
	const RenderModel_Vertex_t *rVertexData;	// Vertex data for the mesh
	uint32_t unVertexCount;						// Number of vertices in the vertex data
	const uint16_t *rIndexData;					// Indices into the vertex data for each triangle
	uint32_t unTriangleCount;					// Number of triangles in the mesh. Index count is 3 * TriangleCount
	TextureID_t diffuseTextureId;				// Session unique texture identifier. Rendermodels which share the same texture will have the same id. <0 == texture not present
};

#pragma pack( pop )

class IVRRenderModels
{
public:


	/** Loads and returns a render model for use in the application. pchRenderModelName should be a render model name
	* from the Prop_RenderModelName_String property or an absolute path name to a render model on disk. 
	*
	* The resulting render model is valid until VR_Shutdown() is called or until FreeRenderModel() is called. When the 
	* application is finished with the render model it should call FreeRenderModel() to free the memory associated
	* with the model.
	*
	* The method returns false if the model could not be loaded.
	*
	* The API expects that this function will be called at startup or when tracked devices are connected and disconnected.
	* If it is called every frame it will hurt performance.
	*/
	virtual bool LoadRenderModel( const char *pchRenderModelName, RenderModel_t **ppRenderModel ) = 0;

	/** Frees a previously returned render model
	*   It is safe to call this on a null ptr.
	**/
	virtual void FreeRenderModel( RenderModel_t *pRenderModel ) = 0;

	/** Loads and returns a texture for use in the application.
	*/
	virtual bool LoadTexture( TextureID_t textureId, RenderModel_TextureMap_t **ppTexture ) = 0;

	/** Frees a previously returned texture
	*   It is safe to call this on a null ptr.
	*/
	virtual void FreeTexture( RenderModel_TextureMap_t *pTexture ) = 0;

	/** Use this to get the names of available render models.  Index does not correlate to a tracked device index, but
	* is only used for iterating over all available render models.  If the index is out of range, this function will return 0.
	* Otherwise, it will return the size of the buffer required for the name. */
	virtual uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) = 0;

	/** Returns the number of available render models. */
	virtual uint32_t GetRenderModelCount() = 0;



	/** Returns the number of components of the specified render model.
	*  Components are useful when client application wish to draw, label, or otherwise interact with components of tracked objects.
	*  Examples controller components:
	*   renderable things such as triggers, buttons
	*   non-renderable things which include coordinate systems such as 'tip', 'base', a neutral controller agnostic hand-pose
	*   If all controller components are enumerated and rendered, it will be equivalent to drawing the traditional render model
	*   Returns 0 if components not supported, >0 otherwise
	*/
	virtual uint32_t GetComponentCount( const char *pchRenderModelName ) = 0;

	/** Use this to get the names of available components.  Index does not correlate to a tracked device index, but
	* is only used for iterating over all available components.  If the index is out of range, this function will return 0.
	* Otherwise, it will return the size of the buffer required for the name. */
	virtual uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) = 0;

	/** Get the button mask for all buttons associated with this component
	*   If no buttons (or axes) are associated with this component, return 0
	*   Note: multiple components may be associated with the same button. Ex: two grip buttons on a single controller.
	*   Note: A single component may be associated with multiple buttons. Ex: A trackpad which also provides "D-pad" functionality */
	virtual uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName ) = 0;

	/** Use this to get the render model name for the specified rendermode/component combination, to be passed to LoadRenderModel.
	* If the component name is out of range, this function will return 0.
	* Otherwise, it will return the size of the buffer required for the name. */
	virtual uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen ) = 0;

	/** Use this to query information about the component, as a function of the controller state.
	*
	* For dynamic controller components (ex: trigger) values will reflect component motions
	* For static components this will return a consistent value independent of the VRControllerState_t
	*
	* If the pchRenderModelName or pchComponentName is invalid, this will return false (and transforms will be set to identity).
	* Otherwise, return true
	* Note: For dynamic objects, visibility may be dynamic. (I.e., true/false will be returned based on controller state ) */
	virtual bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const VRControllerState_t *pControllerState, RenderModel_ComponentState_t *pComponentState ) = 0;

};

static const char * const IVRRenderModels_Version = "IVRRenderModels_002";

}


} // Close custom namespace
