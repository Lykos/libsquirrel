require 'RubyDataStructures'
require 'yaml'

KEY_FILE = File.join(File.dirname(__FILE__), 'key.yml')
KEY = YAML::load(File::read(KEY_FILE))

include Crypto

ENC = ElgamalEncrypter.new(KEY[:public_key], KEY[:initial_state])
DEC = ElgamalDecrypter.new(KEY[:private_key], KEY[:initial_state])

p = "Affe"
c = ENC.encrypt(p)
rp = DEC.decrypt(c)
puts p == rp
puts rp

