#!/usr/bin/ruby

require "mkmf"

extension_name = "RubyDataStructures"
dir_config(extension_name)

raise "could not find boost_random library" unless have_library("boost_random")
raise "could not find DataStructures library" unless have_library("DataStructures")
raise "could not find Crypto library" unless have_library("Crypto")

CXX="gcc --std=c++11"

create_header
create_makefile(extension_name)
