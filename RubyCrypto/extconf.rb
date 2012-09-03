#!/usr/bin/ruby

require "mkmf-rice"

extension_name = "RubyCrypto"
dir_config(extension_name)

raise "could not find boost_random library" unless have_library("boost_random")
raise "could not find DataStructures library" unless have_library("DataStructures")
raise "could not find Crypto library" unless have_library("Crypto")
raise "could not find rice library" unless have_library("rice")

create_header
create_makefile(extension_name)

# Add c++ flag
puts "Adding c++ flag"
lines = File.readlines("Makefile")
File.open("Makefile", 'w') do |f|
  lines.each do |l|
    if l["CXXFLAGS"]
      l = l.chomp + " -std=c++11\n"
    end
    f.puts(l)
  end
end
