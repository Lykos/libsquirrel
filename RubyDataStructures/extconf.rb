#!/usr/bin/ruby

require "mkmf"

extension_name = "RubyDataStructures"
dir_config(extension_name)
find_header("longint.h", "/usr/local/include/DataStructures")

if have_library("DataStructures")
  create_header
  create_makefile(extension_name)
else
  raise "could not find DataStructures library"
end

