# QT_Projects

export QT_QPA_PLATFORM=offscreen
export WESTON_DRM_MIRROR=1
export WESTON_DRM_KEEP_RATIO=1
export PIXMAN_USE_RGA=1
export GST_VIDEO_CONVERT_USE_RGA=1
export GST_V4L2_PREFERRED_FOURCC=YU12
export QT_GSTREAMER_WINDOW_VIDEOSINK=waylandsink
export QT_WAYLAND_CLIENT_BUFFER_INTEGRATION=wayland
mkdir -p /tmp/.xdg &&  chmod 0700 /tmp/.xdg
export XDG_RUNTIME_DIR=/tmp/.xdg
weston --tty=2 -B=drm-backend.so --idle-time=0 --use-pixman&
