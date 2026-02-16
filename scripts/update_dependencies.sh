#!/usr/bin/env bash
set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "${SCRIPT_DIR}/.."

# Configurable target URL & branch for Stagehand (can be overridden via env)
: ${STAGEHAND_REPO_URL="git@github.com:VerdantInteractive/Stagehand.git"}
: ${STAGEHAND_BRANCH:=alpha}


if ! git remote get-url stagehand >/dev/null 2>&1; then
	git remote add -f stagehand "${STAGEHAND_REPO_URL}"
else
	git remote set-url stagehand "${STAGEHAND_REPO_URL}"
fi

git stash

git fetch stagehand "${STAGEHAND_BRANCH}"
git subtree pull --prefix addons/stagehand stagehand "${STAGEHAND_BRANCH}" --squash

git stash pop
