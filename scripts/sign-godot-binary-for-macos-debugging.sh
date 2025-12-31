#!/usr/bin/env bash
set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
GODOT_APP="/Applications/Godot.app"
ENTITLEMENTS_FILE="${SCRIPT_DIR}/files/debug.entitlements"

if [ ! -d "$GODOT_APP" ]; then
    echo "Error: $GODOT_APP not found."
    exit 1
fi

if [ ! -f "$ENTITLEMENTS_FILE" ]; then
    echo "Error: $ENTITLEMENTS_FILE not found."
    exit 2
fi

echo "Signing Godot with debugging entitlements (requires sudo)..."
sudo codesign --force --deep --sign - --entitlements "$ENTITLEMENTS_FILE" "$GODOT_APP"

echo "Done. You can now attach the debugger."
