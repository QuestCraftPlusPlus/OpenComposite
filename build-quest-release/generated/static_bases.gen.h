#pragma once
#include <memory>
class BaseCompositor;
std::shared_ptr<BaseCompositor> GetBaseCompositor();
BaseCompositor* GetUnsafeBaseCompositor();
std::shared_ptr<BaseCompositor> GetCreateBaseCompositor();
class BaseSystem;
std::shared_ptr<BaseSystem> GetBaseSystem();
BaseSystem* GetUnsafeBaseSystem();
std::shared_ptr<BaseSystem> GetCreateBaseSystem();
class BaseChaperone;
std::shared_ptr<BaseChaperone> GetBaseChaperone();
BaseChaperone* GetUnsafeBaseChaperone();
std::shared_ptr<BaseChaperone> GetCreateBaseChaperone();
class BaseOverlay;
std::shared_ptr<BaseOverlay> GetBaseOverlay();
BaseOverlay* GetUnsafeBaseOverlay();
std::shared_ptr<BaseOverlay> GetCreateBaseOverlay();
class BaseChaperoneSetup;
std::shared_ptr<BaseChaperoneSetup> GetBaseChaperoneSetup();
BaseChaperoneSetup* GetUnsafeBaseChaperoneSetup();
std::shared_ptr<BaseChaperoneSetup> GetCreateBaseChaperoneSetup();
class BaseRenderModels;
std::shared_ptr<BaseRenderModels> GetBaseRenderModels();
BaseRenderModels* GetUnsafeBaseRenderModels();
std::shared_ptr<BaseRenderModels> GetCreateBaseRenderModels();
class BaseScreenshots;
std::shared_ptr<BaseScreenshots> GetBaseScreenshots();
BaseScreenshots* GetUnsafeBaseScreenshots();
std::shared_ptr<BaseScreenshots> GetCreateBaseScreenshots();
class BaseSettings;
std::shared_ptr<BaseSettings> GetBaseSettings();
BaseSettings* GetUnsafeBaseSettings();
std::shared_ptr<BaseSettings> GetCreateBaseSettings();
class BaseExtendedDisplay;
std::shared_ptr<BaseExtendedDisplay> GetBaseExtendedDisplay();
BaseExtendedDisplay* GetUnsafeBaseExtendedDisplay();
std::shared_ptr<BaseExtendedDisplay> GetCreateBaseExtendedDisplay();
class BaseApplications;
std::shared_ptr<BaseApplications> GetBaseApplications();
BaseApplications* GetUnsafeBaseApplications();
std::shared_ptr<BaseApplications> GetCreateBaseApplications();
class BaseInput;
std::shared_ptr<BaseInput> GetBaseInput();
BaseInput* GetUnsafeBaseInput();
std::shared_ptr<BaseInput> GetCreateBaseInput();
class BaseInputInternal;
std::shared_ptr<BaseInputInternal> GetBaseInputInternal();
BaseInputInternal* GetUnsafeBaseInputInternal();
std::shared_ptr<BaseInputInternal> GetCreateBaseInputInternal();
class BaseClientCore;
std::shared_ptr<BaseClientCore> GetBaseClientCore();
BaseClientCore* GetUnsafeBaseClientCore();
std::shared_ptr<BaseClientCore> GetCreateBaseClientCore();
class BaseOverlayView;
std::shared_ptr<BaseOverlayView> GetBaseOverlayView();
BaseOverlayView* GetUnsafeBaseOverlayView();
std::shared_ptr<BaseOverlayView> GetCreateBaseOverlayView();
class BaseMailbox;
std::shared_ptr<BaseMailbox> GetBaseMailbox();
BaseMailbox* GetUnsafeBaseMailbox();
std::shared_ptr<BaseMailbox> GetCreateBaseMailbox();
class BaseControlPanel;
std::shared_ptr<BaseControlPanel> GetBaseControlPanel();
BaseControlPanel* GetUnsafeBaseControlPanel();
std::shared_ptr<BaseControlPanel> GetCreateBaseControlPanel();
class BaseServerDriverHost;
std::shared_ptr<BaseServerDriverHost> GetBaseServerDriverHost();
BaseServerDriverHost* GetUnsafeBaseServerDriverHost();
std::shared_ptr<BaseServerDriverHost> GetCreateBaseServerDriverHost();
