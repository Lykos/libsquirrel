def gen_parts(number)
  raise if number < 0
  intermediate_result = 0
  lines = []
  number.to_s.each_char do |c|
    intermediate_result *= 10
    intermediate_result += c.to_i
    r = intermediate_result
    parts = []
    while r > 0
      parts.push((r % (1 << 64)).to_s.rjust(20))
      r /= 1 << 64
    end
    parts.reverse!
    lines.push(parts.join(" "))
  end
  lines.collect! do |l|
    l.rjust(lines[-1].length)
  end
  lines.join("\n")
end
