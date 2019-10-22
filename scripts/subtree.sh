#!/bin/bash

show_usage() {
          echo "Usage: $0 module_name {pull|push}"
          exit 1
}

SUBTREE_BRANCH=master

# subtree item list
case "$2" in
  imgui)
          SUBTREE_DIR=3rdparty/imgui
          SUBTREE_REPO=https://github.com/Flix01/imgui.git
          SUBTREE_BRANCH=imgui_with_addons
          ;;
  *)
          show_usage
          ;;
esac

# operation
case "$1" in
  pull)
          git subtree pull --prefix=$SUBTREE_DIR $SUBTREE_REPO $SUBTREE_BRANCH --squash
          ;;
  push)
          git subtree push --prefix=$SUBTREE_DIR $SUBTREE_REPO $SUBTREE_BRANCH
          ;;
  *)
          show_usage
esac

exit $?