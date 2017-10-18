in=ra666666

all: mkimage

source:
	#Define a fonte dos comandos arm- (source)
	#Não funciona pelo "make", deve copiar e colar o comando no bash
	. /home/specg12-1/mc404/simulador/set_path.sh

mkimage: linked
	#Gera a imagem do cartao SD
	mksd.sh --so /home/specg12-1/mc404/simulador/dummyos.elf --user ${in}

linked: $(in).o
	#Execucao do Linker
	arm-eabi-ld ${in}.o -g -o ${in} -Ttext=0x77802000 -Tdata=0x77803050

%.o: %.s
	#Execucao do Assembler
	arm-eabi-as -g $< -o $*.o

simulate: disk.img
	arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin --sd=disk.img

simulate_file: disk.img
	(arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin --sd=disk.img 2>&1) > ${in}.out

simulate_gdb: disk.img
	#Executa o programa em paralelo com uma instância do GDB em outro terminal
	arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin --sd=disk.img -g

start_gdb: disk.img
	#inicia o gdb para debugar o programa gerado
	# Usar: "target remote localhost:5000" para acessar o programa remotamente
	arm-eabi-gdb ${in}

clean:
	rm -f ${in} ${in}.o
