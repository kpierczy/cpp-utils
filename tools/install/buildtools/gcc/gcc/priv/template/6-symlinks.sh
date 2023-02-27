#!/usr/bin/bash -e
# ====================================================================================================================================
# @file       6-symlinks.bash
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 21st July 2021 10:50:38 pm
# @modified   Thursday, 29th December 2022 1:56:26 am
# @project    cpp-utils
# @brief      Script creating symbolic links for built binaries
#    
# @author Lucjan Bryndza (original source: https://github.com/lucckb/isixrtos/tree/master/extras/toolchain/mac)
# @maintainer Krzysztof Pierczyk
# ====================================================================================================================================

# Source config file
source $PROJECT_HOME/scripts/toolchain/config.bash

# Create symbolic links to binaries
for i in /usr/local/arm-none-eabi-gcc/*; do
	ln -s $i /usr/local/bin
done
