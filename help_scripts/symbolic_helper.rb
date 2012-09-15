require 'mathn'
require 'symbolic'
include Symbolic

def inf
  :inf
end

def r_table
  $r_table ||= Hash.new
end

def r(x)
  r_table[x] ||= var :name => "r(#{x})"
end

r3_1 = 16 * (r(1) + r(-1))
r2_1 = r(1/2) + r(-1/2)
r4_1 = (r3_1 - r2_1) / 3
r3_2 = r3_1 / 4
r2_2 = (r2_1 - r3_2) / 3
r3_3 = 2 * (16 * r(0) - r(inf))
r2_3 = (r2_2 + r3_3) / 8 - r(0)
r4_2 = (r2_2 - r3_3) / 8 - r(inf)
