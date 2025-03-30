run:
	./program.exe
interpolator:
	g++ ./lec6/interpolator.cpp ./lec2/SLE_solver.cpp ./helpers/print_helper.cpp -o program.exe

newton_inter:
	g++ ./lec6/newton_interpolator.cpp -o program.exe
parametric:
	g++ ./lec6/parametric.cpp -o program.exe