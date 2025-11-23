#!/usr/bin/env bash
set -u

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

# ---------------------------------------------------
# INVALID MAP LEAK CHECK (Basit, input gerekmez)
# ---------------------------------------------------
check_leak_invalid() {
  local mapfile="$1"
  local log="logs/leak_invalid_$(basename "$mapfile").log"
  
  # Valgrind direk çalışır, program hata verip çıkar.
  valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all "$BIN" "$mapfile" >"$log" 2>&1
  
  if grep -q "All heap blocks were freed" "$log" && grep -q "in use at exit: 0 bytes" "$log"; then
    echo "✅ LEAK FREE (Invalid): $mapfile"
    ((OK++))
  else
    echo "❌ LEAK DETECTED (Invalid): $mapfile"
    ((FAIL++))
    # Logun son kısmını göster ki hatayı görelim
    grep "definitely lost" "$log" -A 2 || true
    grep "in use at exit" "$log" || true
  fi
}

# ---------------------------------------------------
# VALID MAP LEAK CHECK (Input Gerekir: ESC)
# ---------------------------------------------------
check_leak_valid() {
  local mapfile="$1"
  local log="logs/leak_valid_$(basename "$mapfile").log"

  # 1. Valgrind'i arka planda başlat
  valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all "$BIN" "$mapfile" >"$log" 2>&1 &
  PID=$!

  # 2. Bekle (Valgrind ile oyun ÇOK yavaş açılır, süreyi uzun tut)
  sleep 5

  # 3. ESC tuşuna bas
  xdotool key Escape

  # 4. İşlemin bitmesini bekle
  wait $PID

  # 5. Log dosyasını kontrol et
  if grep -q "All heap blocks were freed" "$log" && grep -q "in use at exit: 0 bytes" "$log"; then
    echo "✅ LEAK FREE (Valid): $mapfile"
    ((OK++))
  else
    echo "❌ LEAK DETECTED (Valid): $mapfile"
    ((FAIL++))
    grep "definitely lost" "$log" -A 2 || true
    grep "in use at exit" "$log" || true
  fi
}

echo "========================================"
echo "==> Invalid Map Leak Tests"
echo "========================================"
for m in "${INVALID_MAPS[@]}"; do
  [ -f "$m" ] && check_leak_invalid "$m"
done

echo ""
echo "========================================"
echo "==> Valid Map Leak Tests"
echo "========================================"
for m in "${VALID_MAPS[@]}"; do
  [ -f "$m" ] && check_leak_valid "$m"
done

echo "----------------------------------------"
echo "Summary: $OK LEAK FREE, $FAIL LEAK DETECTED"
echo "----------------------------------------"

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi
exit 0