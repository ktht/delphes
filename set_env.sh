#!/bin/bash

# source this file

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

case :$PATH: in
  *:$SCRIPT_DIR:*)  ;;  # do nothing
  *) PATH=$SCRIPT_DIR:$PATH ;;
esac

case :$LD_LIBRARY_PATH: in
  *:$SCRIPT_DIR:*)  ;;  # do nothing
  *) LD_LIBRARY_PATH=$SCRIPT_DIR:$LD_LIBRARY_PATH ;;
esac

case :$ROOT_INCLUDE_PATH: in
  *:$SCRIPT_DIR/external:*)  ;;  # do nothing
  *) ROOT_INCLUDE_PATH=$SCRIPT_DIR/external:$ROOT_INCLUDE_PATH ;;
esac
