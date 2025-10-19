#!/usr/bin/env bash
set -e

export DISPLAY=:99
Xvfb $DISPLAY -screen 0 1024x768x24 -ac +extension GLX +render -nolisten tcp &
fluxbox >/tmp/fluxbox.log 2>&1 &
x11vnc -display $DISPLAY -forever -shared -nopw >/tmp/x11vnc.log 2>&1 &

# noVNC
cd /opt/novnc
websockify --web . 6080 localhost:5900 >/tmp/websockify.log 2>&1 &

# Uygulama dizinine dön
cd /app

echo "=== DIAG ==="
echo "PWD=$(pwd)"
echo "CUB_FILE=${CUB_FILE}"
echo "LS /app:"
ls -l
echo "============"

# test
# Windows bind-mount'ta exec biti düşebiliyor; garantiye al
if [ -f "./cub3D" ] && [ ! -x "./cub3D" ]; then
  chmod +x ./cub3D || true
fi

# CUB_FILE'in bulunduğu klasöre göre çalışma dizinini çözüyoruz (ör. mandatory)
MAP_PARENT_DIR=$(dirname "${CUB_FILE}")
APP_DIR=$(cd "${MAP_PARENT_DIR}/.." && pwd)
APP_BIN="${APP_DIR}/cub3D"

# Eğer kökteki symlink çalışıyorsa onu tercih et
if [ -x "/app/cub3D" ]; then
  APP_BIN="/app/cub3D"
fi

if [ -d "${APP_DIR}" ] && [ -x "${APP_BIN}" ]; then
  # Oyun texture'ları göreli olarak açtığı için doğru dizinden çalıştır
  (
    cd "${APP_DIR}"
    "${APP_BIN}" "${CUB_FILE}"
  ) || true
else
  echo "cub3D bulunamadı; test için xclock açılıyor."
  xclock >/tmp/xclock.log 2>&1 &
fi

tail -f /tmp/*.log /dev/null
