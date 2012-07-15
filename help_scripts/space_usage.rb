INITIAL_VALUES = [
                  [0]
                  [0, 2],
                  [0, 9, 16],
                  [0, 20, 29, 38]
                  ]

def f(m, n)
  return f(n, m) if m < n
  if m <= 3
    INITIAL_VALUES[m][n]
  end
  m2 = (m / 2.0).ceil
  if n <= m2
    f(m2 + 1, n) + 2 * m2 + n + 1
  else
    f(m2 + 1, m2 + 1) + m + n + 2 * m2 + 2
  end
end
