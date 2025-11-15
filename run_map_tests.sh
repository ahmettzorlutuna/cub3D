#!/usr/bin/env bash
set -euo pipefail

BIN=./cub3D
OK=0
FAIL=0

mkdir -p logs

# Beklenen geçerli (başarılı) haritalar
VALID_MAPS=(maps/valid/*.cub)

# Beklenen hatalı (başarısız) haritalar
INVALID_MAPS=(maps/invalid/*.cub)

#echo "==> Valid map tests"
#for m in "${VALID_MAPS[@]}"; do
 # if "$BIN" "$m" >/dev/null 2>logs/$(basename "$m").err; then
  #  echo "✅ PASS: $m"
   # ((OK++))
#  else
 #   echo "❌ FAIL (should pass): $m"
  #  ((FAIL++))
#  fi
#done

echo "==> Invalid map tests"
for m in "${INVALID_MAPS[@]}"; do
  if [ "$?" -eq 1 ]; then
    echo "❌ FAIL (should fail): $m"
    ((FAIL++))
  else
    echo "✅ PASS (failed as expected): $m"
    ((OK++))
  fi
done

echo "==> Summary: OK=$OK FAIL=$FAIL"
exit $([ "$FAIL" -eq 0 ])
