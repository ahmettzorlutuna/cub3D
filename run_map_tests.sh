#!/usr/bin/env bash
set -u  # -e ve -o pipefail kaldırıldı, çünkü testler hata alabilir

BIN=./cub3d
OK=0
FAIL=0

mkdir -p logs

# Geçerli haritalar
VALID_MAPS=(maps/valid/*.cub)
# Hatalı haritalar
INVALID_MAPS=(maps/invalid/*.cub)

if [ ! -x "$BIN" ]; then
  echo "Error: $BIN not found or not executable."
  exit 127
fi

echo "==> Invalid map tests"
for m in "${INVALID_MAPS[@]}"; do
  if [ ! -f "$m" ]; then
    echo "SKIP (file not found): $m"
    continue
  fi
  EXIT_CODE=0
  "$BIN" "$m" >/dev/null 2>&1 || EXIT_CODE=$?
  if [ "$EXIT_CODE" -eq 1 ]; then
    echo "✅ PASS (failed as expected): $m"
    ((OK++))
  else
    echo "❌ FAIL (should fail with exit 1, but got $EXIT_CODE): $m"
    ((FAIL++))
  fi
done

echo "==> Valid map tests"
for m in "${VALID_MAPS[@]}"; do
  if [ ! -f "$m" ]; then
    echo "SKIP (file not found): $m"
    continue
  fi
  EXIT_CODE=0
  "$BIN" "$m" >/dev/null 2>&1 || EXIT_CODE=$?
  if [ "$EXIT_CODE" -eq 0 ]; then
    echo "✅ PASS (valid map succeeded): $m"
    ((OK++))
  else
    echo "❌ FAIL (valid map should succeed, got exit $EXIT_CODE): $m"
    ((FAIL++))
  fi
done

echo "Summary: $OK PASS, $FAIL FAIL"