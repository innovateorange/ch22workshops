FLAGS="-fopenmp"
COMP="-O3"

.SILENT: all

hello:
	gcc ${FLAGS} src/hello.c -o build/hello

pi_serial:
	gcc ${FLAGS} src/pi_serial.c -o build/pi_serial


pi_parallel:
	gcc ${FLAGS} src/pi_parallel.c -o build/pi_parallel

pi_parallel_pad:
	gcc ${FLAGS} src/pi_parallel_pad.c -o build/pi_parallel_pad

pi_loop_redux:
	gcc ${FLAGS} src/pi_loop_redux.c -o build/pi_loop_redux

pi_atomic:
	gcc ${FLAGS} src/pi_atomic.c -o build/pi_atomic

pi_critical:
	gcc ${FLAGS} src/pi_critical.c -o build/pi_critical


mandel_correct:
	gcc ${FLAGS} src/mandel_correct.c -o build/mandel_c

mandel_wrong:
	gcc ${FLAGS} src/mandel_wrong.c -o build/mandel_w

pi_final:
	gcc ${FLAGS} src/pi_final.c -o build/pi_final

all:
	@make -s hello
	@make -s pi_serial
	@make -s pi_parallel
	@make -s pi_parallel_pad
	@make -s pi_loop_redux
	@make -s pi_atomic
	@make -s pi_critical
	@make -s pi_final
	@make -s mandel_wrong
	@make -s mandel_correct

clean:
	@rm -f build/hello
	@rm -f build/pi_*
	@rm -f build/mandel_*
