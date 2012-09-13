class Poly

  K = 3

  # Sucks, but ok for a debugging script
  def self.part_size=(part_size)
    @@part_size = part_size
  end

  def initialize(s)
    if s.is_a? String
      a = s.split(" ").collect {|e| e.rjust(16, "0").to_i(16)}.reverse
      raise if a.length > K * @@part_size
      @coeffs = []
      K.times do |i|
        break if i * @@part_size > a.length
        part = a[i*@@part_size...(i+1)*@@part_size]
        @coeffs.push(part.reverse.inject(0) { |a, b| (a << 64) + b })
      end
    elsif s.is_a? Array
      @coeffs = s
    else
      raise
    end
  end

  attr_reader :coeffs

  def [](x)
    @coeffs.reverse.inject(0) { |a, b| a * x + b }
  end

  def deg
    @coeffs.length - 1
  end

  def *(other)
    r = [0] * (deg + other.deg + 1)
    @coeffs.each_with_index do |e, i|
      other.coeffs.each_with_index do |u, j|
        r[i + j] += e * u
      end
    end
    Poly.new(r)
  end

end

def num(s)
  if s[0] == "-"
    s.slice!(0)
    sign = -1
  else
    sign = 1
  end
  s.split(" ").collect { |e| e.to_i(16) }.inject(0) { |a, b| (a << 64) + b } * sign
end
