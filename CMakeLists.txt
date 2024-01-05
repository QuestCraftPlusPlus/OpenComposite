# Set the Windows kit if using MSVC
# CMake will look for the newest kit that isn't newer than this
# Required to find modern D3D12 header
if (MSVC)
	set(CMAKE_SYSTEM_VERSION 10.0.17134.0)
endif ()

cmake_minimum_required(VERSION 3.16)
project(OpenComposite)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options

set(XR_VALIDATION_LAYER_PATH "" CACHE STRING "A path to set XR_API_LAYER_PATH to. Setting this will enable the debug layer")
set(XR_VALIDATION_FILE_NAME "" CACHE STRING "A filename to set XR_CORE_VALIDATION_FILE_NAME to.")

option(USE_SYSTEM_OPENXR "Try using system installation of OpenXR if available" OFF)
option(USE_SYSTEM_GLM "Try using system installation of glm if available" OFF)

# Directory for generated files, those being split headers and stubs
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Platform-dependent flags
# Support Vulkan on Linux instead of DirectX
if (WIN32)
	set(GRAPHICS_API_SUPPORT_FLAGS -DSUPPORT_DX -DSUPPORT_DX11 -DSUPPORT_DX12 -DSUPPORT_VK -DSUPPORT_GL)
elseif (ANDROID)
	set(GRAPHICS_API_SUPPORT_FLAGS -DSUPPORT_VK -DSUPPORT_GLES)
else ()
	set(GRAPHICS_API_SUPPORT_FLAGS -DSUPPORT_VK -DSUPPORT_GL)
endif()

set(FORCE_COLORED_OUTPUT            OFF CACHE BOOL "Always produce ANSI-colored output (GNU/Clang only).")

if(FORCE_COLORED_OUTPUT)
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		add_compile_options(-fdiagnostics-color=always)
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		add_compile_options(-fcolor-diagnostics)
	endif()
endif()

# For all projects, set the symbol visibility to private on Linux
# If we don't then if an application declares a function with the same name as an OpenComposite function
# the application's one will be used instead. This has some nasty effects - for example, when using the
# global installation both libopenvr_api.so and OpenComposite will define VR_InitInternal2. What's supposed
# to happen is that libopenvr_api calls a VRClient interface method which in turn calls OpenComposite's version
# of VR_InitInternal2. But since libopenvr_api was loaded first it's function will be used, leading to
# a stack overflow.
# In general using private symbols is a great idea, and it's something we'd want to do anyway.
# There is also -Bsymbolic set when linking the final shared library, see the bottom of this file
# FIXME the Vulkan functions still get exported, hopefully they won't fight with the application's ones.
if (WIN32)
else ()
    add_definitions(-fvisibility=hidden)
endif ()

# === Runtime Switcher ===
include_external_msproject(
	RuntimeSwitcher ${CMAKE_SOURCE_DIR}/RuntimeSwitcher/RuntimeSwitcher.csproj
	TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
	PLATFORM "AnyCPU"
)

# === OpenVR Headers ===
add_library(OpenVR INTERFACE)
target_include_directories(OpenVR INTERFACE ${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders) # TODO make this private and put the public headers elsewhere

# === Vulkan ===
add_library(Vulkan INTERFACE)

if (WIN32)
	# On Windows, use the bundled copy
	target_include_directories(Vulkan INTERFACE libs/vulkan/Include) # TODO make this private and put the public headers elsewhere
	if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
		target_link_libraries(Vulkan INTERFACE ${CMAKE_CURRENT_LIST_DIR}/libs/vulkan/Lib/vulkan-1.lib)
	else ()
		target_link_libraries(Vulkan INTERFACE ${CMAKE_CURRENT_LIST_DIR}/libs/vulkan/Lib32/vulkan-1.lib)
	endif ()

	target_compile_definitions(Vulkan INTERFACE -DVK_USE_PLATFORM_WIN32_KHR)
elseif (ANDROID)
	# Let the system sort out the linkage, we'll just use our included headers
	target_include_directories(Vulkan INTERFACE libs/vulkan/Include)
else ()
	# On Linux, use the system copy
	find_library(Vulkan vulkan REQUIRED)
	target_include_directories(Vulkan INTERFACE ${Vulkan_INCLUDE_DIR})

	# We have to include the vulkan library, since the linker is now set to fail if we use undefined symbols
	# On Gentoo at least, it seems there's nothing in Vulkan_LIBRARIES
	if ("${Vulkan_LIBRARIES}")
		target_link_libraries(Vulkan INTERFACE ${Vulkan_LIBRARIES})
	else ()
		target_link_libraries(Vulkan INTERFACE -lvulkan)
	endif ()

endif ()

# === OpenXR ===

if (USE_SYSTEM_OPENXR)
	find_package(OpenXR)
	set(XrLib OpenXR::openxr_loader)
endif()

if (NOT OpenXR_FOUND)
	# Building CMake subprojects is a real pain (IMO), so just build this here
	set(XrDir ${CMAKE_CURRENT_LIST_DIR}/libs/openxr-sdk)
	set(XrDirLoader ${CMAKE_CURRENT_LIST_DIR}/libs/openxr-sdk/src/loader)
	set(XrDirCommon ${CMAKE_CURRENT_LIST_DIR}/libs/openxr-sdk/src/common)
	if (ANDROID)
		# Whatever consumes this library must then link to an OpenXR loader, such as the Oculus one
		add_library(OpenXR STATIC ${CMAKE_CURRENT_LIST_DIR}/scripts/empty.c) # Doesn't do anything
	else ()
	add_library(OpenXR STATIC
		${XrDirLoader}/api_layer_interface.cpp
		${XrDirLoader}/api_layer_interface.hpp
		${XrDirLoader}/loader_core.cpp
		${XrDirLoader}/loader_instance.cpp
		${XrDirLoader}/loader_instance.hpp
		${XrDirLoader}/loader_logger.cpp
		${XrDirLoader}/loader_logger.hpp
		${XrDirLoader}/loader_logger_recorders.cpp
		${XrDirLoader}/loader_logger_recorders.hpp
		${XrDirLoader}/manifest_file.cpp
		${XrDirLoader}/manifest_file.hpp
		${XrDirLoader}/runtime_interface.cpp
		${XrDirLoader}/runtime_interface.hpp

		${XrDirLoader}/xr_generated_loader.hpp
		${XrDirLoader}/xr_generated_loader.cpp
		${XrDir}/src/xr_generated_dispatch_table.h
		${XrDir}/src/xr_generated_dispatch_table.c

		${XrDirCommon}/filesystem_utils.cpp
		${XrDirCommon}/object_info.cpp

		${XrDir}/src/external/jsoncpp/src/lib_json/json_reader.cpp
		${XrDir}/src/external/jsoncpp/src/lib_json/json_value.cpp
		${XrDir}/src/external/jsoncpp/src/lib_json/json_writer.cpp
	)
	endif()
	target_include_directories(OpenXR PRIVATE ${XrDirCommon} ${XrDir}/src ${XrDir}/src/external/jsoncpp/include)
	target_include_directories(OpenXR PUBLIC ${XrDir}/include)
	# Platform-dependent flags
	if (WIN32)
		target_compile_definitions(OpenXR PRIVATE -DXR_OS_WINDOWS -DXR_USE_PLATFORM_WIN32
		-DXR_USE_GRAPHICS_API_D3D11 -DXR_USE_GRAPHICS_API_D3D12 -DXR_USE_GRAPHICS_API_OPENGL)
		target_link_libraries(OpenXR PUBLIC advapi32 pathcch OpenGL32)
	else()
		# TODO Turtle1331 should we include -DXR_USE_PLATFORM_(XLIB|XCB|WAYLAND) here?
		target_compile_definitions(OpenXR PRIVATE -DXR_OS_LINUX
		-DXR_USE_GRAPHICS_API_OPENGL -DXR_USE_GRAPHICS_API_VULKAN)
		target_link_libraries(OpenXR PUBLIC -ldl)
	endif()
	target_link_libraries(OpenXR PUBLIC Vulkan)

	if (ANDROID)
		target_compile_definitions(OpenXR PUBLIC -DXR_USE_PLATFORM_ANDROID -DXR_USE_GRAPHICS_API_OPENGL_ES)
	endif()
	set(XrLib OpenXR)
endif()

# === glm ===
# Since we used to use LibOVR's maths library, we need a replacement
# glm is an obvious choice

if (USE_SYSTEM_GLM)
	find_package(glm)
	set(glmLib glm::glm)
endif()

if (NOT glm_FOUND)
	add_library(glm INTERFACE)
	target_include_directories(glm INTERFACE ${CMAKE_CURRENT_LIST_DIR}/libs/glm) # No separate include directory :(
	set(glmLib glm)
endif()

# === DrvOpenXR ===
add_library(DrvOpenXR STATIC
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/DrvOpenXR.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrDriverPrivate.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrBackend.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrBackend.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrTrackedDevice.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrTrackedDevice.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrHMD.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrHMD.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrController.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/XrController.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/tmp_gfx/TemporaryGraphics.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/tmp_gfx/TemporaryGraphics.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/tmp_gfx/TemporaryD3D11.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/tmp_gfx/TemporaryD3D11.h
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/tmp_gfx/TemporaryVk.cpp
	${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/tmp_gfx/TemporaryVk.h

	# Ensuring vrtypes.h exists should mean the rest of our generated interfaces exists
	${GENERATED_DIR}/interfaces/vrtypes.h
	${GENERATED_DIR}/static_bases.gen.h
)
target_include_directories(DrvOpenXR PUBLIC ${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/pub ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(DrvOpenXR PRIVATE ${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR ${CMAKE_CURRENT_LIST_DIR}/OpenOVR)
target_link_libraries(DrvOpenXR PUBLIC OpenVR ${XrLib} ${glmLib})
target_compile_definitions(DrvOpenXR PRIVATE ${GRAPHICS_API_SUPPORT_FLAGS} -D_CRT_SECURE_NO_WARNINGS)
source_group(Public REGULAR_EXPRESSION ${CMAKE_CURRENT_LIST_DIR}/DrvOpenXR/pub/*)

if (NOT (XR_VALIDATION_LAYER_PATH STREQUAL ""))
	target_compile_definitions(DrvOpenXR PRIVATE -DXR_VALIDATION_LAYER_PATH=\"${XR_VALIDATION_LAYER_PATH}\")
endif ()
if (NOT (XR_VALIDATION_FILE_NAME STREQUAL ""))
	target_compile_definitions(DrvOpenXR PRIVATE -DXR_VALIDATION_FILE_NAME=\"${XR_VALIDATION_FILE_NAME}\")
endif ()

# === OCCore ===
# TODO: precompiled headers
if (WIN32)
	set(OVR_RESOURCES
		OpenOVR/resources.rc
	)
else ()
	enable_language(ASM)
	set_property(SOURCE ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/resources_linux.s APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")
	set_property(SOURCE ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/resources_linux.s SET PROPERTY INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}")
	set(OVR_RESOURCES
			${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/resources_linux.s
	)
endif ()
set(OVR_PCH_EXCLUDED
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/ini.c
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/jsoncpp.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/lodepng.cpp
)

add_library(OCCore STATIC
	# This file is used to generate the precompiled headers
		${CMAKE_CURRENT_LIST_DIR}/OpenOVR/stdafx.cpp

	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/compositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/dx11compositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/dx10compositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/dx12compositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/glcompositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/glescompositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/vkcompositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/convert.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/logging.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/linux_funcs.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Config.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/debug_helper.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Haptics.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/xrutil.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/xrmoreutils.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Keyboard/KeyboardLayout.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Keyboard/SudoFontMeta.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Keyboard/VRKeyboard.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/InteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/OculusInteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/KhrSimpleInteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/ViveInteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/IndexControllerInteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/HolographicInteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/ReverbG2InteractionProfile.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/OpenOVR.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseApplications.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseChaperone.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseChaperoneSetup.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseClientCore.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseCompositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseExtendedDisplay.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseInput.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseInput_Hand.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseInputInternal.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseOverlay.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseOverlayView.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseRenderModels.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseScreenshots.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseSettings.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseSystem.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseMailbox.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseControlPanel.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRApplications.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRChaperone.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRChaperoneSetup.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRClientCore.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRCompositor.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRExtendedDisplay.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRInput.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRInputInternal.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVROverlay.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVROverlayView.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRRenderModels.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRScreenshots.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRSettings.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRSystem.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRMailbox.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRControlPanel.cpp
	${GENERATED_DIR}/stubs.gen.cpp

	# Base classes
		${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseServerDriverHost.cpp
		${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseServerDriverHost.h

	# Definitions
		${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVRServerDriverHost.cpp

	# Exclude from the PCH requirement
	${OVR_PCH_EXCLUDED}

	# Headers
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/BaseCommon.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Compositor/compositor.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/convert.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/custom_types.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/logging.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Config.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/debug_helper.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Haptics.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/ini.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/json/json-forwards.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/json/json.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Keyboard/KeyboardLayout.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Keyboard/SudoFontMeta.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Keyboard/VRKeyboard.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/InteractionProfile.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/OculusInteractionProfile.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/Input/KhrSimpleInteractionProfile.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/lodepng.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Misc/ScopeGuard.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseApplications.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseChaperone.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseChaperoneSetup.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseClientCore.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseCompositor.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseExtendedDisplay.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseInput.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseInputInternal.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseOverlay.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseOverlayView.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseRenderModels.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseScreenshots.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseSettings.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseSystem.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseMailbox.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/BaseControlPanel.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/Interfaces.h
	${GENERATED_DIR}/static_bases.gen.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/resources.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/stdafx.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/steamvr_abi.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/targetver.h

	# Newly-added classes
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Drivers/DriverManager.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Drivers/DriverManager.h
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Drivers/Backend.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Drivers/Backend.h

	# While not actually part of OCCore, list all the OpenVR interfaces here so they are easily accessable in IDE
	${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/IVRClientCore_002.h
	${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/IVRClientCore_003.h
	${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/IVRCompositor_017.h
	${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/IVRMailbox_001.h
	${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/IVRInputInternal_002.h
	${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/IVRControlPanel_006.h
	# Ensuring vrtypes.h exists should mean the rest of our generated interfaces exists
	${GENERATED_DIR}/interfaces/vrtypes.h
)
target_include_directories(OCCore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/OpenOVR ${CMAKE_CURRENT_BINARY_DIR})  # TODO make this private and put the public headers elsewhere
target_include_directories(OCCore PRIVATE BundledLibs OpenVRHeaders)
target_compile_definitions(OCCore PRIVATE ${GRAPHICS_API_SUPPORT_FLAGS})

target_link_libraries(OCCore OpenVR Vulkan ${XrLib} ${glmLib})

if (NOT WIN32 AND NOT ANDROID)
	find_package(OpenGL REQUIRED) # for glGetError()
	target_link_libraries(OCCore ${OPENGL_LIBRARIES})
endif ()

# Set up precompiled headers for OCCore
target_precompile_headers(OCCore PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/stdafx.h)
set_source_files_properties(${OVR_PCH_EXCLUDED} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

source_group(OpenVR REGULAR_EXPRESSION ${GENERATED_DIR}/interfaces)
source_group(OpenVR\\Drivers REGULAR_EXPRESSION ${GENERATED_DIR}/interfaces/driver_*)
source_group(OpenVR\\Custom REGULAR_EXPRESSION ${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/custom_interfaces/*)
source_group(Interfaces REGULAR_EXPRESSION ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/Base*)
source_group(Interfaces\\Declarations REGULAR_EXPRESSION ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl/CVR*)

# === OCOVR ===
if (WIN32)
	set(OCOVR_PLAT_SRC windows.cpp)
else ()
	set(OCOVR_PLAT_SRC linux.cpp)
endif ()
set(OCOVR_SRC_ALL
	${CMAKE_CURRENT_LIST_DIR}/OCOVR/${OCOVR_PLAT_SRC}
	${CMAKE_CURRENT_LIST_DIR}/OCOVR/openvr_api.cpp
	${CMAKE_CURRENT_LIST_DIR}/OCOVR/openvr_api_0_9_12.cpp

	# Resources don't get nicely included in a library file
	${OVR_RESOURCES}
)

# On Android, build a static library so it can be linked into the target application
# This is required since we can't build the openxr loader on android.
if (ANDROID)
	add_library(OCOVR STATIC ${OCOVR_SRC_ALL})
else ()
	add_library(OCOVR SHARED ${OCOVR_SRC_ALL})
endif ()

# Require that all symbols are defined on Linux - this is always done on Windows
# Also on Linux, put all the static libraries in a group to avoid ordering problems
if (NOT WIN32)
	target_link_libraries(OCOVR PRIVATE -Wl,--no-undefined)
	target_link_libraries(OCOVR PUBLIC -Wl,--start-group OCCore DrvOpenXR -Wl,--end-group)
else ()
	# On Windows this isn't a problem since the linker knows how to figure this stuff out
	target_link_libraries(OCOVR OCCore DrvOpenXR)
endif ()

# If we're on Linux, compile everything as position-independent
if (WIN32)
else ()
	target_compile_options(DrvOpenXR PRIVATE -fPIC)
	if (NOT OpenXR_FOUND)
		target_compile_options(OpenXR PRIVATE -fPIC)
	endif ()
	target_compile_options(OCCore PRIVATE -fPIC)
endif ()

# The -Bsymbolic makes this work on exported functions - otherwise those will still use the first-defined one.
# See the comment at the top about -fvisibility=hidden
if (WIN32)
else ()
	target_link_options(OCOVR PRIVATE -Wl,-Bsymbolic -Wl,-Bsymbolic-functions)

	# Ensure all required symbols are actually found, don't produce a binary that can't be loaded
	target_link_options(OCOVR PRIVATE -z defs)

	# Oh, and we need dlopen
	target_link_libraries(OCOVR PUBLIC -ldl)
endif ()

# needed for generated files
target_include_directories(OCOVR PRIVATE ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl)

# Required because the compositor header needs the platform-specific structures enabled via defines
target_compile_definitions(OCOVR PRIVATE ${GRAPHICS_API_SUPPORT_FLAGS})

find_package(Python REQUIRED Interpreter)

# glob for all openvr headers
file(GLOB openvr-headers CONFIGURE_DEPENDS LIST_DIRECTORIES false ${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders/openvr-*)

# glob for stub generator libraries
file(GLOB stub-deps CONFIGURE_DEPENDS LIST_DIRECTORIES false ${CMAKE_CURRENT_LIST_DIR}/scripts/stubs/*)

# Command for running header splitting script
add_custom_command(
	OUTPUT ${GENERATED_DIR}/interfaces/vrtypes.h
	COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/scripts/split_headers.py ${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders ${GENERATED_DIR}
	DEPENDS ${CMAKE_CURRENT_LIST_DIR}/scripts/split_headers.py ${openvr-headers}
	COMMENT "Splitting headers..."
	)

# Command for running stub generator
add_custom_command(
	OUTPUT ${GENERATED_DIR}/stubs.gen.cpp ${GENERATED_DIR}/static_bases.gen.h
	COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/scripts/stubs.py ${CMAKE_CURRENT_LIST_DIR}/OpenOVR/Reimpl ${CMAKE_CURRENT_LIST_DIR}/OpenVRHeaders ${GENERATED_DIR}
	DEPENDS ${CMAKE_CURRENT_LIST_DIR}/scripts/stubs.py ${stub-deps} ${GENERATED_DIR}/interfaces/vrtypes.h
	COMMENT "Generating stubs..."
	)

# Allows clean target to delete generated files too
set_property(
	TARGET OCCore
	APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${GENERATED_DIR};${CMAKE_BINARY_DIR}/bin)

if ( CMAKE_SIZEOF_VOID_P EQUAL 8) # 64 bit build - void pointer is 8 bits on 64 bit
	set(is_64bit_build true)
else()
	set(is_64bit_build false)
endif()

# Move OCOVR to appropriate directory expected by OpenVR and rename it to vrclient (or vrclient_x64)
# This enables marking the build directory as the OpenVR runtime path.
# For example, you can set the VR_OVERRIDE variable to the build dir (VR_OVERRIDE=<path to build dir>) when launching an app.
# see VR_LoadHmdSystemInternal() from openvr_api_public.cpp in the OpenVR repo for the expected paths.
if (WIN32)
	set(VRCLIENT_DIR bin)
	if ( is_64bit_build )
		set(VRCLIENT_NAME vrclient_x64)
	else()
		set(VRCLIENT_NAME vrclient)
	endif()
else ()
	set(VRCLIENT_NAME vrclient)
	if ( is_64bit_build )
		set(VRCLIENT_DIR bin/linux64)
	else()
		set(VRCLIENT_DIR bin)
	endif()
endif ()

# Windows puts DLLs in RUNTIME_OUTPUT_DIRECTORY for some reason
set_target_properties(OCOVR PROPERTIES
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${VRCLIENT_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${VRCLIENT_DIR}
	LIBRARY_OUTPUT_NAME ${VRCLIENT_NAME}
	RUNTIME_OUTPUT_NAME ${VRCLIENT_NAME})

# ensure output directory exists
get_target_property(output_dir OCOVR LIBRARY_OUTPUT_DIRECTORY)
add_custom_command(TARGET OCOVR
	PRE_LINK COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir})
