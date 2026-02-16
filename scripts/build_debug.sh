#!/usr/bin/env bash
set -e

scons -C addons/stagehand debug_symbols=yes optimize=debug "$@"
