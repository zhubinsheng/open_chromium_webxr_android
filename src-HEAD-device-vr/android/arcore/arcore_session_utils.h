// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_VR_ANDROID_ARCORE_ARCORE_SESSION_UTILS_H_
#define DEVICE_VR_ANDROID_ARCORE_ARCORE_SESSION_UTILS_H_

#include "base/android/scoped_java_ref.h"
#include "base/memory/weak_ptr.h"
#include "gpu/ipc/common/surface_handle.h"
#include "ui/display/display.h"
#include "ui/gfx/geometry/point_f.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {
class WindowAndroid;
}  // namespace ui

namespace device {

// Immersive AR sessions use callbacks in the following sequence:
//
// RequestArSession
//   SurfaceReadyCallback
//   SurfaceTouchCallback (repeated for each touch)
//   [exit session via "back" button, or via JS session exit]
//   DestroyedCallback
//
using SurfaceReadyCallback =
    base::RepeatingCallback<void(gfx::AcceleratedWidget window,
                                 gpu::SurfaceHandle handle,
                                 ui::WindowAndroid* root_window,
                                 display::Display::Rotation rotation,
                                 const gfx::Size& size)>;
using SurfaceTouchCallback =
    base::RepeatingCallback<void(bool is_primary,
                                 bool touching,
                                 int32_t pointer_id,
                                 const gfx::PointF& location)>;
using SurfaceDestroyedCallback = base::OnceClosure;

class ArCoreSessionUtils {
 public:
  virtual ~ArCoreSessionUtils() = default;
  virtual bool EnsureLoaded() = 0;
  virtual base::android::ScopedJavaLocalRef<jobject>
  GetApplicationContext() = 0;
  virtual void RequestArSession(
      int render_process_id,
      int render_frame_id,
      bool use_overlay,
      bool can_render_dom_content,
      SurfaceReadyCallback ready_callback,
      SurfaceTouchCallback touch_callback,
      SurfaceDestroyedCallback destroyed_callback) = 0;
  virtual void EndSession() = 0;
};

}  // namespace device

#endif  // DEVICE_VR_ANDROID_ARCORE_ARCORE_SESSION_UTILS_H_
