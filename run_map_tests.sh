#!/usr/bin/env bash
set -u

# Binary ismini belirle
if [ -f "./cub3D" ]; then
    BIN="./cub3D"
else
    BIN="./cub3d"
fi

OK=0
FAIL=0

mkdir -p logs

VALID_MAPS=(maps/valid/*.cub)
INVALID_MAPS=(maps/invalid/*.cub)

if [ ! -x "$BIN" ]; then
  echo "Error: $BIN not found or not executable."
  exit 127
fi

echo "========================================"
echo "==> Invalid Map Tests (Should Exit 1)"
echo "========================================"
for m in "${INVALID_MAPS[@]}"; do
  if [ ! -f "$m" ]; then continue; fi
  
  # Invalid map'ler hemen kapanmalı, user input gerekmez.
  "$BIN" "$m" >/dev/null 2>&1
  EXIT_CODE=$?
  
  if [ "$EXIT_CODE" -eq 1 ]; then
    echo "✅ PASS: $m"
    ((OK++))
  else
    echo "❌ FAIL (Got exit $EXIT_CODE, expected 1): $m"
    ((FAIL++))
  fi
done

echo ""
echo "========================================"
echo "==> Valid Map Tests (Should Exit 0)"
echo "========================================"
for m in "${VALID_MAPS[@]}"; do
  if [ ! -f "$m" ]; then continue; fi

  # 1. Programı arka planda başlat
  "$BIN" "$m" >/dev/null 2>&1 &
  PID=$!

  # 2. Bekle (CI ortamı yavaş olabilir, 3 saniye güvenlidir)
  sleep 3

  # 3. Sanal tuşa bas (ESC)
  # Bu komut o anki X11 display'ine tuş gönderir.
  xdotool key Escape

  # 4. Programın kapanmasını bekle
  wait $PID
  EXIT_CODE=$?

  if [ "$EXIT_CODE" -eq 0 ]; then
    echo "✅ PASS: $m"
    ((OK++))
  else
    echo "❌ FAIL (Got exit $EXIT_CODE, expected 0): $m"
    ((FAIL++))
  fi
done

echo "----------------------------------------"
echo "Summary: $OK PASS, $FAIL FAIL"
echo "----------------------------------------"

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi
exit 0