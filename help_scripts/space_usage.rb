# Next higher two potence
#
def h(n)
  return 0 if n == 0
  result = 1
  while result < n
    result <<= 1
  end
  result
end

# Space usage for result
#
def g(m, n)
  if n > 0 && m > 0
    m + n
  else
    0
  end
end


# Space usage for calculation
#
def f(m, n)
  return f(n, m) if m < n
  return 0 if n <= 0
  return 2 if m == 1
  return 9 if m == 2 && n == 1
  return 16 if m == 2 && n == 2
  if n <= h(m) / 2
    g(h(m) / 2, n) + h(m) / 2 + 1 + f(h(m) / 2 + 1, n)
  else
     g(h(m) / 2, h(m) / 2) + g(m - h(m) / 2, n - h(m) / 2) + h(m) + 2 + f(h(m) / 2 + 1, h(m) / 2 + 1)
  end
end
