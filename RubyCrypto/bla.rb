#!/usr/bin/ruby

require 'RubyCrypto'
require 'yaml'

KEY_FILE = File.join(File.dirname(__FILE__), 'key.yml')
KEY = YAML::load(File::read(KEY_FILE))

include Crypto

ENC = ElgamalEncrypter.new(KEY[:public_key], KEY[:initial_state])
DEC = ElgamalDecrypter.new(KEY[:private_key], KEY[:initial_state])

P = <<EOS
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

C = ENC.encrypt(P)
RP = DEC.decrypt(C)

if P != RP
  puts P
  puts RP
else
  puts "SUCCESS!"
end
