#!/usr/bin/ruby

def g(m, n)
  m2 = (m / 2.0).ceil
  z0 = 2 * m2
  z2 = (n <= m2 ? m2 : 2 * m2)
  x2 = m2
  y2 = (n <= m2 ? 0 : m2)
  z1 = (n2 <= m2 ? f(x2, n) : f(x2, y2) )
end

def f(m, n)
  return f(n, m) if m < n
  return 0 if n <= 0
  return 2 if m == 1
  m2 = (m / 2.0).ceil
  z0 = 2 * m2
  z2 = (n <= m2 ? m2 : 2 * m2)
  x2 = m2 + 1
  y2 = (n <= m2 ? 0 : m2 + 1)
  if m == m2 + 1
    z1 = (n2 <= m2 ? g(x2, n) : g(x2, y2))
  else
    z1 = (n2 <= m2 ? f(x2, n) : f(x2, y2) )
  end
  z0 + z1 + z2 + x2 + y2
end

puts "{" + (0..3).collect do |n|
  "{" + (0..3).collect do |m|
    f(m, n).to_s
  end.join(", ") + "}"
end.join(", ") + "}"

