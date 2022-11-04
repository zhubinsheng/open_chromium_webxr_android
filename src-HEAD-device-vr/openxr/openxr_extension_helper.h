// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_VR_OPENXR_OPENXR_EXTENSION_HELPER_H_
#define DEVICE_VR_OPENXR_OPENXR_EXTENSION_HELPER_H_

+#ifdef XR_USE_GRAPHICS_API_D3D11
 #include <d3d11.h>
+#endif
+
+#ifdef XR_USE_GRAPHICS_API_OPENGL
+#if defined(XR_USE_PLATFORM_XLIB) || defined(XR_USE_PLATFORM_XCB)


+//# include <GL/glx.h>
+

+//#include <X11/Xlib.h>
+//#include <X11/Xutil.h>
+//typedef struct __GLXcontextRec *GLXContext;
+//typedef XID GLXDrawable;
+//typedef struct __GLXFBConfigRec *GLXFBConfig;
+//#include "ui/gl/gl_bindings.h"
+
+using Display = struct _XDisplay;
+using Bool = int;
+using Status = int;
+using XID = unsigned long;
+using Colormap = XID;
+using Font = XID;
+using Pixmap = XID;
+using Window = XID;
+using GLXPixmap = XID;
+using GLXWindow = XID;
+using GLXDrawable = XID;
+using GLXPbuffer = XID;
+using GLXContextID = XID;
+using GLXContext = struct __GLXcontextRec*;
+using GLXFBConfig = struct __GLXFBConfigRec*;
// +struct XVisualInfo;

+#endif  // (XR_USE_PLATFORM_XLIB || XR_USE_PLATFORM_XCB)
+#endif

#include <vector>

#include "base/logging.h"
#include "base/memory/raw_ptr.h"
#include "third_party/openxr/src/include/openxr/openxr.h"
#include "third_party/openxr/src/include/openxr/openxr_platform.h"

namespace device {
struct OpenXrExtensionMethods {
  OpenXrExtensionMethods();
  ~OpenXrExtensionMethods();

   // D3D
+  #ifdef XR_USE_GRAPHICS_API_D3D11
   PFN_xrGetD3D11GraphicsRequirementsKHR xrGetD3D11GraphicsRequirementsKHR{
       nullptr};
+  #endif
+  #ifdef XR_USE_GRAPHICS_API_OPENGL
+  PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR{
+      nullptr};
+  #endif

  // Hand Tracking
  PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT{nullptr};
  PFN_xrDestroyHandTrackerEXT xrDestroyHandTrackerEXT{nullptr};
  PFN_xrLocateHandJointsEXT xrLocateHandJointsEXT{nullptr};

  // Anchors
  PFN_xrCreateSpatialAnchorMSFT xrCreateSpatialAnchorMSFT{nullptr};
  PFN_xrDestroySpatialAnchorMSFT xrDestroySpatialAnchorMSFT{nullptr};
  PFN_xrCreateSpatialAnchorSpaceMSFT xrCreateSpatialAnchorSpaceMSFT{nullptr};

  // Scene Understanding
  PFN_xrEnumerateSceneComputeFeaturesMSFT xrEnumerateSceneComputeFeaturesMSFT{
      nullptr};
  PFN_xrCreateSceneObserverMSFT xrCreateSceneObserverMSFT{nullptr};
  PFN_xrDestroySceneObserverMSFT xrDestroySceneObserverMSFT{nullptr};
  PFN_xrCreateSceneMSFT xrCreateSceneMSFT{nullptr};
  PFN_xrDestroySceneMSFT xrDestroySceneMSFT{nullptr};
  PFN_xrComputeNewSceneMSFT xrComputeNewSceneMSFT{nullptr};
  PFN_xrGetSceneComputeStateMSFT xrGetSceneComputeStateMSFT{nullptr};
  PFN_xrGetSceneComponentsMSFT xrGetSceneComponentsMSFT{nullptr};
  PFN_xrLocateSceneComponentsMSFT xrLocateSceneComponentsMSFT{nullptr};
  PFN_xrGetSceneMeshBuffersMSFT xrGetSceneMeshBuffersMSFT{nullptr};

  // Time
  PFN_xrConvertWin32PerformanceCounterToTimeKHR
      xrConvertWin32PerformanceCounterToTimeKHR{nullptr};
};

class OpenXrExtensionEnumeration {
 public:
  OpenXrExtensionEnumeration();
  ~OpenXrExtensionEnumeration();

  bool ExtensionSupported(const char* extension_name) const;

 private:
  std::vector<XrExtensionProperties> extension_properties_;
};

class OpenXrExtensionHelper {
 public:
  OpenXrExtensionHelper(
      XrInstance instance,
      const OpenXrExtensionEnumeration* const extension_enumeration);
  ~OpenXrExtensionHelper();

  const OpenXrExtensionEnumeration* ExtensionEnumeration() const {
    return extension_enumeration_;
  }

  const OpenXrExtensionMethods& ExtensionMethods() const {
    return extension_methods_;
  }

 private:
  const OpenXrExtensionMethods extension_methods_;
  const raw_ptr<const OpenXrExtensionEnumeration> extension_enumeration_;
};

}  // namespace device

#endif  // DEVICE_VR_OPENXR_OPENXR_EXTENSION_HELPER_H_
