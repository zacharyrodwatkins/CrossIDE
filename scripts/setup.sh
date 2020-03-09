#!/bin/bash
export crs_dir=$(cd ..; pwd)
export asm_compiler=$crs_dir"/Call51/Bin/a51.exe"
export qrt_stp=$(locate --regex quartus/bin/quartus_stp$)
export load_script=$(locate CrossIDE/Load_Script.tcl)

