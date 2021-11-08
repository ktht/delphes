#!/bin/bash

# source this file

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

case :$PATH: in
  *:$SCRIPT_DIR:*) export PATH ;;  # make sure to export
  *) export PATH=$SCRIPT_DIR:$PATH ;;
esac

case :$LD_LIBRARY_PATH: in
  *:$SCRIPT_DIR:*) export LD_LIBRARY_PATH ;;  # make sure to export
  *) export LD_LIBRARY_PATH=$SCRIPT_DIR:$LD_LIBRARY_PATH ;;
esac

case :$ROOT_INCLUDE_PATH: in
  *:$SCRIPT_DIR/external:*) export ROOT_INCLUDE_PATH ;;  # make sure to export
  *) export ROOT_INCLUDE_PATH=$SCRIPT_DIR/external:$ROOT_INCLUDE_PATH ;;
esac

case :$DELPHES_PILEUP: in
  *:$SCRIPT_DIR:*) export DELPHES_PILEUP  ;;  # make sure to export
  *) export DELPHES_PILEUP=$SCRIPT_DIR:$DELPHES_PILEUP ;;
esac

case :$DELPHES_CARDS: in
  *:$SCRIPT_DIR/cards:*) export DELPHES_CARDS  ;;  # make sure to export
  *) export DELPHES_CARDS=$SCRIPT_DIR/cards:$DELPHES_CARDS ;;
esac
