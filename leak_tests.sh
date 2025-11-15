#!/usr/bin/env bash
set -u

BIN=./cub3d
OK=0
FAIL=0

mkdir -p logs

VALID_MAPS=(maps/valid/*.cub)
INVALID_MAPS=(maps/invalid/*.cub)

if [ ! -x "$BIN" ]; then
  echo "Error: $BIN not found or not executable."
  exit 127
fi

check_leak() {
  local mapfile="$1"
  local log="logs/$(basename "$mapfile").log"
  valgrind --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all "$BIN" "$mapfile" >"$log" 2>&1
  if grep -q "All heap blocks were freed" "$log" && grep -q "in use at exit: 0 bytes" "$log"; then
    echo "✅ LEAK FREE: $mapfile"
    ((OK++))
  else
    echo "❌ LEAK DETECTED: $mapfile"
    ((FAIL++))
    grep "in use at exit" "$log"
  fi
}

echo "==> Invalid map leak tests"
for m in "${INVALID_MAPS[@]}"; do
  [ -f "$m" ] && check_leak "$m"
done

echo "==> Valid map leak tests"
for m in "${VALID_MAPS[@]}"; do
  [ -f "$m" ] && check_leak "$m"
done

echo "Summary: $OK LEAK FREE, $FAIL LEAK DETECTED"