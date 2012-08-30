require 'RubyDataStructures'
require 'yaml'

KEY_FILE = File.join(File.dirname(__FILE__), 'key.yml')
KEY = YAML::load(File::read(KEY_FILE))

include Crypto

ENC = ElgamalEncrypter.new(KEY[:public_key], KEY[:initial_state])
DEC = ElgamalDecrypter.new(KEY[:private_key], KEY[:initial_state])

P = "Affe"
C = ENC.encrypt(P)
RP = DEC.decrypt(C)
if P != RP
puts P
puts RP
end
