#!/usr/local/bin/ruby

=begin

 => Exercicio feito em Ruby
	Necessario ruby instalado no computador

	Para executar :
	Digite no terminal

	$ruby fcfs.rb

	ou

	$chmod +x fcfs.rb
	e
	$./fcfs.rb


=end

require 'csv'

class Job
    attr_accessor :nome, :sobrenome
    def initialize(burst, delay)
        @Burst = burst.to_f
        @Delay = delay.to_f
    end

    def Burst
    	return @Burst
    end

    def Delay
    	return @Delay
    end
end

# -------------------------------------------------------------------
#                              MAIN
# -------------------------------------------------------------------

filaJobs = []

CSV.foreach("teste.csv") do |row|
	filaJobs << Job.new(row[0],row[1])
end

i = 0
waitTime = 0.to_f
burstAnt = 0.to_f
cpuTime = 0.to_f
turnaround = 0.to_f
aux = 0.to_i
maiorWait = 0.to_i
menorWait = 0.to_i
executionTime = 0.to_f
menorTurnaround = 0.to_f
maiorTurnaround = 0.to_f

firstDelay = filaJobs[0].Delay

for i in 0..(filaJobs.length-1)

	delay = filaJobs[i].Delay
	burst = filaJobs[i].Burst
	
	executionTime = executionTime + burst
	cpuTime = cpuTime + delay
	aux = 0
	if(delay < burstAnt)
		aux = burstAnt - delay
		if(aux > maiorWait)
			maiorWait = aux
		elsif(burst < menorWait)
			menorWait = aux
		end

		if(burst + aux > maiorTurnaround)
			maiorTurnaround = burst + aux
		elsif(burst < menorTurnaround)
			menorTurnaround = burst + aux
		end

		waitTime = waitTime + aux
		turnaround = turnaround + burst + aux
		burstAnt = burst + aux
	else
		waitTime = waitTime
		if(burst > maiorTurnaround)
			maiorTurnaround = burst
		elsif(burst < menorTurnaround)
			menorTurnaround = burst
		end
		turnaround = turnaround + burst
		burstAnt = burst
	end
end

cpuTime = executionTime.to_f/(cpuTime + filaJobs[filaJobs.length-1].Burst)
waitTime = (waitTime.to_f)/filaJobs.length  
turnaround = turnaround/filaJobs.length

puts "\nWait time: min = #{menorWait} max = #{maiorWait} mean = #{waitTime}"
#Como o escalonador não é preemptivo o response time será semelhante ao wait time
puts "Response time: min = #{menorWait} max = #{maiorWait} mean = #{waitTime}"
puts "Turnaround time: min = #{menorTurnaround} max = #{maiorTurnaround} mean = #{turnaround}"
puts "CPU utilization: #{cpuTime.round(2)}\n\n"


exit