#!/usr/bin/ruby

require 'RubyCrypto'
require 'yaml'

KEY_FILE = File.join(File.dirname(__FILE__), 'key.yml')
KEY = YAML::load(File::read(KEY_FILE))

include Crypto

ELGAMAL_ENC = ElgamalEncrypter.new(KEY[:public_key], KEY[:initial_state])
ELGAMAL_DEC = ElgamalDecrypter.new(KEY[:private_key], KEY[:initial_state])

ELGAMAL_SIG = ElgamalSigner.new(KEY[:private_key])
ELGAMAL_VER = ElgamalVerifier.new(KEY[:public_key])

LONG_PLAIN = <<EOS
Arbeitsschule nannte zu Beginn des 20. Jahrhunderts eine Richtung der deutschen 
Reformp?dagogik ihr Reformprojekt einer neuen Schule. Dabei wurde der Begriff 
sehr heterogen verstanden.

Auf der Reichsschulkonferenz 1920 und in vielen anderen reformp?dagogischen 
Zusammenk?nften in Deutschland diskutierten die Erneuerer ?ber eine Schule, die 
sich von der "Buch- und Paukschule" abgrenzen sollte, die f?r das wilhelminische 
Schulsystem als typisch behauptet wurde. Arbeitsp?dagogik galt als der Weg aus 
der obrigkeitsorientierten Schule des 19. Jahrhunderts. Allerdings wurde 
Arbeitsp?dagogik schon auf der Reichsschulkonferenz sehr unterschiedlich gefasst.
EOS

SHORT_PLAIN = "Affe"

plain = SHORT_PLAIN
success = true

cipher = ELGAMAL_ENC.encrypt(plain)
replain = ELGAMAL_DEC.decrypt(cipher)
if replain != plain
  puts "plain:"
  puts plain
  puts
  puts "replain:"
  puts replain
  puts
  success = false
else
  puts "replain == plain"
end

signed = ELGAMAL_SIG.sign(plain)
if !ELGAMAL_VER.verify(signed)
  puts "Invalid signature."
  success = false
else
  puts "Signature correct"
end

unsigned = ELGAMAL_VER.remove_signature(signed)
if unsigned != plain
  puts "plain:"
  puts plain
  puts
  puts "unsigned:"
  puts unsigned
  puts
  success = false
else
  puts "unsigned == plain"
end

puts "SUCCESS!" if success
