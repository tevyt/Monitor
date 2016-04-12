require 'rubyserial'

class Monitor
  attr_reader :heart_rate

  def initialize(port , baud_rate)
    @serial_port = Serial.new port, baud_rate
    @heart_rate = 60.0
  end

  def read_heart_rate()
    @heart_rate = @serial_port.read 5
  end

  def write_heart_rate(rate)
    @serial_port.write rate
    @heart_rate = rate.to_f
  end

  def level()
    case @heart_rate
    when 70 ... 120, 30 ... 50
      'WARN'
    when 50 ... 70 
      'SAFE'
    else
      'DANGER'
    end
  end
end

monitor = Monitor.new('/dev/ttyACM0', 9600)
while true
  # monitor.read_heart_rate
  puts 
  puts "*********************************************"
  puts "*Reading as of #{Time.now}    *"
  puts "*********************************************"
  puts "Heart Rate: #{monitor.heart_rate}"
  puts "Level: #{monitor.level}"
  print "Send new heart rate: "
  new_rate = gets.chomp
  puts
  monitor.write_heart_rate new_rate
end
