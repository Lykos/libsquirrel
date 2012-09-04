#!/usr/bin/ruby

require 'RubyCrypto'
require 'yaml'

KEY_FILE = File.join(File.dirname(__FILE__), 'key.yml')
CONFIG = YAML::load(File::read(KEY_FILE))

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

include Crypto

ELGAMAL_KG = ElgamalKeyGenerator.new
PUBLIC_KEY, PRIVATE_KEY = ELGAMAL_KG.generate(512)

ELGAMAL_STATE = CONFIG[:initial_state]

ELGAMAL_ENC = ElgamalEncrypter.new(PUBLIC_KEY, ELGAMAL_STATE)
ELGAMAL_DEC = ElgamalDecrypter.new(PRIVATE_KEY, ELGAMAL_STATE)

ELGAMAL_SIG = ElgamalSigner.new(PRIVATE_KEY)
ELGAMAL_VER = ElgamalVerifier.new(PUBLIC_KEY)

aes_key = ""
while aes_key.length < 32
  aes_key = sprintf("%x", rand(1 << 128))
end
AES_KEY = aes_key

aes_state = ""
while aes_state.length < 32
  aes_state = sprintf("%x", rand(1 << 128))
end
AES_STATE = aes_state

AES_ENC = AESEncrypter.new(AES_KEY, AES_STATE)
AES_DEC = AESDecrypter.new(AES_KEY, AES_STATE)

AES_SIG = AESSigner.new(AES_KEY, AES_STATE)
AES_VER = AESVerifier.new(AES_KEY, AES_STATE)

DH_KE_1 = DHKeyExchange.new
DH_KE_2 = DHKeyExchange.new

plain = LONG_PLAIN
success = true

elgamal_cipher = ELGAMAL_ENC.encrypt(plain)
elgamal_replain = ELGAMAL_DEC.decrypt(elgamal_cipher)
if elgamal_replain != plain
  puts "plain:"
  puts plain
  puts
  puts "elgamal_replain:"
  puts elgamal_replain
  puts
  success = false
else
  puts "elgamal_replain == plain"
end

elgamal_signed = ELGAMAL_SIG.sign(plain)
if !ELGAMAL_VER.verify(elgamal_signed)
  puts "Invalid signature."
  success = false
else
  puts "Signature correct"
end

elgamal_unsigned = ELGAMAL_VER.remove_signature(elgamal_signed)
if elgamal_unsigned != plain
  puts "plain:"
  puts plain
  puts
  puts "elgamal_unsigned:"
  puts unsigned
  puts
  success = false
else
  puts "elgamal_unsigned == plain"
end

aes_cipher = AES_ENC.encrypt(plain)
aes_replain = AES_DEC.decrypt(aes_cipher)
if aes_replain != plain
  puts "plain:"
  puts plain
  puts
  puts "aes_replain:"
  puts aes_replain
  puts
  success = false
else
  puts "aes_replain == plain"
end

aes_signed = AES_SIG.sign(plain)
if !AES_VER.verify(aes_signed)
  puts "Invalid signature."
  success = false
else
  puts "Signature correct"
end

aes_unsigned = AES_VER.remove_signature(aes_signed)
if aes_unsigned != plain
  puts "plain:"
  puts plain
  puts
  puts "aes_unsigned:"
  puts aes_unsigned
  puts
  success = false
else
  puts "aes_unsigned == plain"
end

group = DH_KE_1.choose_group(512)
group1 = DH_KE_1.group
if group != group1
  puts "group:"
  puts group
  puts
  puts "group1:"
  puts group1
  puts
  success = false
else
  puts "group == group1"
end
DH_KE_2.group = group1
group2 = DH_KE_2.group
if group != group2
  puts "group:"
  puts group
  puts
  puts "group2:"
  puts group2
  puts
  success = false
else
  puts "group == group2"
end
DH_KE_1.other_part = DH_KE_2.own_part
DH_KE_2.other_part = DH_KE_1.own_part
key1 = DH_KE_1.key
key2 = DH_KE_2.key
if key1 != key2
  puts "key1:"
  puts key1
  puts
  puts "key2:"
  puts key2
  puts
  success = false
else
  puts "key1 == key2"
end

puts "SUCCESS!" if success
